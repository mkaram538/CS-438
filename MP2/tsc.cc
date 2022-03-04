#include <iostream>
#include <string>
#include <unistd.h>
#include <grpc++/grpc++.h>
#include <grpcpp/channel.h>
#include <grpcpp/client_context.h>
#include <grpcpp/create_channel.h>
#include <grpcpp/security/credentials.h>
#include "sns.grpc.pb.h"
#include "client.h"

using grpc::Channel;
using grpc::ClientContext;
using grpc::ClientReader;
using grpc::ClientReaderWriter;
using grpc::ClientWriter;
using grpc::Status;

using csce438::Message;
using csce438::Request;
using csce438::Reply;
using csce438::SNSService;

class Client : public IClient
{
    public:
        Client(const std::string& hname,
               const std::string& uname,
               const std::string& p)
            :hostname(hname), username(uname), port(p)
            {}
    protected:
        virtual int connectTo();
        virtual IReply processCommand(std::string& input);
        virtual void processTimeline();
    private:
        std::string hostname;
        std::string username;
        std::string port;
        std::unique_ptr<SNSService::Stub> stub_;

        // You can have an instance of the client stub
        // as a member variable.
        //std::unique_ptr<NameOfYourStubClass::Stub> stub_;
};

int main(int argc, char** argv) {

    std::string hostname = "localhost";
    std::string username = "default";
    std::string port = "3010";
    int opt = 0;
    while ((opt = getopt(argc, argv, "h:u:p:")) != -1){
        switch(opt) {
            case 'h':
                hostname = optarg;break;
            case 'u':
                username = optarg;break;
            case 'p':
                port = optarg;break;
            default:
                std::cerr << "Invalid Command Line Argument\n";
        }
    }

    Client myc(hostname, username, port);
    // You MUST invoke "run_client" function to start business logic
    myc.run_client();

    return 0;
}

int Client::connectTo()
{
	// ------------------------------------------------------------
    // In this function, you are supposed to create a stub so that
    // you call service methods in the processCommand/porcessTimeline
    // functions. That is, the stub should be accessible when you want
    // to call any service methods in those functions.
    // I recommend you to have the stub as
    // a member variable in your own Client class.
    // Please refer to gRpc tutorial how to create a stub.
	// ------------------------------------------------------------
    auto channel = grpc::CreateChannel("localhost:50051", grpc::InsecureChannelCredentials());
    
    stub_ = SNSService::NewStub(channel);
    
    ClientContext context;
    
    Request login;
    login.set_username(username);
    Reply login_reply;
    
    grpc::Status status = stub_->Login(&context, login, &login_reply);
    
    if (status.ok()) {
        std::cout << "Login Successful" << std::endl;
    } else {
        std::cout << "Login Not Successful?" << std::endl;
    }

    return 1; // return 1 if success, otherwise return -1
}

IReply Client::processCommand(std::string& input)
{
	// ------------------------------------------------------------
	// GUIDE 1:
	// In this function, you are supposed to parse the given input
    // command and create your own message so that you call an
    // appropriate service method. The input command will be one
    // of the followings:
	//
	// FOLLOW <username>
	// UNFOLLOW <username>
	// LIST
    // TIMELINE
	//
	// ------------------------------------------------------------
	
	// ------------------------------------------------------------
	// GUIDE 2:
	// Then, you should create a variable of IReply structure
	// provided by the client.h and initialize it according to
	// the result. Finally you can finish this function by returning
    // the IReply.
	// ------------------------------------------------------------

	// ------------------------------------------------------------
    // HINT: How to set the IReply?
    // Suppose you have "Follow" service method for FOLLOW command,
    // IReply can be set as follow:
    //
    //     // some codes for creating/initializing parameters for
    //     // service method
    //     IReply ire;
    //     grpc::Status status = stub_->Follow(&context, /* some parameters */);
    //     ire.grpc_status = status;
    //     if (status.ok()) {
    //         ire.comm_status = SUCCESS;
    //     } else {
    //         ire.comm_status = FAILURE_NOT_EXISTS;
    //     }
    //
    //      return ire;
    //
    // IMPORTANT:
    // For the command "LIST", you should set both "all_users" and
    // "following_users" member variable of IReply.
    // ------------------------------------------------------------
    
    int space_location = input.find_first_of(" ");
    std::string cmd_username;
    
    IReply ire;
    ClientContext context;
    
    if (space_location < input.length()) {
        cmd_username = input.substr(space_location + 1, input.length() - space_location - 1);
        if (input[0] == 'F') { // FOLLOW <username>
            Request follow_request;
            follow_request.set_username(username);
            follow_request.add_arguments(cmd_username);
            Reply follow_reply;
            
            grpc::Status status = stub_->Follow(&context, follow_request, &follow_reply);
            
            ire.grpc_status = status;
           
            if (status.ok()) {
                ire.comm_status = SUCCESS;
            } else {
                ire.comm_status= FAILURE_NOT_EXISTS;
            }
            
        } else { // UNFOLLOW <username>
            
            Request unfollow_request;
            unfollow_request.set_username(username);
            unfollow_request.add_arguments(cmd_username);
            
            Reply unfollow_reply;
            
            grpc::Status status = stub_->UnFollow(&context, unfollow_request, &unfollow_reply);
            
            ire.grpc_status = status;
           
            if (status.ok()) {
                ire.comm_status = SUCCESS;
            } else {
                ire.comm_status= FAILURE_NOT_EXISTS;
            }
        }
    } else {
        if (input[0] == 'L') { // LIST
            Request list_request;
            
            Reply list_reply;
            
            list_request.set_username(username);
            
            grpc::Status status = stub_->List(&context, list_request, &list_reply);
             
            ire.grpc_status = status;
            for (int i = 0; i < list_reply.all_users_size(); i++) {
                ire.all_users.push_back(list_reply.all_users(i));
            }
            
            for (int j = 0; j < list_reply.following_users_size(); j++) {
                ire.following_users.push_back(list_reply.following_users(j));
            }
            
            if (status.ok()) {
                ire.comm_status = SUCCESS;
            } else {
                ire.comm_status = FAILURE_NOT_EXISTS;
            }
            
        } else { // TIMELINE
        }
    }
    
    return ire;
}

void Client::processTimeline()
{
	// ------------------------------------------------------------
    // In this function, you are supposed to get into timeline mode.
    // You may need to call a service method to communicate with
    // the server. Use getPostMessage/displayPostMessage functions
    // for both getting and displaying messages in timeline mode.
    // You should use them as you did in hw1.
	// ------------------------------------------------------------

    // ------------------------------------------------------------
    // IMPORTANT NOTICE:
    //
    // Once a user enter to timeline mode , there is no way
    // to command mode. You don't have to worry about this situation,
    // and you can terminate the client program by pressing
    // CTRL-C (SIGINT)
	// ------------------------------------------------------------
}
