#ifndef _SEQUENCE_ITERATOR_H_
#define _SEQUENCE_ITERATOR_H_

#include <cstddef>
#include <iterator>
#include <iostream>

template <typename T> class ArrSequence;


template <typename T> class ArrSequence_iterator
{
    private:
        T *p;

    public:
        friend class ArrSequence<T>;
        using difference_type = std::ptrdiff_t;
        using value_type = std::remove_cv_t<T>;
        using pointer = T *;
        using const_pointer = const T *;
        using reference = T &;
        using iterator_category = std::random_access_iterator_tag;

        ArrSequence_iterator(T *p);
        ArrSequence_iterator(const ArrSequence_iterator &it);

        ArrSequence_iterator<T> operator+(const size_t &num) const noexcept;
        ArrSequence_iterator<T> operator-(const size_t &num) const noexcept;

        size_t operator-(const ArrSequence_iterator &other) const;
        bool operator!=(const ArrSequence_iterator &other) const noexcept;
        bool operator==(const ArrSequence_iterator &other) const noexcept;
        bool operator>(const ArrSequence_iterator &other) const noexcept;
        bool operator<(const ArrSequence_iterator &other) const noexcept;

        T &operator*() const noexcept;

        ArrSequence_iterator &operator++() noexcept;
        ArrSequence_iterator &operator--() noexcept;
};

template <typename T> ArrSequence_iterator<T>::ArrSequence_iterator(T *p) : p(p)
{
}

template <typename T> ArrSequence_iterator<T>::ArrSequence_iterator(const ArrSequence_iterator &it)
{
    p = it.p;
}

template <typename T> ArrSequence_iterator<T> ArrSequence_iterator<T>::operator+(const size_t &num) const noexcept
{
    return ArrSequence_iterator<T>(p + num);
}

template <typename T> ArrSequence_iterator<T> ArrSequence_iterator<T>::operator-(const size_t &num) const noexcept
{
    return ArrSequence_iterator<T>(p - num);
}

template <typename T> size_t ArrSequence_iterator<T>::operator-(const ArrSequence_iterator &other) const
{
    if (*this < other)
        throw std::invalid_argument("Cannot subtract iterators from different ArrSequences");
    return p - other.p;
}

template <typename T> bool ArrSequence_iterator<T>::operator!=(const ArrSequence_iterator &other) const noexcept
{
    return p != other.p;
}

template <typename T> bool ArrSequence_iterator<T>::operator==(const ArrSequence_iterator &other) const noexcept
{
    return p == other.p;
}

template <typename T> bool ArrSequence_iterator<T>::operator>(const ArrSequence_iterator &other) const noexcept
{
    return p > other.p;
}


template <typename T> bool ArrSequence_iterator<T>::operator<(const ArrSequence_iterator &other) const noexcept
{
    return p < other.p;
}


template <typename T> T &ArrSequence_iterator<T>::operator*() const noexcept
{
    return *p;
}

template <typename T> ArrSequence_iterator<T> &ArrSequence_iterator<T>::operator++() noexcept
{
    ++p;
    return *this;
}

template <typename T> ArrSequence_iterator<T> &ArrSequence_iterator<T>::operator--() noexcept
{
    --p;
    return *this;
}

#endif 