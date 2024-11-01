#include "FileRetrievalEngineImpl.hpp"
#include <iostream>

FileRetrievalEngineImpl::FileRetrievalEngineImpl(std::shared_ptr<IndexStore> store) : store(store) {
}


grpc::Status FileRetrievalEngineImpl::ComputeIndex(
        grpc::ServerContext* context,
        const fre::IndexReq* request,
        fre::IndexRep* reply)
{

    std::string documentPath = request->document_path();
    std::string clientId = request->client_id();
    std::unordered_map<std::string, long> wordFrequencies;
    for (const auto& [word, frequency] : request->word_frequencies()) {
        wordFrequencies[word] = frequency;
    }

    int documentNumber = store->putDocument(documentPath, clientId);
    store->updateIndex(documentNumber, wordFrequencies);


    return grpc::Status::OK;
}

grpc::Status FileRetrievalEngineImpl::ComputeSearch(
        grpc::ServerContext* context,
        const fre::SearchReq* request,
        fre::SearchRep* reply)
{

    std::unordered_map<long, long> combinedResults;

    std::vector<std::string> terms;
    for (const auto& term : request->terms()) {
        terms.push_back(term);
    }

    bool hasAnd = false;
    auto andPos = std::find(terms.begin(), terms.end(), "AND");
    if (andPos != terms.end()) {
        hasAnd = true;
        terms.erase(andPos);
    }

    for (const auto& term : terms) {
        if(term.empty()) continue;

        auto termResults = store->lookupIndex(term);

        if(termResults.empty()) {
            if (hasAnd) {
                return grpc::Status::OK; 
            } else {
                continue;
            }
        }

        if(combinedResults.empty()) {
            for (const auto& result : termResults) {
                combinedResults[result.documentNumber] = result.wordFrequency;
            }
        } else {
            std::unordered_map<long, long> currentResults;
            for (const auto &result : termResults) {
                if (combinedResults.count(result.documentNumber)) {
                    currentResults[result.documentNumber] = combinedResults[result.documentNumber] + result.wordFrequency;
                }
            }
            combinedResults = std::move(currentResults);
        }
    }

    std::vector<std::pair<long, long>> sortedResults(combinedResults.begin(), combinedResults.end());
    std::sort(sortedResults.begin(), sortedResults.end(), [](auto& a, auto& b) {
        return a.second > b.second; 
    });
    
    int totalSize = sortedResults.size();
    if (sortedResults.size() > 10) {
        sortedResults.resize(10);  
    }


    for (const auto &[documentNumber, frequency] : sortedResults) {
        DocumentResult documentResult = store->getDocument(documentNumber);

        auto *resultEntry = reply->add_search_results();
        
        resultEntry->set_document_path(documentResult.documentPath);
        resultEntry->set_frequency(frequency);
        resultEntry->set_client_id(documentResult.clientId);
    }
    reply->set_total_result(totalSize);
    return grpc::Status::OK;
}

grpc::Status FileRetrievalEngineImpl::RegisterClient (
    grpc::ServerContext* context,
    const fre::RegisterClientReq* request,
    fre::RegisterClientRep* reply) 
{
    int newClientIdNumber = clientIds.size() + 1;
    std::string newClientId = "client_" + std::to_string(newClientIdNumber);

    clientIds[newClientIdNumber] = newClientId;

    reply->set_client_id(newClientId);

    return grpc::Status::OK;
}