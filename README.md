[![Review Assignment Due Date](https://classroom.github.com/assets/deadline-readme-button-22041afd0340ce965d47ae6ef1cefeee28c7c493a6346c4f15d667ab976d596c.svg)](https://classroom.github.com/a/OSNtM4gR)
## CSC 435 Programming Assignment 5 (Fall 2024)
**Jarvis College of Computing and Digital Media - DePaul University**

**Student**: Reyna Royce (Email: rroyce@depaul.edu)  
**Solution programming language**: C++


## What This Program Does

This project implements a file retrieval engine designed to index text files located in an input folder and execute search operations on the indexed data. The program utilizes a Client-Server architecture, allowing multiple clients to operate simultaneously. Each client has exclusive access to its dataset and transmits a partial index to the server for search operations. Interprocess communication is facilitated through gRPC, with data serialization achieved using Google Protocol Buffers. The program supports the following features:


- Supports multiple clients for indexing and searching operations in a client-server architecture, utilizing gRPC for client-server communication.
- Indexing a directory and reading files within it.
- Searching for terms within indexed files, supporting both single-term queries and AND-based multiple term queries.
- Displays the time taken for indexing and search operations, along with the total bytes read.

#### A Few Points to Consider:

- Server can be started by running the executable passing the port as the command line argument
- Client can be started by running the executable file.
- Search functionality is **case-sensitive** and supports multi-term search using "AND" to find documents containing all the queried words.
- The engine processes only alphanumeric characters and ignores short words (length ≤ 2).
- if the search query is expressed with an AND query, the result will contain all the documents that contain **all** the terms from the AND query. 
- The results are sorted by the number of accumulated occurrences of all terms in each document, and only the top 10 documents are printed. 
- The program uses gRPC for communication between clients and the server, along with Google Protocol Buffers for encoding and transmitting data.

#### The program also assumes that your enviroment already has the following installed and configured:

- GCC 14 C++ Compiler
- CMake (For generating build files)
- Git
- Google Protocol Buffers (protobuf)
- gRPC


## Folder and File Structure
The repository follows the below given folder and file structure:

```
CSC-435-PA5/
├── app-cpp/
│   ├── build/
│   ├── include/
│   │   ├── ClientAppInterface.hpp
│   │   ├── ClientProcessingEngine.hpp
│   │   ├── FileRetrievalEngineImpl.hpp
│   │   ├── IndexStore.hpp
│   │   ├── ServerAppInterface.hpp
│   │   └── ServerProcessingEngine.hpp
│   ├── proto/
│   │   └── file_retrieval_engine.proto/.pb.h/.pb.cc
│   └── src/
│       ├── ClientAppInterface.cpp
│       ├── ClientProcessingEngine.cpp
│       ├── file-retrieval-benchmark.cpp
│       ├── file-retrieval-client.cpp
│       ├── file-retrieval-server.cpp
│       ├── FileRetrievalEngineImpl.cpp
│       ├── IndexStore.cpp
│       ├── ServerAppInterface.cpp
│       └── ServerProcessingEngine.cpp
├── CMakeLists.txt
├── .gitignore
└── README.md
```

## How to build and run the program

### 1. Install Google Protocol Buffers (ProtoBuf) and gRPC libraries
In additon to the GCC  Compiler and CMake installed on your system. You will also need to install Google Protocol Buffers (ProtoBuf) and gRPC libraries and development files. On Ubuntu 24.04 LTS you can install it using the following command

````
sudo apt install pkg-config protobuf-compiler libprotobuf-dev protobuf-compiler-grpc libgrpc++-dev
````

### 1. Creating the `build/` Directory 

Now after the installation proceed to create the build folder inside the project repo. For this, navigate to the `app-cpp` folder and create the build folder by using the command below. This folder will contain the build files generated by CMake.

```` 
cd app-cpp
mkdir build
````

### 2. Run CMake commands to intiate the Build process

Navigate into the `build/` directory and run CMake commands to intialise the project.

````
cd build
cmake ..
````

### 3. Build the program

Now navigate back into the `app-cpp` folder of the reposiory and run the build command.


```
cd ..
cmake --build build/
```


### 4. Execute the program and start the server

Once the build is complete, run the server with the following command from the app-cpp directory.

```
./build/file-retrieval-engine <port>
```

- `<port>` indicates the port number the server uses for its communication

### 5. Start the client

Ensure that the server is running before starting the client. You can run the client by using the below given command

````
./build/file-retrieval-client
````

And for the benchmark program, you can use the following command 

````
./build/file-retrieval-benchmark 192.168.64.4 8080 1 ../../datasets/dataset1_client_server/1_client/client_1
````

which follows the format `./build/file-retrieval-benchmark <server IP> <server port> <number of clients> [<dataset path>]`

#### Example:

`Server`: The below given command will start the server at port 8080

````
./build/file-retrieval-server 8080
> <list | quit>  Server listening on port 8080
````

`Client`: The below given program will start the client program

````
./build/file-retrieval-client
> <connect | index | search | quit>
````


`For connection, indexing and searching`

````
./build/file-retrieval-client 
> <connect | index | search | quit> connect 192.168.64.4 8080
Connected with client ID: client_1
Connection Succesfull!

> <connect | index | search | quit> index ../../datasets/dataset1_client_server/2_clients/client_1 
Completed indexing 68383239 bytes of data
Completed indexing in 3 seconds

> <connect | index | search | quit> search at
Search executed in 0.000834833 seconds.
No results found

> <connect | index | search | quit>
````

`For Benchmark`

```
./build/file-retrieval-benchmark 192.168.64.4 8080 2 ../../datasets/dataset1_client_server/2_clients/client_1 ../../datasets/dataset1_client_server/2_clients/client_2
Connected with client ID: client_1
Connected with client ID: client_2

Completed indexing 134247377 bytes of data
Completed indexing in 3.92178 seconds

Searching "at"
Search completed in 0.000875083 seconds
Search results (top 10 out of 0):

Searching "Worms"
Search completed in 0.000917125 seconds
Search results (top 10 out of 13):
* client_1: ../../datasets/dataset1_client_server/2_clients/client_1/folder4/Document10553.txt: 4
* client_1: ../../datasets/dataset1_client_server/2_clients/client_1/folder3/Document1043.txt: 4
* client_1: ../../datasets/dataset1_client_server/2_clients/client_1/folder3/Document10383.txt: 3
* client_2: ../../datasets/dataset1_client_server/2_clients/client_2/folder7/Document1091.txt: 3
* client_2: ../../datasets/dataset1_client_server/2_clients/client_2/folder7/folderB/Document10991.txt: 2
* client_1: ../../datasets/dataset1_client_server/2_clients/client_1/folder2/Document101.txt: 1
* client_2: ../../datasets/dataset1_client_server/2_clients/client_2/folder5/folderA/Document10689.txt: 1
* client_2: ../../datasets/dataset1_client_server/2_clients/client_2/folder8/Document11116.txt: 1
* client_2: ../../datasets/dataset1_client_server/2_clients/client_2/folder5/folderB/Document10705.txt: 1
* client_1: ../../datasets/dataset1_client_server/2_clients/client_1/folder2/folderA/Document10340.txt: 1

Searching "distortion AND adaptation"
Search completed in 0.000350417 seconds
Search results (top 10 out of 4):
* client_2: ../../datasets/dataset1_client_server/2_clients/client_2/folder7/folderC/Document10998.txt: 6
* client_1: ../../datasets/dataset1_client_server/2_clients/client_1/folder4/Document10516.txt: 3
* client_2: ../../datasets/dataset1_client_server/2_clients/client_2/folder8/Document11157.txt: 2
* client_2: ../../datasets/dataset1_client_server/2_clients/client_2/folder8/Document11159.txt: 2
```
 ------------------------