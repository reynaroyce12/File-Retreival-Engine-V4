#include "ClientAppInterface.hpp"

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <filesystem>

ClientAppInterface::ClientAppInterface(std::shared_ptr<ClientProcessingEngine> engine) : engine(engine) {
    // TO-DO implement constructor
}

void ClientAppInterface::readCommands() {
    // TO-DO implement the read commands method

    // color code constants for output messages
    const std::string RED = "\033[31m";
    const std::string GREEN = "\033[32m";
    const std::string YELLOW = "\033[33m";
    const std::string RESET = "\033[0m";

    std::string command;
    
    while (true) {
        std::cout << "> <connect | index | search | quit> ";
        
        // read from command line
        std::getline(std::cin, command);

        // if the command is quit, terminate the program       
        if (command == "quit") {
            // close the program
            break;
        }

        // if the command begins with connect, connect to the given server
        if (command.size() >= 7 && command.substr(0, 7) == "connect") {
            // TO-DO parse command cand call connect on the processing engine

            std::istringstream iss(command);
            std::string action, serverIPAddress, serverPort;

            iss >> action >> serverIPAddress >> serverPort;

            std::cout << "Server IP " << serverIPAddress << std::endl;
            std::cout << "Server Port " << serverPort << std::endl;


            if(serverIPAddress.empty() || serverPort.empty()) {
                std::cout << "Invalid connection command" << std::endl;
                continue;
            }

            if(engine->connect(serverIPAddress, serverPort)) {
                std::cout << "Connection Succesfull!" << std::endl;
            } else {
                std::cout << "Failed to connect to the server!" << std::endl;
            }

            continue;
        }
        
        // if the command begins with index, index the files from the specified directory
        if (command.size() >= 5 && command.substr(0, 5) == "index") {
            // TO-DO parse command and call indexFolder on the processing engine ✅
            // TO-DO print the execution time and the total number of bytes read ✅
            
            std::string folderPath = command.substr(6);

            if (!std::filesystem::exists(folderPath)) {
                std::cout << YELLOW << "Specified folder does not exist!" << RESET << std::endl;
                continue; 
            }

            folderPath.erase(0, folderPath.find_first_not_of(" "));
            folderPath.erase(folderPath.find_last_not_of(" ") + 1); 

            if (folderPath.empty()) {
                std::cout << YELLOW << "Missing folder path for indexing!" << RESET << std::endl;
                continue;
            }

            IndexResult result = engine->indexFolder(folderPath);

            if (result.totalBytesRead == 0) {
                std::cout << YELLOW << "No files found to index!" << RESET << std::endl;
            } else {
                std::cout << "Completed indexing " << result.totalBytesRead << " bytes of data" << std::endl;
                std::cout << "Completed indexing in " << result.executionTime << " seconds" << std::endl;
            }

            continue;
        }

        // if the command begins with search, search for files that matches the query
        if (command.size() >= 6 && command.substr(0, 6) == "search") {
            // TO-DO parse command and call search on the processing engine
            // TO-DO print the execution time and the top 10 search results

            std::string searchQuery = command.substr(7);

            std::vector<std::string> terms;
            std::istringstream stream(searchQuery);
            std::string term;

            while (stream >> term) {
                terms.push_back(term);
            }

            SearchResult result = engine->search(terms);

            std::cout << "\nSearch executed in " << result.executionTime << " seconds." << std::endl;

            if (result.documentFrequencies.empty()) {
                std::cout << YELLOW << "No results found" << RESET << std::endl;
            } else {
                std::cout << "Search Results: " << "( Top 10 out of " << result.documentFrequencies.size() << ")\n"
                          << std::endl;
                for (const auto &docFrequency : result.documentFrequencies) {
                    std::cout << GREEN << docFrequency.documentPath << " (Frequency: " << docFrequency.wordFrequency << ")" << RESET << std::endl;
                }
            }

            continue;
        }

        std::cout << "unrecognized command!" << std::endl;
    }
}