#include "ServerProcessingEngine.hpp"

ServerProcessingEngine::ServerProcessingEngine(std::shared_ptr<IndexStore> store) : store(store) {
    // TO-DO initialize FileRetrievalEngineImpl and gRPC server objects
}

void ServerProcessingEngine::initialize(int serverPort) {
    // TO-DO create and start the gRPC server thread
}

void ServerProcessingEngine::rungRPCServer(int serverPort) {
    // TO-DO build the gRPC server
    // TO-DO register the FileRetrievalEngineImpl service with the gRPC server
    // TO-DO start the gRPC server
}

void ServerProcessingEngine::shutdown() {
    // TO-DO shutdown the gRPC server
    // TO-DO wait for the gRPC server to shutdown
    // TO-DO join the gRPC server thread
}