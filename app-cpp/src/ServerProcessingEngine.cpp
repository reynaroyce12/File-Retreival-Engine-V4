#include "ServerProcessingEngine.hpp"
#include <string> 

ServerProcessingEngine::ServerProcessingEngine(std::shared_ptr<IndexStore> store) : store(store), service(store) {
    // TO-DO initialize FileRetrievalEngineImpl and gRPC server objects ✅
}

void ServerProcessingEngine::initialize(int serverPort) {
    // TO-DO create and start the gRPC server thread ✅
    serverThread = std::thread(&ServerProcessingEngine::rungRPCServer, this, serverPort);
}

void ServerProcessingEngine::rungRPCServer(int serverPort) {
    // TO-DO build the gRPC server ✅
    // TO-DO register the FileRetrievalEngineImpl service with the gRPC server ✅
    // TO-DO start the gRPC server ✅
    // std::cout << "Hi I'm " << serverPort << " from server!" << std::endl;

    serverAddress = "0.0.0.0";

    grpc::ServerBuilder builder;
    builder.AddListeningPort(serverAddress + ":" + std::to_string(serverPort), grpc::InsecureServerCredentials());

    builder.SetMaxReceiveMessageSize(-1); 
    builder.SetMaxSendMessageSize(-1);   
    
    builder.RegisterService((grpc::Service*) &service);
    RPCServer = builder.BuildAndStart();
    RPCServer->Wait();
}

void ServerProcessingEngine::shutdown() {
    // TO-DO shutdown the gRPC server ✅
    // TO-DO wait for the gRPC server to shutdown ✅
    // TO-DO join the gRPC server thread ✅
    RPCServer->Shutdown();
    RPCServer->Wait();
    serverThread.join();

    std::cout << "Server terminated Succesfully!" << std::endl;
}