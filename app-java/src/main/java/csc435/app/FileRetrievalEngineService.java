package csc435.app;

import io.grpc.stub.StreamObserver;

public class FileRetrievalEngineService extends FileRetrievalEngineGrpc.FileRetrievalEngineImplBase {
    private IndexStore store;
    
    public FileRetrievalEngineService(IndexStore store) {
        this.store = store;
    }

    @Override
    public void computeIndex(IndexReq request, StreamObserver<IndexRep> responseObserver) {
        responseObserver.onNext(doIndex(request));
        responseObserver.onCompleted();
    }

    @Override
    public void computeSearch(SearchReq request, StreamObserver<SearchRep> responseObserver) {
        responseObserver.onNext(doSearch(request));
        responseObserver.onCompleted();
    }

    private IndexRep doIndex(IndexReq request) {
        // TO-DO update global index with temporary index received from the request
        // TO-DO send an OK message as the reply

        return IndexRep.newBuilder().build();
    }

    private SearchRep doSearch(SearchReq request) {
        // TO-DO do lookup over the global index given the search term from the request
        // TO-DO send the results as the reply message

        return SearchRep.newBuilder().build();
    }

}
