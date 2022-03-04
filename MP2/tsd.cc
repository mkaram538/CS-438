#include <ctime>

#include <google/protobuf/timestamp.pb.h>
#include <google/protobuf/duration.pb.h>
#include <map>
#include <vector>
#include <fstream>
#include <iostream>
#include <memory>
#include <string>
#include <stdlib.h>
#include <unistd.h>
#include <google/protobuf/util/time_util.h>
#include <grpc++/grpc++.h>

#include "sns.grpc.pb.h"

using google::protobuf::Timestamp;
using google::protobuf::Duration;
using grpc::Server;
using grpc::ServerBuilder;
using grpc::ServerContext;
using grpc::ServerReader;
using grpc::ServerReaderWriter;
using grpc::ServerWriter;
using grpc::Status;
using csce438::Message;
using csce438::Request;
using csce438::Reply;
using csce438::SNSService;

class SNSServiceImpl final : public SNSService::Service {
  
  std::map<std::string, std::vector<std::string>> user_map;
  
  Status List(ServerContext* context, const Request* request, Reply* reply) override {
    // ------------------------------------------------------------
    // In this function, you are to write code that handles 
    // LIST request from the user. Ensure that both the fields
    // all_users & following_users are populated
    // ------------------------------------------------------------
    
    std::string username = request->username();
    
    std::map<std::string, std::vector<std::string>>::iterator it;
    
    for (it = user_map.begin(); it != user_map.end(); ++it) {
      reply->add_all_users(it->first);
    }
    
    std::map<std::string, std::vector<std::string>>::iterator user_it;
    user_it = user_map.find(username);
    
    if (user_it == user_map.end()) {
      return Status::CANCELLED; 
    }
    
    std::vector<std::string> follower_list = user_map[username];
    
    for (int i = 0; i < follower_list.size(); i++) {
      reply->add_following_users(follower_list[i]);
    }
    
    return Status::OK;
  }

  Status Follow(ServerContext* context, const Request* request, Reply* reply) override {
    // ------------------------------------------------------------
    // In this function, you are to write code that handles 
    // request from a user to follow one of the existing
    // users
    // ------------------------------------------------------------
    
    std::string follow_username = request->arguments(0);
    std::string follower_username = request->username();
    
    std::map<std::string, std::vector<std::string>>::iterator it;
    it = user_map.find(follower_username);
    
    if (it != user_map.end()) {
      user_map[follower_username].push_back(follow_username);
      
      return Status::OK; 
    } else {
      return Status::CANCELLED;
    }
  }

  Status UnFollow(ServerContext* context, const Request* request, Reply* reply) override {
    // ------------------------------------------------------------
    // In this function, you are to write code that handles 
    // request from a user to unfollow one of his/her existing
    // followers
    // ------------------------------------------------------------
    
    std::string unfollow_username = request->arguments(0);
    std::string unfollower_username = request->username();
    
    std::map<std::string, std::vector<std::string>>::iterator it;
    it = user_map.find(unfollower_username);
    
    if (it != user_map.end()) {
      std::vector<std::string> follower_list = user_map[unfollower_username];
      
      for (std::vector<std::string>::iterator vec_it = follower_list.begin(); vec_it != follower_list.end(); vec_it++) {
        if (*vec_it == unfollow_username) {
          
          follower_list.erase(vec_it);
          user_map[unfollower_username] = follower_list;
          return Status::OK;
        }
      }
      return Status::CANCELLED; 
    } else {
      return Status::CANCELLED;
    }
  }
  
  Status Login(ServerContext* context, const Request* request, Reply* reply) override {
    // ------------------------------------------------------------
    // In this function, you are to write code that handles 
    // a new user and verify if the username is available
    // or already taken
    // ------------------------------------------------------------
    std::string username = request->username();
    
    std::map<std::string, std::vector<std::string>>::iterator it;
    it = user_map.find(username);
    
    if (it != user_map.end()) {
      std::cout << it->first << std::endl;
      return Status::CANCELLED;
    } else {
      std::vector<std::string> new_follower_list;
      user_map[username] = new_follower_list;
      
      std::map<std::string, std::vector<std::string>>::iterator it;
      
      return Status::OK;
    }
  }

  Status Timeline(ServerContext* context, ServerReaderWriter<Message, Message>* stream) override {
    // ------------------------------------------------------------
    // In this function, you are to write code that handles 
    // receiving a message/post from a user, recording it in a file
    // and then making it available on his/her follower's streams
    // ------------------------------------------------------------
    return Status::OK;
  }

};

void RunServer(std::string port_no) {
  // ------------------------------------------------------------
  // In this function, you are to write code 
  // which would start the server, make it listen on a particular
  // port number.
  // ------------------------------------------------------------
  
  std::string server_address("0.0.0.0:50051");
  SNSServiceImpl service;
  
  ServerBuilder builder;
  
  int port_num = stoi(port_no);
  
  builder.AddListeningPort(server_address, grpc::InsecureServerCredentials(), &port_num);
  builder.RegisterService(&service);
  
  std::unique_ptr<Server> server(builder.BuildAndStart());
  
  server->Wait();
}

int main(int argc, char** argv) {
  
  std::string port = "3010";
  int opt = 0;
  while ((opt = getopt(argc, argv, "p:")) != -1){
    switch(opt) {
      case 'p':
          port = optarg;
          break;
      default:
	         std::cerr << "Invalid Command Line Argument\n";
    }
  }
  RunServer(port);
  return 0;
}
