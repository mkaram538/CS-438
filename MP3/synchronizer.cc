#include <ctime>

#include <google/protobuf/timestamp.pb.h>
#include <google/protobuf/duration.pb.h>

#include <fstream>
#include <iostream>
#include <memory>
#include <string>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <thread>
#include <google/protobuf/util/time_util.h>
#include <grpc++/grpc++.h>

#include "coord.grpc.pb.h"
#include "sync.grpc.pb.h"

using google::protobuf::Timestamp;
using google::protobuf::Duration;
using google::protobuf::util::TimeUtil;
using grpc::Channel;
using grpc::ClientContext;
using grpc::ClientReader;
using grpc::ClientReaderWriter;
using grpc::ClientWriter;
using grpc::Server;
using grpc::ServerBuilder;
using grpc::ServerContext;
using grpc::ServerReader;
using grpc::ServerReaderWriter;
using grpc::ServerWriter;
using grpc::Status;

using csce438::ClientInfo;
using csce438::SyncerInfo;
using csce438::ServerInfo;
using csce438::COORDService;

using csce438::NewClientInfo;
using csce438::FollowerInfo;
using csce438::Empty;
using csce438::TimelineInfo;
using csce438::SYNCService;

struct Synchonizer {
  std::string portNum;
  std::string syncID;
  std::string coordPort;
  std::string coordIP;
  std::string slave_dir;
  std::string master_dir;
};

Synchonizer currentSync;

// Stores the created coordinator stub globally
std::unique_ptr<COORDService::Stub> coord_stub_;

class SYNCServiceImpl final : public SYNCService::Service {

  // Adds the new client from a different server the file containing a list of 
  // all clients for a particular server when a new client logs in
  Status NewClient(ServerContext* context, const NewClientInfo* clientInfo, Empty* empty) override {
    std::string client_id = clientInfo->client_id();
    std::string client_filename = "/all_clients.txt";

    std::string masterPath = currentSync.master_dir + client_filename;
    std::string slavePath = currentSync.slave_dir + client_filename;

    std::ofstream master_client_file(masterPath,std::ios::app|std::ios::out|std::ios::in);
    if (master_client_file.is_open()) {
      master_client_file << client_id << "\n";
      master_client_file.close();
    }

    std::ofstream slave_client_file(slavePath,std::ios::app|std::ios::out|std::ios::in);
    if (slave_client_file.is_open()) {
      slave_client_file << client_id << "\n";
      slave_client_file.close();
    }

    return Status::OK;
  }

  // Adds a new follower to the *_followers.txt file of the followed client, then compiles all
  // of the followed client's messages to add to the follower's timeline
  Status NewFollower(ServerContext* context, const FollowerInfo* followerInfo, Empty* empty) override {
    std::string follower_id = followerInfo->follower_id();
    std::string followed_id = followerInfo->followed_id();

    std::string follower_filename = "/" + followed_id + "_followers.txt";

    std::string masterPath = currentSync.master_dir + follower_filename;
    std::string slavePath = currentSync.slave_dir + follower_filename;

    std::ofstream master_follow_file(masterPath,std::ios::app|std::ios::out|std::ios::in);
    if (master_follow_file.is_open()) {
      master_follow_file << follower_id << "\n";
      master_follow_file.close();
    }

    std::ofstream slave_follow_file(slavePath,std::ios::app|std::ios::out|std::ios::in);
    if (slave_follow_file.is_open()) {
      slave_follow_file << follower_id << "\n";
      slave_follow_file.close();
    }

    ClientInfo clientInfo;
    clientInfo.set_id(follower_id);
    SyncerInfo syncerInfo;
    ClientContext context_1;

    // Creates a stub to the follower's server's synchronizer
    Status status = coord_stub_->GetFollowSyncer(&context_1, clientInfo, &syncerInfo);

    std::string login_info = "0.0.0.0:" + syncerInfo.port();
    std::unique_ptr<SYNCService::Stub> sync_stub_ = std::unique_ptr<SYNCService::Stub>(
                    SYNCService::NewStub(grpc::CreateChannel(
                        login_info, grpc::InsecureChannelCredentials())));

    ClientContext context_2;
    Empty empty_1;
    TimelineInfo followTimeline;
    followTimeline.set_follower_id(follower_id);

    std::string followed_feed_path = currentSync.slave_dir + "/" + followed_id + "_feed.txt";

    std::ifstream read_feed(followed_feed_path,std::ios::app|std::ios::out|std::ios::in);

    // Iterates through the followed client's feed adding all messages to the entry list
    // of followTimeline
    std::string line;
    int counter = 0;
    if (read_feed.is_open()) {
      while (getline(read_feed, line)) {
        if (isdigit(line[0])) {
          followTimeline.add_entries(line);
          counter++;
        }
      }
    }
    if (counter > 0) {
      // Sends list of entries to be added to the follower's timeline to TimelineUpdate
      // which will do so
      sync_stub_->TimelineUpdate(&context_2, followTimeline, &empty_1);
    }
    return Status::OK;
  }

  // Receives a list of new entries to add to a client's timeline, these new entries
  // based on the order they were posted originally
  Status TimelineUpdate(ServerContext* context, const TimelineInfo* timeline, Empty* empty) override {
    std::string follower_id = timeline->follower_id();

    std::string follower_filename = "/" + follower_id + "_timeline.txt";

    std::string masterPath = currentSync.master_dir + follower_filename;
    std::string slavePath = currentSync.slave_dir + follower_filename;

    std::vector<std::string> new_timeline;

    std::ifstream read_timeline(slavePath,std::ios::app|std::ios::out|std::ios::in);

    // Adds all of the entries from the old timeline into a vector
    std::string line;
    if (read_timeline.is_open()) {
      while (getline(read_timeline, line)) {
        if (isdigit(line[0])) {
          new_timeline.push_back(line);
        }
      }
      read_timeline.close();
    }
    
    // Iterates through all of the new entries being added to the timeline
    for (std::string message : timeline->entries()) {
      if (new_timeline.size() == 0) {
        new_timeline.push_back(message);
      } else {
        // Parses entry to find the time since the new entry was posted
        std::size_t time_size = message.find("::");
        std::string string_time = message.substr(0, time_size);
        Timestamp message_time;
        TimeUtil::FromString(string_time, &message_time);

        std::vector<std::string>::reverse_iterator it = new_timeline.rbegin();

        bool inserted = false;
        // Iterates through the timeline in reverse order from most recent to least
        // since new updates will be recent
        while (it  != new_timeline.rend()) {
          Timestamp after_time;
          Timestamp before_time;

          // Finds the time since the current entry in the timeline
          std::string after_string_time = (*it).substr(0, time_size);

          TimeUtil::FromString(after_string_time, &after_time);

          Duration after_to_current = after_time - message_time;
          
          // If the current timeline entry was made more recently than the new entry
          // move to the next most recent entry. Repeat until it was made before and enter
          // the new entry after the current entry. If the end is reached, insert new entry
          // at the front as the oldest message
          if (TimeUtil::DurationToSeconds(after_to_current) < 0) {
            if (it == new_timeline.rbegin()) {
              new_timeline.push_back(message);
            } else {
              new_timeline.insert(it.base()+1, message);
            }
            inserted = true;
            break;
          } else {
            it++;
          }
        }
        if (!inserted) {
          new_timeline.insert(new_timeline.begin(), message);
        }
      } 
    }

    // Overwrite the timeline files with the new entries
    std::ofstream master_write_timeline(masterPath, std::ios::out|std::ios::trunc);
    for (int i = 0; i < new_timeline.size(); i++) {
      master_write_timeline << new_timeline[i] << "\n";
    }
    master_write_timeline.close();

    std::ofstream slave_write_timeline(slavePath, std::ios::out|std::ios::trunc);
    for (int i = 0; i < new_timeline.size(); i++) {
      slave_write_timeline << new_timeline[i] << "\n";
    }
    slave_write_timeline.close();

    return Status::OK;
  }
};

// Creates the listening port for the synchronizer
void updateLocal() {
  std::string sync_address = "0.0.0.0:"+currentSync.portNum;
  SYNCServiceImpl service;

  ServerBuilder builder;
  builder.AddListeningPort(sync_address, grpc::InsecureServerCredentials());
  builder.RegisterService(&service);
  std::unique_ptr<Server> server(builder.BuildAndStart());

  server->Wait();
}

// Finds the ID of new client in the current synchronizer's server by checking the
// server client file and sending the ID to the other two synchronizers
void newClient() {
  std::string local_clients_path = currentSync.slave_dir + "/server_" + currentSync.syncID + "_clients.txt";
  std::ifstream read_clients(local_clients_path,std::ios::app|std::ios::out|std::ios::in);

  std::string new_client;

  std::vector<std::string> all_clients;

  if (read_clients.is_open()) {
    while (getline(read_clients, new_client)) {
      all_clients.push_back(new_client);
    }
    read_clients.close();
  }
  
  // Gets the most recent entry in the clients list which is the one most recently added
  // This also means that only one client can be added in a particular server every 30 seconds
  new_client = all_clients[all_clients.size() - 1];

  ClientInfo clientInfo_a;
  ClientInfo clientInfo_b;

  SyncerInfo syncerInfo_a;
  SyncerInfo syncerInfo_b;

  if (currentSync.syncID == "1") {
    clientInfo_a.set_id("2");
    clientInfo_b.set_id("3");
  } else if (currentSync.syncID == "2") {
    clientInfo_a.set_id("1");
    clientInfo_b.set_id("3");
  } else {
    clientInfo_a.set_id("1");
    clientInfo_b.set_id("2");
  }

  ClientContext context_a;
  ClientContext context_b;

  // Calls the coordinator to get the ports of the other two synchronizers
  Status status_a = coord_stub_->GetFollowSyncer(&context_a, clientInfo_a, &syncerInfo_a);
  Status status_b = coord_stub_->GetFollowSyncer(&context_b, clientInfo_b, &syncerInfo_b);

  // Sends both synchronizers the ID of the new client so that they may add it
  // to their server's list of all clients
  std::string login_info_a = "0.0.0.0:" + syncerInfo_a.port();

  std::unique_ptr<SYNCService::Stub> sync_stub_a_ = std::unique_ptr<SYNCService::Stub>(
                    SYNCService::NewStub(grpc::CreateChannel(
                        login_info_a, grpc::InsecureChannelCredentials())));

  NewClientInfo newClientInfo;
  newClientInfo.set_client_id(new_client);

  Empty empty_1;
  Empty empty_2;

  ClientContext context_a1;
  ClientContext context_b1;

  Status status_1 = sync_stub_a_->NewClient(&context_a1, newClientInfo, &empty_1);

  std::string login_info_b = "0.0.0.0:" + syncerInfo_b.port();

  std::unique_ptr<SYNCService::Stub> sync_stub_b_ = std::unique_ptr<SYNCService::Stub>(
                    SYNCService::NewStub(grpc::CreateChannel(
                        login_info_b, grpc::InsecureChannelCredentials())));

  Status status_2 = sync_stub_b_->NewClient(&context_b1, newClientInfo, &empty_2);
}

// Gets the ID of the newly followed client by getting the last entry in the follower's
// following file, then send the new follower information to the server where
// the followed client belongs
void newFollowing(std::string clientID) {
  std::string following_path = currentSync.slave_dir + "/" + clientID + "_following.txt";
  std::ifstream read_following(following_path,std::ios::app|std::ios::out|std::ios::in);

  std::string following;

  std::vector<std::string> all_following;

  // Gets most recent follow from following file
  if (read_following.is_open()) {
    while (getline(read_following, following)) {
      all_following.push_back(following);
    }
    read_following.close();
  }

  following = all_following[all_following.size() - 1];

  ClientInfo clientInfo;
  clientInfo.set_id(following);

  SyncerInfo syncerInfo;
  ClientContext context;

  // Gets port of the followed client's synchronizer
  Status status = coord_stub_->GetFollowSyncer(&context, clientInfo, &syncerInfo);

  std::string login_info = "0.0.0.0:" + syncerInfo.port();
  std::unique_ptr<SYNCService::Stub> sync_stub_ = std::unique_ptr<SYNCService::Stub>(
                    SYNCService::NewStub(grpc::CreateChannel(
                        login_info, grpc::InsecureChannelCredentials())));

  // Sends synchronizer the information about the new follower
  FollowerInfo followerInfo;
  followerInfo.set_follower_id(clientID);
  followerInfo.set_followed_id(following);

  Empty empty;
  ClientContext new_context;

  Status new_status = sync_stub_->NewFollower(&new_context, followerInfo, &empty);
}

// Gets a list of all of the posts made in the last 30 seconds by a particular client
// then calls its follower's synchronizers to update the follower's timeline
void newPost(std::string clientID) {
  std::string feed_path = currentSync.slave_dir + "/" + clientID + "_feed.txt";
  std::ifstream read_feed(feed_path,std::ios::app|std::ios::out|std::ios::in);
  std::string message;

  std::vector<std::string> new_posts;

  // Parsing every entry in the client's feed to get the ones made in the last
  // 30 seconds. These are stored
  Timestamp right_now = TimeUtil::GetCurrentTime();
  if (read_feed.is_open()) {
    while (getline(read_feed, message)) {
      std::size_t time_size = message.find("::");
      std::string string_time = message.substr(0, time_size);
      Timestamp message_time;
      TimeUtil::FromString(string_time, &message_time);

      Duration time_since_post = right_now - message_time;
      if (TimeUtil::DurationToSeconds(time_since_post) <= 10) {
        new_posts.push_back(message);
      }
    }
    read_feed.close();
  }
  TimelineInfo timelineInfo;

  for (int i = 0; i < new_posts.size(); i++) {
    timelineInfo.add_entries(new_posts[i]);
  }
  std::string followers_path = currentSync.slave_dir + "/" + clientID + "_followers.txt";
  std::ifstream read_followers(followers_path,std::ios::app|std::ios::out|std::ios::in);

  std::string follower;
  // Iterates through all of the current clients followers, calling the coordinator
  // to get their synchronizer's port then calling that synchronizer to update their timeline
  if (read_followers.is_open()) {
    while (getline(read_followers, follower)) {
      ClientInfo clientInfo;
      ClientContext coord_context;
      ClientContext sync_context;
      SyncerInfo syncerInfo;
      Empty empty;
      clientInfo.set_id(follower);
      coord_stub_->GetFollowSyncer(&coord_context, clientInfo, &syncerInfo);
      std::string login_info = "0.0.0.0:" + syncerInfo.port();
      std::unique_ptr<SYNCService::Stub> sync_stub_ = std::unique_ptr<SYNCService::Stub>(
              SYNCService::NewStub(grpc::CreateChannel(
                 login_info, grpc::InsecureChannelCredentials())));
      timelineInfo.set_follower_id(follower);
      sync_stub_->TimelineUpdate(&sync_context, timelineInfo, &empty);
    }
  }
}

// Iterates across the files that the master controls in the server and looks for any changes
// made in the last 30 seconds. If one is found the appropriate function is called that
// will disseminate these changes to the other synchronizers
void informOthers() {

  while (true) {
    std::string local_clients_path = currentSync.slave_dir + "/server_" + currentSync.syncID + "_clients.txt";
    std::ifstream clients(local_clients_path,std::ios::app|std::ios::out|std::ios::in);
    struct stat buf;
    // First checks if a client has been assigned to this server in the last 30 seconds
    stat(local_clients_path.c_str(), &buf);
    if (difftime(time(0), buf.st_mtime) <= 10 && clients.peek() != std::ifstream::traits_type::eof()) {
      newClient();
    }

    std::string client;

    // Iterates through all clients assigned to this server and checks if their following list has
    // changed or if they have posted anything in the last 30 seconds
    if (clients.is_open()) {
      while (getline(clients, client)) {
        
        std::string following_path = currentSync.slave_dir + "/" + client + "_following.txt";
        std::ifstream followers(following_path,std::ios::app|std::ios::out|std::ios::in);

        stat(following_path.c_str(), &buf);
        if (difftime(time(0), buf.st_mtime) <= 10 && followers.peek() != std::ifstream::traits_type::eof()) {
          newFollowing(client);
        }

        std::string feed_path = currentSync.slave_dir + "/" + client + "_feed.txt";
        std::ifstream posts(feed_path,std::ios::app|std::ios::out|std::ios::in);

        stat(feed_path.c_str(), &buf);
        if (difftime(time(0), buf.st_mtime) <= 10 && posts.peek() != std::ifstream::traits_type::eof()) {
          newPost(client);
        }
      }
    }

    //Waits 30 seconds until next loop
    sleep(10);
  }
}

// Begins by registering the Synchronizer with its server in the Coordinator, does this through
// the BeginServer Coordinator call
void startSyncer() {
  std::string login_info = currentSync.coordIP + ":" + currentSync.coordPort;

  coord_stub_ = std::unique_ptr<COORDService::Stub>(
                    COORDService::NewStub(grpc::CreateChannel(
                        login_info, grpc::InsecureChannelCredentials())));

  ServerInfo serverInfo;
  serverInfo.set_port(currentSync.portNum);
  serverInfo.set_type("synchronizer");
  serverInfo.set_id(currentSync.syncID);

  ServerInfo returnInfo;
  
  ClientContext context;

  Status status = coord_stub_->BeginServer(&context, serverInfo, &returnInfo);

  // One thread monitors local files for changes then creates stubs to the
  // other synchronizers to disseminate changes

  // Other thread creates a listening port and waits for follower updates or timeline
  // updates from other syncers

  std::thread Updater(updateLocal);
  std::thread Checker(informOthers);

  Updater.join();
  Checker.join();
}

int main(int argc, char** argv) {
  
  std::string port = "3010";
  std::string coordIP = "0.0.0.0";
  std::string coordP = "3010";
  std::string id = "1";

  int opt = 0;
  while ((opt = getopt(argc, argv, "i:c:p:d:")) != -1){
    switch(opt) {
      case 'i':
          coordIP = optarg;break;
      case 'c':
          coordP = optarg;break;
      case 'p':
          port = optarg;break;        
      case 'd':
          id = optarg;break;
      default:
	  std::cerr << "Invalid Command Line Argument\n";
    }
  }
  std::string master_dir = "master_" + id;
  std::string slave_dir = "slave_" + id;
  currentSync = {port, id, coordP, coordIP, slave_dir, master_dir};

  startSyncer();

  return 0;
}