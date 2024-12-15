#ifndef _PROBLEMS_MOSTFREQUENT_H_
#define _PROBLEMS_MOSTFREQUENT_H_

#include "../HashTable/Hash.h"
#include "../HashTable/IDictionary.h"
#include <fstream>

IDictionary<std::string, int> theMostFrequentSubsequences(const std::string &in, int lmin, int lmax) {
    IDictionary<std::string, int> dict;

    for (int i = 0; i < in.length(); ++i) {
        for (int j = lmin; j <= lmax; ++j) {
            if (i + j <= in.length()) {
                std::string word = in.substr(i, j);
                if (dict.containsKey(word)) {
                    dict.get(word) += 1;
                } else {
                    dict.add(word, 1);
                }
            }
        }
    }

    return dict;
}

void FileOutTheMostFrequentSubsequence(const std::string& in, int lmin, int lmax) {
    auto dict = theMostFrequentSubsequences(in, lmin, lmax);

    std::string outFilePath = "D:/LabWorks/S3_Lab3/Tests/Subsequence.txt";

    std::ofstream outFile(outFilePath);

    if (!outFile) {
        throw std::runtime_error("Can't open the file");
    } 

    for (auto it = dict.begin(); it != dict.end(); ++it) {
        auto [key, count] = *it;
        outFile << "Subsequence: " << key << "\tCount: " << count << std::endl; 
    }

    outFile.close();
}

#endif