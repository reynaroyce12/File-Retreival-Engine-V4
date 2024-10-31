#include "IndexStore.hpp"

IndexStore::IndexStore() {
    documentMap = {};
    reverseDocumentMap = {};
    termInvertedIndex = {};
}

long IndexStore::putDocument(std::string documentPath, std::string clientId) {

    std::lock_guard<std::mutex> lock(documentMapMutex);

    if(documentMap.contains(documentPath)) {
        return documentMap[documentPath].documentNumber;
    }

    long documentNumber = documentMap.size() +  1;
    documentMap[documentPath] = { documentNumber, clientId };


    // reverse map for getDocument method for constant complexity while retrieving docs
    reverseDocumentMap[documentNumber] = documentPath;

    //    std::cout << "Document Map Contents:" << std::endl;
    //     for (const auto& entry : documentMap) {
    //         const std::string& documentPath = entry.first;
    //         const DocumentInfo& info = entry.second;
    //         std::cout << "Document Path: " << documentPath
    //                   << ", Document Number: " << info.documentNumber
    //                   << ", Client ID: " << info.clientId << std::endl;
    //     }

    return documentNumber;
}

std::string IndexStore::getDocument(long documentNumber) {
    std::string documentPath = "";

    if (reverseDocumentMap.contains(documentNumber)) {
        documentPath = reverseDocumentMap[documentNumber];
    }

    return documentPath;
}

void IndexStore::updateIndex(long documentNumber, const std::unordered_map<std::string, long> &wordFrequencies) {

    std::lock_guard<std::mutex> lock(termInvertedIndexMutex);

    for (const auto &wordFrequency : wordFrequencies) {
        std::string word = wordFrequency.first;
        long frequency = wordFrequency.second;

        auto itr = termInvertedIndex.find(word);
        if (itr != termInvertedIndex.end()) {
            itr->second.push_back({documentNumber, frequency});
        } else {
            termInvertedIndex[word] = {{documentNumber, frequency}};
        }
    }
}

std::vector<DocFreqPair> IndexStore::lookupIndex(std::string term) {

    std::vector<DocFreqPair> results = {};
    if (termInvertedIndex.contains(term)) {
        results = termInvertedIndex[term];
    }

    return std::move(results);
}