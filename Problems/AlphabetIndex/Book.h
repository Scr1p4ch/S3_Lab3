#ifndef _ALPHABET_INDEX_BOOK_H_
#define _ALPHABET_INDEX_BOOK_H_

#include "Page.h"

class Book {
private:
    ArrSequence<Page> _book;

public:
    Book() = default;

    Book(const Book & other) : _book(other._book) {}
    Book(Book && other) noexcept : _book(Move(_book)) {}

    Book & operator=(const Book & other) {
        _book = other._book;
        return *this;
    }

    Book & operator=(Book && other) noexcept{
        _book = Move(other._book);
        return *this;
    }

    Book(const ArrSequence<Page> & other_pages) : _book(other_pages) {}
    Book(ArrSequence<Page> && other_pages) : _book(Move(other_pages)) {}

    size_t getPagesCount() const {
        return _book.get_size();
    }

    Page operator[](size_t index) const {
        return _book[index];
    }
};


#endif