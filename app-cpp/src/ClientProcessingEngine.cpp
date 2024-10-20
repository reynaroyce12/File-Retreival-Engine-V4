#include "ClientProcessingEngine.hpp"

ClientProcessingEngine::ClientProcessingEngine() {
    // TO-DO add information to keep track of the gRPC client stub
}

IndexResult ClientProcessingEngine::indexFolder(std::string folderPath) {
    IndexResult result = {0.0, 0};
    // TO-DO get the start time
    // TO-DO crawl the folder path and extrac all file paths
    // TO-DO for each file extract all alphanumeric terms that are larger than 2 characters
    //       and count their frequencies
    // TO-DO increment the total number of bytes read
    // TO-DO for each file perform a remote procedure call to the server by calling the gRPC client stub
    // TO-DO get the stop time and calculate the execution time
    // TO-DO return the execution time and the total number of bytes read

    return result;
}

SearchResult ClientProcessingEngine::search(std::vector<std::string> terms) {
    SearchResult result = {0.0, { }};
    // TO-DO get the start time
    // TO-DO perform a remote procedure call to the server by calling the gRPC client stub
    // TO-DO get the stop time and calculate the execution time
    // TO-DO return the execution time and the top 10 documents and frequencies

    return std::move(result);
}

void ClientProcessingEngine::connect(std::string serverIP, std::string serverPort) {
    // TO-DO create communication channel with the gRPC Server
    // TO-DO create gRPC client stub
}

