#ifndef CLIENT_SIDE_ENGINE_H
#define CLIENT_SIDE_ENGINE_H

#include <memory>
#include <string>
#include <vector>

#include <grpc/grpc.h>
#include <grpcpp/channel.h>
#include <grpcpp/client_context.h>
#include <grpcpp/create_channel.h>
#include <grpcpp/security/credentials.h>

#include "proto/file_retrieval_engine.grpc.pb.h"

struct IndexResult {
    double executionTime;
    long totalBytesRead;
};

struct DocPathFreqPair {
    std::string documentPath;
    long wordFrequency;
    std::string clientId;
};

struct SearchResult {
    double executionTime;
    std::vector<DocPathFreqPair> documentFrequencies;
    int totalSize;
};

class ClientProcessingEngine {
    std::string serverIPAddress;
    std::string serverPort;

    std::shared_ptr<grpc::Channel> channel;
    std::unique_ptr<fre::FileRetrievalEngine::Stub> stub;
    grpc::Status status;

    std::mutex indexRequestMutex;
    std::string clientId;

    public:
        // constructor
        ClientProcessingEngine();

        // default virtual destructor
        virtual ~ClientProcessingEngine() = default;
        
        bool connect(std::string serverIPAddress, std::string serverPort);

        IndexResult indexFolder(std::string folderPath);
        
        SearchResult search(std::vector<std::string> terms);

        // Utility function for indexing
        std::unordered_map<std::string, long> extractWords(const std::string& fileContent);
};

#endif