#include <ctime>

#include <google/protobuf/timestamp.pb.h>
#include <google/protobuf/duration.pb.h>

#include <fstream>
#include <iostream>
#include <memory>
#include <thread>
#include <string>
#include <stdlib.h>
#include <unistd.h>
#include <google/protobuf/util/time_util.h>
#include <grpc++/grpc++.h>

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
using grpc::Status;
using csce438::None;
using csce438::ClientInfo;
using csce438::SyncerInfo;
using csce438::ServerInfo;
using csce438::COORDService;

struct clusterProcess {
  std::string port;
  std::string status;
  Timestamp lastPulse;
};

// Stores the master, slave, and synchronizer for each server mapped to the server ID
std::map<int, clusterProcess> master_list;
std::map<int, clusterProcess> slave_list;
std::map<int, clusterProcess> sync_list;

class COORDServiceImpl final : public COORDService::Service {

  // Called by a server to find the port of the server associated with a particular client
  Status GetServer(ServerContext* context, const ClientInfo* clientInfo, ServerInfo* serverInfo) override {
    int serverID = -1;
    serverID = stoi(clientInfo->id()) % 3;

    // Lists are mapped to server IDs for ease of access, so we want IDs between 1 and 3
    if (serverID == 0) {
      serverID = 3;
    }
    if (master_list[serverID].status == "Active") {
      serverInfo->set_port(master_list[serverID].port);
      serverInfo->set_type("MASTER");
    } else {
      serverInfo->set_port(slave_list[serverID].port);
      serverInfo->set_type("SLAVE");
    }
    return Status::OK;
  }

  // Called by a master process to get the port of the slave process in the same server so that it may send changes to it
  Status GetSlave(ServerContext* context, const ClientInfo* clientInfo, ServerInfo* serverInfo) override {
    int serverID = stoi(clientInfo->id());
    serverInfo->set_port(slave_list[serverID].port);
    return Status::OK;
  }

  // Called by a synchronizer to get the port of the synchronizer associated with a particular client
  Status GetFollowSyncer(ServerContext* conext, const ClientInfo* clientInfo, SyncerInfo* syncerInfo) override {
    int syncerID = stoi(clientInfo->id()) % 3;
    if (syncerID == 0) {
      syncerID = 3;
    }
    syncerInfo->set_port(sync_list[syncerID].port);
    return Status::OK;
  }

  // Called by every master, slave, and synchronizer at the beginning of its runtime informing the coordinator
  // of the process's port so that the coordinator can store it
  Status BeginServer(ServerContext* context, const ServerInfo* newServer, ServerInfo* returnServer) override {
    int serverID = stoi(newServer->id());
    std::string serverType = newServer->type();
    std::string serverPort = newServer->port();

    Timestamp first_access = TimeUtil::GetCurrentTime();

    clusterProcess serv = {serverPort, "Active", first_access};

    if (serverType == "master") {
      master_list[serverID] = serv;
    } else if (serverType == "slave") {
      slave_list[serverID] = serv;
    } else {
      sync_list[serverID] = serv;
    }
    return Status::OK;
  }

  // Called by masters and slaves every 10 seconds to let the coordinator know they are still alive
  Status Pulse(ServerContext* context, const ServerInfo* processInfo, None* none) override {
    std::string type = processInfo->type();
    int id = stoi(processInfo->id());

    if (type == "master") {
      master_list[id].lastPulse = TimeUtil::GetCurrentTime();
    } else {
      slave_list[id].lastPulse = TimeUtil::GetCurrentTime();
    }
    return Status::OK;
  }
};

// Opens the listening port for the coordinator
void RunServer(std::string port_no) {
  std::string server_address = "0.0.0.0:"+port_no;
  COORDServiceImpl service;

  ServerBuilder builder;
  builder.AddListeningPort(server_address, grpc::InsecureServerCredentials());
  builder.RegisterService(&service);
  std::unique_ptr<Server> server(builder.BuildAndStart());

  server->Wait();
}

// Iterates through the list of master and slave processes each 10 seconds
// and checks the difference between the current time and the last pulse from that process.
// If the time is greater than 20, that means the process has missed the last two pulses and
// the process is deamed inactive
void CheckPulse() {
  while(true) {
    Timestamp now = TimeUtil::GetCurrentTime();

    std::map<int, clusterProcess>::iterator it = master_list.begin();
    while (it != master_list.end()) {
      Duration time_since_pulse = now - it->second.lastPulse;
      if (TimeUtil::DurationToSeconds(time_since_pulse) > 20) {
        master_list[it->first].status = "Inactive";
      }
      it++;
    }

    it = slave_list.begin();
    while (it != slave_list.end()) {
      Duration time_since_pulse = now - it->second.lastPulse;
      if (TimeUtil::DurationToSeconds(time_since_pulse) > 20) {
        slave_list[it->first].status = "Inactive";
      }
      it++;
    }
    sleep(10);
  } 
}

int main(int argc, char** argv) {
  
  std::string port = "3010";
  int opt = 0;
  while ((opt = getopt(argc, argv, "p:")) != -1){
    switch(opt) {
      case 'p':
          port = optarg;break;
      default:
	  std::cerr << "Invalid Command Line Argument\n";
    }
  }

  // One thread used to create the listening port, while the other checks time since last pulse
  std::thread coordinator(RunServer, port);
  std::thread pulseChecker(CheckPulse);

  coordinator.join();
  pulseChecker.join();

  return 0;
}
