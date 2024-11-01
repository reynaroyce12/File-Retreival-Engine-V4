#ifndef INDEX_STORE_H
#define INDEX_STORE_H

#include <string>
#include <vector>
#include <unordered_map>
#include <mutex>

// Data structure that stores a document number and the number of time a word/term appears in the document
struct DocFreqPair {
    long documentNumber;
    long wordFrequency;
};

struct DocumentInfo {
    long documentNumber;
    std::string clientId;
};

struct DocumentResult {
    std::string documentPath;
    std::string clientId;
};


class IndexStore {

    std::unordered_map<std::string, DocumentInfo> documentMap;
    std::unordered_map<long, std::string> reverseDocumentMap;
    std::unordered_map<std::string, std::vector<DocFreqPair>> termInvertedIndex;

    std::mutex documentMapMutex;
    std::mutex termInvertedIndexMutex;

    public:
        // constructor
        IndexStore();

        // default virtual destructor
        virtual ~IndexStore() = default;
        
        long putDocument(std::string documentPath, std::string clientId);
        DocumentResult getDocument(long documentNumber);

        void updateIndex(long documentNumber, const std::unordered_map<std::string, long> &wordFrequencies);
        std::vector<DocFreqPair> lookupIndex(std::string term);
};

#endif