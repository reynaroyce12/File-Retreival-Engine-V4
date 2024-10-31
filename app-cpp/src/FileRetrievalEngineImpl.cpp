#include "FileRetrievalEngineImpl.hpp"
#include <iostream>

FileRetrievalEngineImpl::FileRetrievalEngineImpl(std::shared_ptr<IndexStore> store) : store(store) {
    // TO-DO implement constructor
}


grpc::Status FileRetrievalEngineImpl::ComputeIndex(
        grpc::ServerContext* context,
        const fre::IndexReq* request,
        fre::IndexRep* reply)
{
    // TO-DO extract the document path, client ID and word frequencies from the IndexReq request
    //       get the document number associated with the document path (call putDocument)
    //       update the index store with the word frequencies and the document number
    //       return an acknowledgement as an IndexRep reply

    std::cout << "Client Id Passed: " << request->client_id() << std::endl;

    return grpc::Status::OK;
}

grpc::Status FileRetrievalEngineImpl::ComputeSearch(
        grpc::ServerContext* context,
        const fre::SearchReq* request,
        fre::SearchRep* reply)
{
    // TO-DO extract the terms from the SearchReq request
    //       for each term get the pairs of documents and frequencies from the index store
    //       combine the returned documents and frequencies from all of the specified terms
    //       sort the document and frequency pairs and keep only the top 10
    //       for each document number get from the index store the document path
    //       return the top 10 results as a SearchRep reply

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