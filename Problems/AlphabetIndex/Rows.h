#ifndef _ALPHABET_INDEX_ROWS_H_
#define _ALPHABET_INDEX_ROWS_H_

#include <string>
#include <sstream>
#include "../../Utility/FirstLabUtility/Sequence.h"


class Row {
private:
    std::string _row;

public:
    Row() : _row{} {}

    Row(const std::string & other_row) : _row{other_row} {}

    Row(const Row& other) : _row{other._row} {}

    std::string addWord(const std::string & word) {
        _row += word;
        return _row;
    }

    std::string setRow(const std::string & other_row) {
        _row = other_row;
    }

    std::string getRow() {
        return _row;
    }

    const std::string& getRow() const {
        return _row;
    }

};

#endif