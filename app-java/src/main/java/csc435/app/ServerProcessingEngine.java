package csc435.app;

import io.grpc.Grpc;
import io.grpc.InsecureServerCredentials;
import io.grpc.ServerBuilder;

public class ServerProcessingEngine {
    private IndexStore store;
    // TO-DO keep track of the RPCServerWorker object
    // TO-DO keep track of the gRPC server thread

    public ServerProcessingEngine(IndexStore store) {
        this.store = store;
    }

    // TO-DO create and start the gRPC Server
    public void initialize(int serverPort) {
        // TO-DO create the RPCServerWorker object
        // TO-DO create and start the gRPC server thread that runs in the context of the RPCServerWorker object
    }

    // TO-DO shutdown the gRPC Server
    public void shutdown() {
        // TO-DO call shutdown on the RPCServerWorker object
        // TO-DO join the gRPC server thread
    }
}
