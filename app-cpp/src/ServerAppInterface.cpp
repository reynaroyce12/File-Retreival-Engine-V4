#include "ServerAppInterface.hpp"

#include <iostream>
#include <string>

ServerAppInterface::ServerAppInterface(std::shared_ptr<ServerProcessingEngine> engine) : engine(engine) {
    // TO-DO implement constructor
}

void ServerAppInterface::readCommands(int serverPort) {
    // TO-DO implement the read commands method ✅
    std::string command;
    
    while (true) {
        std::cout << "> <quit>" << std::endl;
        std::cout << "> Server running at " << serverPort << std::endl;
        
        // read from command line
        std::getline(std::cin, command);

        // if the command is quit, terminate the program       
        if (command == "quit") {
            engine->shutdown();
            break;
        }

        std::cout << "unrecognized command!" << std::endl;
    }
}