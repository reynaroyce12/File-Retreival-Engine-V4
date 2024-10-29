#include <iostream>
#include <memory>

#include "IndexStore.hpp"
#include "ServerProcessingEngine.hpp"
#include "ServerAppInterface.hpp"

int main(int argc, char** argv)
{
    // TO-DO change server port to a non-privileged port from argv[1] ✅
    int serverPort = std::atoi(argv[1]);

    std::shared_ptr<IndexStore> store = std::make_shared<IndexStore>();
    std::shared_ptr<ServerProcessingEngine> engine = std::make_shared<ServerProcessingEngine>(store);
    std::shared_ptr<ServerAppInterface> interface = std::make_shared<ServerAppInterface>(engine);

    // create a thread that runs the gRPC server
    engine->initialize(serverPort);

    // read commands from the user
    interface->readCommands(serverPort);

    return 0;
}