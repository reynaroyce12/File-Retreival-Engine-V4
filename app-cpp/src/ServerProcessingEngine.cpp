#include "ServerProcessingEngine.hpp"
#include <string> 

ServerProcessingEngine::ServerProcessingEngine(std::shared_ptr<IndexStore> store) : store(store), service(store) {
}

void ServerProcessingEngine::initialize(int serverPort) {
    serverThread = std::thread(&ServerProcessingEngine::rungRPCServer, this, serverPort);
}

void ServerProcessingEngine::rungRPCServer(int serverPort) {
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
    std::cout << "Server termination initiated..." << std::endl;
    
    RPCServer->Shutdown();
    RPCServer->Wait();
    serverThread.join();

    std::cout << "Server terminated Succesfully!" << std::endl;
}