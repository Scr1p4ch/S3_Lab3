#ifndef _ALPHABET_INDEX_PAGE_H_
#define _ALPHABET_INDEX_PAGE_H_

#include "Move.h"
#include"Rows.h"


class Page {
private:
    ArrSequence<Row> _page;

public:
    Page() = default;

    Page(const Page & other) : _page(other._page) {}
    Page(Page && other) noexcept : _page(Move(other._page)) {}

    Page(const ArrSequence<Row> & other_page) : _page(other_page) {}
    Page(ArrSequence<Row> && other_page) noexcept : _page(Move(other_page)) {}

    Page & operator=(const Page & other) {
        _page = other._page;
        return *this;
    }
    Page & operator=(Page && other) noexcept {
        _page = Move(other._page);
        return *this;
    }

    void addRow(const Row & other_row) {
        _page.append(other_row);
    }

    size_t getRowsCount() const {
        return _page.get_size();
    }

    Row operator[](size_t index) const {
        return _page[index];
    }

};



#endif