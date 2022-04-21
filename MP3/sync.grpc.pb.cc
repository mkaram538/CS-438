// Generated by the gRPC C++ plugin.
// If you make any local change, they will be lost.
// source: sync.proto

#include "sync.pb.h"
#include "sync.grpc.pb.h"

#include <functional>
#include <grpcpp/impl/codegen/async_stream.h>
#include <grpcpp/impl/codegen/async_unary_call.h>
#include <grpcpp/impl/codegen/channel_interface.h>
#include <grpcpp/impl/codegen/client_unary_call.h>
#include <grpcpp/impl/codegen/client_callback.h>
#include <grpcpp/impl/codegen/message_allocator.h>
#include <grpcpp/impl/codegen/method_handler.h>
#include <grpcpp/impl/codegen/rpc_service_method.h>
#include <grpcpp/impl/codegen/server_callback.h>
#include <grpcpp/impl/codegen/server_callback_handlers.h>
#include <grpcpp/impl/codegen/server_context.h>
#include <grpcpp/impl/codegen/service_type.h>
#include <grpcpp/impl/codegen/sync_stream.h>
namespace csce438 {

static const char* SYNCService_method_names[] = {
  "/csce438.SYNCService/NewClient",
  "/csce438.SYNCService/NewFollower",
  "/csce438.SYNCService/TimelineUpdate",
};

std::unique_ptr< SYNCService::Stub> SYNCService::NewStub(const std::shared_ptr< ::grpc::ChannelInterface>& channel, const ::grpc::StubOptions& options) {
  (void)options;
  std::unique_ptr< SYNCService::Stub> stub(new SYNCService::Stub(channel, options));
  return stub;
}

SYNCService::Stub::Stub(const std::shared_ptr< ::grpc::ChannelInterface>& channel, const ::grpc::StubOptions& options)
  : channel_(channel), rpcmethod_NewClient_(SYNCService_method_names[0], options.suffix_for_stats(),::grpc::internal::RpcMethod::NORMAL_RPC, channel)
  , rpcmethod_NewFollower_(SYNCService_method_names[1], options.suffix_for_stats(),::grpc::internal::RpcMethod::NORMAL_RPC, channel)
  , rpcmethod_TimelineUpdate_(SYNCService_method_names[2], options.suffix_for_stats(),::grpc::internal::RpcMethod::NORMAL_RPC, channel)
  {}

::grpc::Status SYNCService::Stub::NewClient(::grpc::ClientContext* context, const ::csce438::NewClientInfo& request, ::csce438::Empty* response) {
  return ::grpc::internal::BlockingUnaryCall< ::csce438::NewClientInfo, ::csce438::Empty, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(channel_.get(), rpcmethod_NewClient_, context, request, response);
}

void SYNCService::Stub::async::NewClient(::grpc::ClientContext* context, const ::csce438::NewClientInfo* request, ::csce438::Empty* response, std::function<void(::grpc::Status)> f) {
  ::grpc::internal::CallbackUnaryCall< ::csce438::NewClientInfo, ::csce438::Empty, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(stub_->channel_.get(), stub_->rpcmethod_NewClient_, context, request, response, std::move(f));
}

void SYNCService::Stub::async::NewClient(::grpc::ClientContext* context, const ::csce438::NewClientInfo* request, ::csce438::Empty* response, ::grpc::ClientUnaryReactor* reactor) {
  ::grpc::internal::ClientCallbackUnaryFactory::Create< ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(stub_->channel_.get(), stub_->rpcmethod_NewClient_, context, request, response, reactor);
}

::grpc::ClientAsyncResponseReader< ::csce438::Empty>* SYNCService::Stub::PrepareAsyncNewClientRaw(::grpc::ClientContext* context, const ::csce438::NewClientInfo& request, ::grpc::CompletionQueue* cq) {
  return ::grpc::internal::ClientAsyncResponseReaderHelper::Create< ::csce438::Empty, ::csce438::NewClientInfo, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(channel_.get(), cq, rpcmethod_NewClient_, context, request);
}

::grpc::ClientAsyncResponseReader< ::csce438::Empty>* SYNCService::Stub::AsyncNewClientRaw(::grpc::ClientContext* context, const ::csce438::NewClientInfo& request, ::grpc::CompletionQueue* cq) {
  auto* result =
    this->PrepareAsyncNewClientRaw(context, request, cq);
  result->StartCall();
  return result;
}

::grpc::Status SYNCService::Stub::NewFollower(::grpc::ClientContext* context, const ::csce438::FollowerInfo& request, ::csce438::Empty* response) {
  return ::grpc::internal::BlockingUnaryCall< ::csce438::FollowerInfo, ::csce438::Empty, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(channel_.get(), rpcmethod_NewFollower_, context, request, response);
}

void SYNCService::Stub::async::NewFollower(::grpc::ClientContext* context, const ::csce438::FollowerInfo* request, ::csce438::Empty* response, std::function<void(::grpc::Status)> f) {
  ::grpc::internal::CallbackUnaryCall< ::csce438::FollowerInfo, ::csce438::Empty, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(stub_->channel_.get(), stub_->rpcmethod_NewFollower_, context, request, response, std::move(f));
}

void SYNCService::Stub::async::NewFollower(::grpc::ClientContext* context, const ::csce438::FollowerInfo* request, ::csce438::Empty* response, ::grpc::ClientUnaryReactor* reactor) {
  ::grpc::internal::ClientCallbackUnaryFactory::Create< ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(stub_->channel_.get(), stub_->rpcmethod_NewFollower_, context, request, response, reactor);
}

::grpc::ClientAsyncResponseReader< ::csce438::Empty>* SYNCService::Stub::PrepareAsyncNewFollowerRaw(::grpc::ClientContext* context, const ::csce438::FollowerInfo& request, ::grpc::CompletionQueue* cq) {
  return ::grpc::internal::ClientAsyncResponseReaderHelper::Create< ::csce438::Empty, ::csce438::FollowerInfo, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(channel_.get(), cq, rpcmethod_NewFollower_, context, request);
}

::grpc::ClientAsyncResponseReader< ::csce438::Empty>* SYNCService::Stub::AsyncNewFollowerRaw(::grpc::ClientContext* context, const ::csce438::FollowerInfo& request, ::grpc::CompletionQueue* cq) {
  auto* result =
    this->PrepareAsyncNewFollowerRaw(context, request, cq);
  result->StartCall();
  return result;
}

::grpc::Status SYNCService::Stub::TimelineUpdate(::grpc::ClientContext* context, const ::csce438::TimelineInfo& request, ::csce438::Empty* response) {
  return ::grpc::internal::BlockingUnaryCall< ::csce438::TimelineInfo, ::csce438::Empty, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(channel_.get(), rpcmethod_TimelineUpdate_, context, request, response);
}

void SYNCService::Stub::async::TimelineUpdate(::grpc::ClientContext* context, const ::csce438::TimelineInfo* request, ::csce438::Empty* response, std::function<void(::grpc::Status)> f) {
  ::grpc::internal::CallbackUnaryCall< ::csce438::TimelineInfo, ::csce438::Empty, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(stub_->channel_.get(), stub_->rpcmethod_TimelineUpdate_, context, request, response, std::move(f));
}

void SYNCService::Stub::async::TimelineUpdate(::grpc::ClientContext* context, const ::csce438::TimelineInfo* request, ::csce438::Empty* response, ::grpc::ClientUnaryReactor* reactor) {
  ::grpc::internal::ClientCallbackUnaryFactory::Create< ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(stub_->channel_.get(), stub_->rpcmethod_TimelineUpdate_, context, request, response, reactor);
}

::grpc::ClientAsyncResponseReader< ::csce438::Empty>* SYNCService::Stub::PrepareAsyncTimelineUpdateRaw(::grpc::ClientContext* context, const ::csce438::TimelineInfo& request, ::grpc::CompletionQueue* cq) {
  return ::grpc::internal::ClientAsyncResponseReaderHelper::Create< ::csce438::Empty, ::csce438::TimelineInfo, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(channel_.get(), cq, rpcmethod_TimelineUpdate_, context, request);
}

::grpc::ClientAsyncResponseReader< ::csce438::Empty>* SYNCService::Stub::AsyncTimelineUpdateRaw(::grpc::ClientContext* context, const ::csce438::TimelineInfo& request, ::grpc::CompletionQueue* cq) {
  auto* result =
    this->PrepareAsyncTimelineUpdateRaw(context, request, cq);
  result->StartCall();
  return result;
}

SYNCService::Service::Service() {
  AddMethod(new ::grpc::internal::RpcServiceMethod(
      SYNCService_method_names[0],
      ::grpc::internal::RpcMethod::NORMAL_RPC,
      new ::grpc::internal::RpcMethodHandler< SYNCService::Service, ::csce438::NewClientInfo, ::csce438::Empty, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(
          [](SYNCService::Service* service,
             ::grpc::ServerContext* ctx,
             const ::csce438::NewClientInfo* req,
             ::csce438::Empty* resp) {
               return service->NewClient(ctx, req, resp);
             }, this)));
  AddMethod(new ::grpc::internal::RpcServiceMethod(
      SYNCService_method_names[1],
      ::grpc::internal::RpcMethod::NORMAL_RPC,
      new ::grpc::internal::RpcMethodHandler< SYNCService::Service, ::csce438::FollowerInfo, ::csce438::Empty, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(
          [](SYNCService::Service* service,
             ::grpc::ServerContext* ctx,
             const ::csce438::FollowerInfo* req,
             ::csce438::Empty* resp) {
               return service->NewFollower(ctx, req, resp);
             }, this)));
  AddMethod(new ::grpc::internal::RpcServiceMethod(
      SYNCService_method_names[2],
      ::grpc::internal::RpcMethod::NORMAL_RPC,
      new ::grpc::internal::RpcMethodHandler< SYNCService::Service, ::csce438::TimelineInfo, ::csce438::Empty, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(
          [](SYNCService::Service* service,
             ::grpc::ServerContext* ctx,
             const ::csce438::TimelineInfo* req,
             ::csce438::Empty* resp) {
               return service->TimelineUpdate(ctx, req, resp);
             }, this)));
}

SYNCService::Service::~Service() {
}

::grpc::Status SYNCService::Service::NewClient(::grpc::ServerContext* context, const ::csce438::NewClientInfo* request, ::csce438::Empty* response) {
  (void) context;
  (void) request;
  (void) response;
  return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
}

::grpc::Status SYNCService::Service::NewFollower(::grpc::ServerContext* context, const ::csce438::FollowerInfo* request, ::csce438::Empty* response) {
  (void) context;
  (void) request;
  (void) response;
  return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
}

::grpc::Status SYNCService::Service::TimelineUpdate(::grpc::ServerContext* context, const ::csce438::TimelineInfo* request, ::csce438::Empty* response) {
  (void) context;
  (void) request;
  (void) response;
  return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
}


}  // namespace csce438
