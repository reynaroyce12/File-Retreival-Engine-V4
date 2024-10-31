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
};

struct SearchResult {
    double executionTime;
    std::vector<DocPathFreqPair> documentFrequencies;
};

class ClientProcessingEngine {
    // TO-DO keep track of the connection ✅
    std::string serverIPAddress;
    std::string serverPort;

    std::shared_ptr<grpc::Channel> channel;
    std::unique_ptr<fre::FileRetrievalEngine::Stub> stub;

    grpc::Status status;
    // fre::SearchReq searchRequest;
    // fre::SearchRep searchReply;

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

        // Utility functions for indexing and search
        std::unordered_map<std::string, long> extractWords(const std::string& fileContent);
};

#endif