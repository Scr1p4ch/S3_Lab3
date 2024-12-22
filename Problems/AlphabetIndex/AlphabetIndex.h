#ifndef _ALPHABETINDEX_ALPHA_H_
#define _ALPHABETINDEX_ALPHA_H_

#include <iostream>
#include <fstream>
#include "HelperFunctions.h"


class AlphabetIndex {
private:
    IDictionary<std::string, ArrSequence<int>> index;

public:
    AlphabetIndex() = default;

    AlphabetIndex(Book & inBook) {
        for (int numPage = 0; numPage < inBook.getPagesCount(); ++numPage) {
            Page page = inBook[numPage];

            for (int numRow = 0; numRow < page.getRowsCount(); ++numRow) {
                Row row = page[numRow];
                std::istringstream rowStream(row.getRow());
                std::string word;

                while (rowStream >> word) {
                    if (index.containsKey(word)) {
                        ArrSequence<int> & pages = index.get(word);
                        pages.append(numPage + 1);
                    }
                    else {
                        ArrSequence<int> buf(1, numPage + 1);
                        index.add(word, buf);
                    }
                }
            }
        }
    }

    IDictionary<std::string, ArrSequence<int>> getIndex() const {
        return index;
    }

    void IDictionaryToFile(const std::string & outFilePath) {
        std::ofstream outputFile(outFilePath);

        if (!outputFile) {
            throw std::runtime_error("Can not open the file");
        }

        for (auto it = index.begin(); it != index.end(); ++it) {
            const std::pair<std::string, ArrSequence<int>> & entry = *it;
            outputFile << entry.first << ": ";
            for (size_t i = 0; i < entry.second.get_size(); ++ i) {
                outputFile << entry.second[i];
                if (i < entry.second.get_size() - 1) {
                    outputFile << ", ";
                }
            }
            outputFile << std::endl;
        }
        outputFile.close();
    }
};



AlphabetIndex buildIndexFromFile(const std::string & inFilePath, int pageSize, const std::string & outFilePath, int rowSize) {
    
    std::ifstream inputFile(inFilePath);

    if (!inputFile) {
        throw std::runtime_error("Can't open the file");
    }

    std::ostringstream textBuffer;
    textBuffer << inputFile.rdbuf();
    inputFile.close();
    std::string inputText = textBuffer.str();

    /*std::transform(inputText.begin(),inputText.end(), inputText.begin(), [](char & c) {
        if (!std::isalnum(c) && c != '\'') {
            return ' ';
        }
        return static_cast<char>(std::tolower(c));
    });
    */

    for (char & ch : inputText) {
        if (ch == '\n' || ch == '\t' || !(std::isalnum(ch)) && ch != '\'') {
            ch = ' ';
        }
        else
        {
            ch = static_cast<char>(std::tolower(ch));
        }
    }

    ArrSequence<Row> rows = rowsCreator(inputText, rowSize);

    ArrSequence<Page> pages = pageCreator(rows, pageSize);

    Book item(pages);

    std::string bookOutputFilePath = "D:/LabWorks/S3_Lab3/Tests/bookOutput.txt";
    std::ofstream bookOutputFile(bookOutputFilePath);

    if (!bookOutputFile) {
        throw std::runtime_error("Can't open the file");
    }

    bookOutputFile << "Book:\n";
    for (int i = 0; i < item.getPagesCount(); ++i) {
        bookOutputFile << "Page " << i + 1 << ":\n";

        Page page = item[i];

        for (int j = 0; j < item[i].getRowsCount(); ++j) {
            bookOutputFile << page[j].getRow() << '\n';
        }
        bookOutputFile << '\n';
    }

    bookOutputFile.close();
    AlphabetIndex index(item);

    index.IDictionaryToFile(outFilePath);
    return index;
}

void startBuildingIndex(std::string fileName, int pageSize, int rowSize) {
    std::string RealFileName = fileName;
    std::string outputFilePath = "D:/LabWorks/S3_Lab3/Tests/output.txt";

    buildIndexFromFile(RealFileName, pageSize, outputFilePath, rowSize);
}

#endif