#include "ClientProcessingEngine.hpp"

#include <chrono>
#include <fstream>
#include <filesystem>
#include <iostream>
#include <queue>
#include <condition_variable>

ClientProcessingEngine::ClientProcessingEngine() {
    // TO-DO add information to keep track of the gRPC client stub
}

bool ClientProcessingEngine::connect(std::string serverIPAddress, std::string serverPort) {
    // TO-DO create communication channel with the gRPC Server ✅
    // TO-DO create gRPC client stub ✅

    channel = grpc::CreateChannel(serverIPAddress + ":" + serverPort, grpc::InsecureChannelCredentials());
    stub = fre::FileRetrievalEngine::NewStub(channel);

    if (!channel->WaitForConnected(std::chrono::system_clock::now() + std::chrono::seconds(10))) {
        return false;
    }

    std::unique_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    fre::RegisterClientReq registerClientRequest;
    fre::RegisterClientRep registerClientResponse;

    status = stub->RegisterClient(context.get(), registerClientRequest, &registerClientResponse);
    if(status.ok()) {
        clientId = registerClientResponse.client_id();
        std::cout << "Connected with client ID: " << clientId << std::endl; 
        return true;
    } else {
        std::cout << "Failed to register client: " << std::endl;
        return false;
    }

    return true;
}

std::unordered_map<std::string, long> ClientProcessingEngine::extractWords(const std::string& fileContent) {
    std::unordered_map<std::string, long> wordFrequencies;
    std::string currentWord;

    for (char charecter : fileContent) {
        if(std::isalnum(charecter)) {
            currentWord += charecter;
        } else {
            if(currentWord.length() > 2) {
                wordFrequencies[currentWord]++;
            }
            currentWord.clear();
        }
    }

    if(currentWord.length() > 2) {
        wordFrequencies[currentWord]++;
    }
    return wordFrequencies;
}

IndexResult ClientProcessingEngine::indexFolder(std::string folderPath) {
    IndexResult result = {0.0, 0};
    // TO-DO get the start time ✅
    // TO-DO crawl the folder path and extrac all file paths ✅
    // TO-DO for each file extract all alphanumeric terms that are larger than 2 characters
    //       and count their frequencies ✅
    // TO-DO increment the total number of bytes read ✅
    // TO-DO for each file perform a remote procedure call to the server by calling the gRPC client stub ✅
    // TO-DO get the stop time and calculate the execution time ✅
    // TO-DO return the execution time and the total number of bytes read ✅

    std::queue<std::string> fileQueue;
    std::mutex fileQueueMutex;
    std::condition_variable cv;
    std::vector<std::thread> threads;
    bool isDone = false;
    int numWorkerThreads = 6;

    auto indexingStartTime = std::chrono::steady_clock::now();

    for (const auto& file : std::filesystem::recursive_directory_iterator(folderPath)) {
        if (file.is_regular_file()) {
            std::lock_guard<std::mutex> lock(fileQueueMutex);
            fileQueue.push(file.path().string());
        }
    }

    auto worker = [&]() {
        while(true) {
            std::string filePath;

            {
                std::unique_lock<std::mutex> lock(fileQueueMutex);

                // In sleep state until either of the condition is met
                cv.wait(lock, [&]() {
                    return !fileQueue.empty() || isDone; 
                });

                if (fileQueue.empty()) {
                    if (isDone) return;
                    continue;
                }

                filePath = fileQueue.front();
                fileQueue.pop();
            }

            if(!filePath.empty()) {

                std::ifstream file(filePath);
                if (!file) {
                    std::cerr << "Cannot open the file: " << filePath << std::endl;
                    continue;
                }

                std::string fileContent((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
                auto wordFreqeuncies = extractWords(fileContent);

                {
                    std::lock_guard<std::mutex> lock(fileQueueMutex);
                    result.totalBytesRead += fileContent.size();
                }

                std::unique_ptr<grpc::ClientContext> context;
                context = std::make_unique<grpc::ClientContext>();

                {
                    std::lock_guard<std::mutex> lock(indexRequestMutex);
                    fre::IndexReq indexRequest;
                    fre::IndexRep indexReply;
                    indexRequest.set_client_id(clientId);
                    indexRequest.set_document_path(filePath);
                    for (const auto &[word, frequency] : wordFreqeuncies) {
                        // std::cout << "Inserting word: " << word << ", frequency: " << frequency << std::endl;
                        (*indexRequest.mutable_word_frequencies())[word] = frequency;
                    }
                    status = stub->ComputeIndex(context.get(), indexRequest, &indexReply);
                }

            }
        }
    };

    for (int i = 0; i < numWorkerThreads; i++) {
        threads.emplace_back(worker);
    }

    {
        std::lock_guard<std::mutex> lock(fileQueueMutex);
        isDone = true;
    }
    cv.notify_all();

    for(auto& thread : threads) {
        thread.join();
    }

    auto indexingStopTime = std::chrono::steady_clock::now();
    result.executionTime = std::chrono::duration_cast<std::chrono::seconds>(indexingStopTime - indexingStartTime).count();
    
    return result;
}

SearchResult ClientProcessingEngine::search(std::vector<std::string> terms) {
    SearchResult result = {0.0, { }};
    // TO-DO get the start time
    // TO-DO perform a remote procedure call to the server by calling the gRPC client stub
    // TO-DO get the stop time and calculate the execution time
    // TO-DO return the execution time and the top 10 documents and frequencies
    auto searchStartTime = std::chrono::steady_clock::now();

    fre::SearchReq searchRequest;
    fre::SearchRep searchReply;

    for (const auto& term : terms) {
        searchRequest.add_terms(term);
    }

    std::unique_ptr<grpc::ClientContext> context;
    context = std::make_unique<grpc::ClientContext>();
    status = stub->ComputeSearch(context.get(), searchRequest, &searchReply);

    if(!status.ok()) {
        std::cout << "gRPC search call failed" << std::endl;
        return result;
    }

    for (const auto& entry : searchReply.search_results()) {
        result.documentFrequencies.push_back({entry.first, entry.second});
    }

    auto searchStopTime = std::chrono::steady_clock::now();
    auto durationInSeconds = std::chrono::duration_cast<std::chrono::duration<double>>(searchStopTime - searchStartTime).count();
    result.executionTime = durationInSeconds;

    return std::move(result);
}



