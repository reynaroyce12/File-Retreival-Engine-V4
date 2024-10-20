package csc435.app;

public class RPCServerWorker implements Runnable {
    private IndexStore store;
    // TO-DO keep track of the gRPC Server object

    public RPCServerWorker(IndexStore store) {
        this.store = store;
    }

    @Override
    public void run() {
        // TO-DO build the gRPC Server
        // TO-DO register the FileRetrievalEngineService service with the gRPC Server
        // TO-DO start the gRPC Server
    }

    public void shutdown() {
        // TO-DO shutdown the gRPC server
        // TO-DO wait for the gRPC server to shutdown
    }
}
