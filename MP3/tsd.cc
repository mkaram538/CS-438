/*
 *
 * Copyright 2015, Google Inc.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are
 * met:
 *
 *     * Redistributions of source code must retain the above copyright
 * notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above
 * copyright notice, this list of conditions and the following disclaimer
 * in the documentation and/or other materials provided with the
 * distribution.
 *     * Neither the name of Google Inc. nor the names of its
 * contributors may be used to endorse or promote products derived from
 * this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */

#include <ctime>

#include <google/protobuf/timestamp.pb.h>
#include <google/protobuf/duration.pb.h>

#include <fstream>
#include <iostream>
#include <memory>
#include <string>
#include <stdlib.h>
#include <unistd.h>
#include <thread>
#include <google/protobuf/util/time_util.h>
#include <grpc++/grpc++.h>
#include <sys/stat.h>
#include <sys/types.h>

#include "sns.grpc.pb.h"
#include "coord.grpc.pb.h"

using google::protobuf::Timestamp;
using google::protobuf::Duration;
using google::protobuf::util::TimeUtil;
using grpc::Server;
using grpc::ServerBuilder;
using grpc::ServerContext;
using grpc::ServerReader;
using grpc::ServerReaderWriter;
using grpc::ServerWriter;
using grpc::Channel;
using grpc::ClientContext;
using grpc::ClientReader;
using grpc::ClientReaderWriter;
using grpc::ClientWriter;
using grpc::Status;
using csce438::Message;
using csce438::ListReply;
using csce438::Request;
using csce438::Reply;
using csce438::SNSService;
using csce438::None;
using csce438::ClientInfo;
using csce438::ServerInfo;
using csce438::COORDService;

struct Client {
  std::string username;
  bool connected = false;
  ServerReaderWriter<Message, Message>* stream = 0;
};

struct Process {
  std::string directoryName;
  std::string portNum;
  std::string procType;
  std::string procID;
  std::string coordPort;
  std::string coordIP;
};

Process currentProcess;

// Stores the coordinator stub and a stub to the slave process for the master to call
std::unique_ptr<COORDService::Stub> coord_stub_;
std::unique_ptr<SNSService::Stub> slave_stub_;

//Vector that stores every client that has been created. Kept primarily to store the stream
//information used in timeline
std::vector<Client> client_db;

//Helper function used to find a Client object given its username
int find_user(std::string username){
  int index = 0;
  for(Client c : client_db){
    if(c.username == username)
      return index;
    index++;
  }
  return -1;
}

class SNSServiceImpl final : public SNSService::Service {
  
  // Iterates through the followers file for a particular client as well as the all clients file,
  // adding them to the return struct. These files are maintained by the synchronizer.
  Status List(ServerContext* context, const Request* request, ListReply* list_reply) override {
    std::string client_id = request->username();

    std::string followers_path = currentProcess.directoryName + "/" + client_id + "_followers.txt";
    std::ifstream read_followers(followers_path,std::ios::app|std::ios::out|std::ios::in);

    std::string follower;

    if (read_followers.is_open()) {
      while (getline(read_followers, follower)) {
        list_reply->add_followers(follower);
      }
      read_followers.close();
    }

    std::string users_path = currentProcess.directoryName + "/all_clients.txt";
    std::ifstream read_clients(users_path,std::ios::app|std::ios::out|std::ios::in);

    std::string client;

    if (read_clients.is_open()) {
      while (getline(read_clients, client)) {
        list_reply->add_all_users(client);
      }
      read_clients.close();
    }

    return Status::OK;
  }

  // Opens {username}_following.txt in directory, reads through entries to make sure that the
  // client is not already following that client, then writes new entry into file
  Status Follow(ServerContext* context, const Request* request, Reply* reply) override {
    
    // Sends same request to the slave socket if the current process is the master
    // to maintain changes
    if (currentProcess.procType == "master") {
      Reply slave_reply;
      Request slave_request;
      slave_request.set_username(request->username());
      slave_request.add_arguments(request->arguments(0));
      ClientContext clientContext;
      slave_stub_->Follow(&clientContext, slave_request, &slave_reply);
    }

    std::string username1 = request->username();
    std::string username2 = request->arguments(0);

    std::string filename = "/" + username1 + "_following.txt";
    std::string filePath = currentProcess.directoryName + filename;
    std::ifstream read_follow(filePath,std::ios::app|std::ios::out|std::ios::in);

    std::string follows;

    if (read_follow.is_open()) {
      while (getline(read_follow, follows)) {
        if (follows == username2) {
          reply->set_msg("you have already joined");
          return Status::OK;
        }
      }
    }

    read_follow.close();

    std::ofstream write_file(filePath,std::ios::app|std::ios::out|std::ios::in);
    if (write_file.is_open()) {
      write_file << username2 << "\n";
      write_file.close();
    }

    reply->set_msg("Follow Successful");
    return Status::OK;
  }
  
  // Checks to see if the client has already joined the server, if not adds the clients
  // id to the list of local clients as well as the list of global clients
  Status Login(ServerContext* context, const Request* request, Reply* reply) override {

    Client c;
    // Sends same request to the slave socket if the current process is the master
    // to maintain changes
    if (currentProcess.procType == "master") {
      Reply slave_reply;
      Request slave_request;
      slave_request.set_username(request->username());
      ClientContext clientContext;
      slave_stub_->Login(&clientContext, slave_request, &slave_reply);
    }

    // Adds to client_db which is used to store the streams for timeline
    std::string username = request->username();
    int user_index = find_user(username);
    if (user_index < 0) {
      c.username = username;
      client_db.push_back(c);
    }

    std::string filename = "/all_clients.txt";
    std::string filePath = currentProcess.directoryName + filename;
    std::ifstream read_clients(filePath,std::ios::app|std::ios::out|std::ios::in);

    std::string client;

    // Checks if the client has already joined
    if (read_clients.is_open()) {
      while (getline(read_clients, client)) {
        if (client == username) {
          std::string msg = "Welcome Back " + username;
	        reply->set_msg(msg);
          return Status::OK;
        }
      }
      read_clients.close();
    }

    std::ofstream write_all_clients(filePath,std::ios::app|std::ios::out|std::ios::in);
    if (write_all_clients.is_open()) {
      write_all_clients << username << "\n";
      write_all_clients.close();
    }

    filename = "/server_" + currentProcess.procID + "_clients.txt";
    filePath = currentProcess.directoryName + filename;
    std::ofstream write_local_clients(filePath,std::ios::app|std::ios::out|std::ios::in);
    if (write_local_clients.is_open()) {
      write_local_clients << username << "\n";
      write_local_clients.close();
    }

    return Status::OK;
  }

  // Differs from MP2 implementation in that, this function now only reads in, while a looping thread
  // does all of the writing. When a message comes in, it finds the username of the client from the message.
  // If the message isn't "Set Stream" adds the message to both the client's feed and timeline.
  // If the message is "Set Stream" the stream is stored in the client db and the last 20 messages
  // in the client's timeline is sent to the client
  Status Timeline(ServerContext* context, ServerReaderWriter<Message, Message>* stream) override {
    Message message;
    Client *c;
    while(stream->Read(&message)) {

      std::string username = message.username();
      int user_index = find_user(username);
      c = &client_db[user_index];
      std::string filename = "/" + username + "_feed.txt";
      std::string filepath = currentProcess.directoryName + filename;
      std::ofstream user_file(filepath,std::ios::app|std::ios::out|std::ios::in);

      // Creates the file input from the message
      google::protobuf::Timestamp temptime = message.timestamp();
      std::string time = google::protobuf::util::TimeUtil::ToString(temptime);
      std::string fileinput = time+"::"+message.username()+":"+message.msg()+"\n";

      std::string timeline_filename = "/" + username + "_timeline.txt";
      std::string timeline_filepath = currentProcess.directoryName + timeline_filename;
      std::ofstream timeline_file(timeline_filepath,std::ios::app|std::ios::out|std::ios::in);

      //"Set Stream" is the default message from the client to initialize the stream
      if (message.msg() != "Set Stream") {
        user_file << fileinput;
        timeline_file << fileinput;

        // Writes changes to the slave's copy of these files as well if the
        // current process is the master
        if (currentProcess.procType == "master") {
          std::string slave_dir = "slave_" + currentProcess.procID;
          std::string slave_filepath = slave_dir + filename;
          std::ofstream slave_user_file(slave_filepath,std::ios::app|std::ios::out|std::ios::in);

          std::string slave_timeline_filepath = slave_dir + timeline_filename;
          std::ofstream slave_timeline_file(slave_timeline_filepath,std::ios::app|std::ios::out|std::ios::in);
          
          
          slave_user_file << fileinput << "\n";
          slave_timeline_file << fileinput << "\n";

          slave_user_file.close();
          slave_timeline_file.close();
        }
      }

      else {
        if (c->stream == 0) {
          c->stream = stream;
        }

        // Stores that the client is now connected to the timeline so that the timeline
        // writing function can beginning looking fo updates
        c->connected = true;
        std::string timeline_path = currentProcess.directoryName + "/" + username + "_timeline.txt";
        std::ifstream read_timeline(timeline_path,std::ios::app|std::ios::out|std::ios::in);

        // Gets at most the last 20 messages in the client's timeline and sends them
        if (read_timeline.peek() != std::ifstream::traits_type::eof()) {
          std::vector<std::string> full_timeline;
          std::string line;
          int counter = 20;
          if (read_timeline.is_open()) {
            while (getline(read_timeline, line) && counter > 0) {
              if (isdigit(line[0])) {
                full_timeline.push_back(line);
                counter--;
              }
            }
          }
          int timeline_size = full_timeline.size();
          int number_to_print = std::min(20, timeline_size);
          Message new_msg;
          new_msg.set_msg("-------------------------------------");
          c->stream->Write(new_msg);
          for (int i = 0; i < number_to_print; i++) {
            new_msg.set_msg(full_timeline[i]);
            stream->Write(new_msg);
          }
        }
      }
    }
    // Client has disconnected from timeline, writer should not look for updates
    c->connected = false;
    return Status::OK;
  }
};

// Every 30 seconds, iterates through all of the clients in this server looking for changes made
// to their timelines. If one is found and the client is connected to the timeline, the whole
// timeline is sent to the client for displaying
void TimelineWriter() {
  Client *c;
  while (true) {
    Timestamp right_now = TimeUtil::GetCurrentTime();
    std::string clients_path = currentProcess.directoryName + "/server_" + currentProcess.procID + "_clients.txt";
    std::ifstream read_clients(clients_path,std::ios::app|std::ios::out|std::ios::in);
    std::string username;

    // Iterates through all local clients
    if (read_clients.is_open()) {
      while (getline(read_clients, username)) {
        int user_index = find_user(username);
        c = &client_db[user_index];
        if (c->connected) {
          std::string timeline_path = currentProcess.directoryName + "/" + username + "_timeline.txt";
          std::ifstream read_timeline(timeline_path,std::ios::app|std::ios::out|std::ios::in);
          std::string line;
          std::vector<std::string> new_posts;
          Message new_msg;

          struct stat buf;
          stat(timeline_path.c_str(), &buf);
          // Checks if timeline file has been modified in the last 30 seconds, if so writes the whole timeline to the stream
          if (difftime(time(0), buf.st_mtime) <= 10 && read_timeline.peek() != std::ifstream::traits_type::eof()) {

            if (read_timeline.is_open()) {
              while (getline(read_timeline, line)) {
                if (isdigit(line[0])) {
                  new_posts.push_back(line);
                }
              }
              read_timeline.close();
            }
            new_msg.set_msg("-------------------------------------");
            c->stream->Write(new_msg);
            for (int i = 0; i < new_posts.size(); i++) {
              new_msg.set_msg(new_posts[i]);
              c->stream->Write(new_msg);
            }
          }
        }
      }
      read_clients.close();
    }
    sleep(10);
  }
}

// Calls the Coordinator through a call to BeginServer which passes the new servers attributes
// so that the Coordinator can store its info in its tables
void CheckIn(std::string coordIP, std::string coordP, std::string id, std::string type, std::string port) {

  std::string login_info = coordIP + ":" + coordP;

  coord_stub_ = std::unique_ptr<COORDService::Stub>(
                    COORDService::NewStub(grpc::CreateChannel(
                        login_info, grpc::InsecureChannelCredentials())));
  
  ServerInfo serverInfo;
  serverInfo.set_port(port);
  serverInfo.set_type(type);
  serverInfo.set_id(id);

  ServerInfo returnInfo;

  ClientContext context;

  Status status = coord_stub_->BeginServer(&context, serverInfo, &returnInfo);
}

// Called by master processes to get the port of the slave process
// from their server in order to properly pass on updates made by clients
void AttachSlave(std::string id) {
  ClientInfo clientInfo;
  clientInfo.set_id(id);

  ServerInfo slaveInfo;
  ClientContext context;

  Status status = coord_stub_->GetSlave(&context, clientInfo, &slaveInfo);

  std::string slavePort = slaveInfo.port();

  std::string login_info = "0.0.0.0:" + slavePort;

  slave_stub_ = std::unique_ptr<SNSService::Stub>(SNSService::NewStub(
               grpc::CreateChannel(
                    login_info, grpc::InsecureChannelCredentials())));
}

// Creates the listening port for the server
void RunServer(std::string port_no) {
  std::string server_address = "0.0.0.0:"+port_no;
  SNSServiceImpl service;

  ServerBuilder builder;
  builder.AddListeningPort(server_address, grpc::InsecureServerCredentials());
  builder.RegisterService(&service);
  std::unique_ptr<Server> server(builder.BuildAndStart());
  std::cout << "Server listening on " << server_address << std::endl;

  server->Wait();
}

// Calls Pulse in the coordinator every 10 seconds in order
// to let the coordinator know that this process is still active
void HeartBeat() {
  ServerInfo serverInfo;
  serverInfo.set_port(currentProcess.portNum);
  serverInfo.set_type(currentProcess.procType);
  serverInfo.set_id(currentProcess.procID);

  None none;

  while(true) {
    ClientContext context;
    coord_stub_->Pulse(&context, serverInfo, &none);
    sleep(10);
  }
}

int main(int argc, char** argv) {
  
  std::string port = "3010";
  std::string coordIP = "0.0.0.0";
  std::string coordP = "3010";
  std::string id = "1";
  std::string type = "master";

  int opt = 0;
  while ((opt = getopt(argc, argv, "i:c:p:d:t:")) != -1){
    switch(opt) {
      case 'i':
          coordIP = optarg;break;
      case 'c':
          coordP = optarg;break;
      case 'p':
          port = optarg;break;
      case 'd':
          id = optarg;break;
      case 't':
          type = optarg;break;
      default:
	  std::cerr << "Invalid Command Line Argument\n";
    }
  }

  std::string dirName = type + "_" + id;
  currentProcess = {dirName, port, type, id, coordP, coordIP};

  // Sends server information to Coordinator
  CheckIn(coordIP, coordP, id, type, port);

  // Creates directory for server
  int check = mkdir(dirName.c_str(), 0777);

  if (type == "master") {
    AttachSlave(id);
  }

  // Thread for sending heart beats every 10 seconds
  std::thread heartbeat(HeartBeat);
  // Thread for checking for timeline changes locally every 30 seconds
  std::thread timelineWrite(TimelineWriter);
  // Thread for running listening port
  std::thread serverRunner(RunServer, port);

  heartbeat.join();
  timelineWrite.join();
  serverRunner.join();

  return 0;
}
