package csc435.app;

import csc435.app.FileRetrievalEngineGrpc.FileRetrievalEngineBlockingStub;

import io.grpc.Grpc;
import io.grpc.InsecureChannelCredentials;
import io.grpc.ManagedChannel;

import java.util.ArrayList;

class IndexResult {
    public double executionTime;
    public long totalBytesRead;

    public IndexResult(double executionTime, long totalBytesRead) {
        this.executionTime = executionTime;
        this.totalBytesRead = totalBytesRead;
    }
}

class DocPathFreqPair {
    public String documentPath;
    public long wordFrequency;

    public DocPathFreqPair(String documentPath, long wordFrequency) {
        this.documentPath = documentPath;
        this.wordFrequency = wordFrequency;
    }
}

class SearchResult {
    public double excutionTime;
    public ArrayList<DocPathFreqPair> documentFrequencies;

    public SearchResult(double executionTime, ArrayList<DocPathFreqPair> documentFrequencies) {
        this.excutionTime = executionTime;
        this.documentFrequencies = documentFrequencies;
    }
}

public class ClientProcessingEngine {
    // TO-DO keep track of the connection
    ManagedChannel channel;
    FileRetrievalEngineBlockingStub stub;

    public ClientProcessingEngine() { }

    public IndexResult indexFiles(String folderPath) {
        IndexResult result = new IndexResult(0.0, 0);

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
    
    public SearchResult searchFiles(ArrayList<String> terms) {
        SearchResult result = new SearchResult(0.0, new ArrayList<DocPathFreqPair>());

        // TO-DO get the start time
        // TO-DO perform a remote procedure call to the server by calling the gRPC client stub
        // TO-DO get the stop time and calculate the execution time
        // TO-DO return the execution time and the top 10 documents and frequencies

        return result;
    }

    public void connect(String serverIP, String serverPort) {
        // TO-DO create communication channel with the gRPC Server
        // TO-DO create gRPC client stub
    }
}
