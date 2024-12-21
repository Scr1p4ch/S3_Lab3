#ifndef _ALPHABET_INDEX_HELPERFUNCTIONS_H_
#define _ALPHABET_INDEX_HELPERFUNCTIONS_H_

#include "Rows.h"
#include "Page.h"
#include "Book.h"
#include <sstream>
#include <string>
#include <set>
#include "../../Utility/FirstLabUtility/Sequence.h"
#include "../../HashTable/IDictionary.h"


ArrSequence<std::string> splitWords(const std::string& text) {
    ArrSequence<std::string> words;
    std::string cleanedText = text;

    std::transform(cleanedText.begin(), cleanedText.end(), cleanedText.begin(), [](char c) {
        return std::isalnum(c) ? c : ' ';
    });

    std::istringstream stream(cleanedText);
    std::string word;
    while (stream >> word) {
        words.append(word);
    }
    return words;
}

ArrSequence<Row> rowsCreator(const std::string & text, int row_size) {
    ArrSequence<Row> result;
    ArrSequence<std::string> words = splitWords(text);
    int cnt = 0;
    std::string line;

    for (auto word : words) {
        line = line + word + " ";
        ++cnt;

        if (cnt == row_size) {
            Row item(line);
            result.append(item);
            line.clear();
            cnt = 0;
        }
    }

    if (!line.empty()) {
        Row item2(line);
        result.append(item2);
        line.clear();
        cnt = 0;
    }

    return result;
}

ArrSequence<Page> pageCreator(ArrSequence<Row> & rows, int page_size) {
    ArrSequence<Page> result;
    ArrSequence<Row> buf;
    int cnt = 0;

    for (int i = 0; i < rows.get_size(); ++i) {
        buf.append(rows[i]);
        ++cnt;

        if (cnt == page_size) {
            Page item(buf);
            result.append(item);
            buf.erase(buf.begin(), buf.end());
            cnt = 0;
        }
    }

    if (buf.get_size() != 0) {
        Page item2(buf);
        result.append(std::move(item2));
        buf.erase(buf.begin(), buf.end());
    }

    return result;
}






#endif