#include "ServerAppInterface.hpp"

#include <iostream>
#include <string>

ServerAppInterface::ServerAppInterface(std::shared_ptr<ServerProcessingEngine> engine) : engine(engine) {

}

void ServerAppInterface::readCommands(int serverPort) {

    std::string command;
    
    while (true) {
        std::cout << "Server running at " << serverPort << std::endl;
        std::cout << "> <quit>" << std::endl;
        
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