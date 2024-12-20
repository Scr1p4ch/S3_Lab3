#ifndef _SEQUENCE_H_
#define _SEQUENCE_H_

#include "SeqIterator.h"
#include <algorithm>

template <typename T> class ArrSequence
{
    protected:
        T *data = nullptr;
        size_t size = 0;
        size_t capacity = 0;

    public:
        typedef ArrSequence_iterator<T> iterator;

        ArrSequence();
        ArrSequence(const size_t capacity);
        ArrSequence(const size_t size, T default_value);
        ArrSequence(const std::initializer_list<T> list);
        ArrSequence(const ArrSequence<T> &input_ArrSequence);
        ArrSequence(ArrSequence<T> &&input_ArrSequence);

        ~ArrSequence() noexcept;

        void append(const T &value);
        void prepend(const T &value);
        void pop_back();
        void pop_front();

        iterator insert(iterator position, const T &value);
        iterator insert(iterator position, iterator first, iterator last);
        iterator erase(iterator position);
        iterator erase(iterator first, iterator last);

        void resize(const size_t new_size);
        bool is_empty() const noexcept;

        size_t get_size() const noexcept;

        T &operator[](const size_t index);
        T operator[](const size_t index) const;
        ArrSequence &operator=(const ArrSequence<T> &other);
        ArrSequence &operator=(ArrSequence<T> &&other);

        iterator begin() noexcept;
        iterator end() noexcept;

        iterator cbegin() const noexcept;
        iterator cend() const noexcept;
};

template <typename T> ArrSequence<T>::ArrSequence()
{
    data = new T[1];
    capacity = 1;
}

template <typename T> ArrSequence<T>::ArrSequence(const size_t capacity) : capacity(capacity), size(capacity)
{
    data = new T[capacity];
}

template <typename T> ArrSequence<T>::ArrSequence(const size_t size, T default_value) : size(size)
{
    data = new T[size * 2];
    if (data == nullptr)
        throw std::bad_alloc();
    capacity = size * 2;
    std::fill(data, data + size, default_value);
}

template <typename T> ArrSequence<T>::ArrSequence(const std::initializer_list<T> list)
{
    size = list.size();
    data = new T[size];
    capacity = size;
    std::copy(list.begin(), list.end(), data);
}

template <typename T> ArrSequence<T>::ArrSequence(const ArrSequence<T> &input_ArrSequence)
{
    *this = input_ArrSequence;
}

template <typename T> ArrSequence<T>::ArrSequence(ArrSequence<T> &&input_ArrSequence)
{
    *this = std::move(input_ArrSequence);
}

template <typename T> ArrSequence<T>::~ArrSequence() noexcept
{
    delete[] data;
}

template <typename T> void ArrSequence<T>::append(const T &value)
{
    if (size == capacity)
        resize(capacity * 2);
    data[size++] = value;
}

template <typename T> void ArrSequence<T>::prepend(const T &value)
{
    if (size == capacity)
        resize(capacity * 2);
    std::copy_backward(data, data + size, data + size + 1);
    data[0] = value;
    ++size;
}

template <typename T> void ArrSequence<T>::pop_back()
{
    --size;
}

template <typename T> void ArrSequence<T>::pop_front()
{
    std::copy(data + 1, data + size, data);
    --size;
}

template <typename T> typename ArrSequence<T>::iterator ArrSequence<T>::insert(iterator position, const T &value)
{
    if (position > end() || position < begin())
        throw std::invalid_argument("Invalid position");
    size_t pos_index = position - begin();
    if (size == capacity)
        resize(capacity * 2);
    std::copy_backward(data + pos_index, data + size, data + size + 1);
    ArrSequence<T>::iterator new_pos = iterator(data + pos_index);
    *new_pos = value;
    ++size;
    return new_pos;
}

template <typename T> typename ArrSequence<T>::iterator ArrSequence<T>::insert(iterator position, iterator first, iterator last)
{
    if (first > last || position > end() || position < begin())
        throw std::invalid_argument("Invalid range");
    size_t dist = last - first;
    size_t pos_index = position - begin();
    while (capacity - size < dist)
        resize(capacity * 2);
    std::copy_backward(data + pos_index, data + size, data + size + dist);
    std::copy(first, last, data + pos_index);
    size += dist;
    return iterator(data + pos_index);
}

template <typename T> typename ArrSequence<T>::iterator ArrSequence<T>::erase(iterator position)
{
    if (position > end() || position < begin())
        throw std::invalid_argument("Invalid position");
    std::copy(position + 1, end(), position);
    --size;
    return iterator(position);
}

template <typename T> typename ArrSequence<T>::iterator ArrSequence<T>::erase(iterator first, iterator last)
{
    if (first > last || first < begin() || last > end())
        throw std::invalid_argument("Invalid range");
    size_t dist = last - first;
    std::copy(last, end(), first);
    size -= dist;
    return iterator(first);
}

template <typename T> void ArrSequence<T>::resize(const size_t new_size)
{
    if (new_size < size)
        throw std::runtime_error("Cannot resize to a smaller size");
    T *new_data = new T[new_size];
    std::copy(data, data + size, new_data);
    capacity = new_size;
    delete[] data;
    data = new_data;
}

template <typename T> bool ArrSequence<T>::is_empty() const noexcept
{
    return size == 0;
}

template <typename T> size_t ArrSequence<T>::get_size() const noexcept
{
    return size;
}

template <typename T> T &ArrSequence<T>::operator[](const size_t index)
{
    if (index >= size)
        throw std::out_of_range("Index out of range!");
    return data[index];
}

template <typename T> T ArrSequence<T>::operator[](const size_t index) const
{
    if (index >= size)
        throw std::out_of_range("Index out of range!");
    return data[index];
}

template <typename T> ArrSequence<T> &ArrSequence<T>::operator=(const ArrSequence<T> &other)
{
    if (this == &other)
        return *this;
    delete[] data;
    size = other.size;
    capacity = other.capacity;
    data = new T[capacity];
    if (data == nullptr)
        throw std::bad_alloc();
    std::copy(other.cbegin(), other.cend(), data);
    return *this;
}

template <typename T> ArrSequence<T> &ArrSequence<T>::operator=(ArrSequence<T> &&other)
{
    if (this == &other)
        return *this;
    delete[] data;
    data = other.data;
    size = other.size;
    capacity = other.capacity;
    other.data = nullptr;
    other.size = 0;
    other.capacity = 0;
    return *this;
}

template <typename T> typename ArrSequence<T>::iterator ArrSequence<T>::begin() noexcept
{
    return iterator(data);
}

template <typename T> typename ArrSequence<T>::iterator ArrSequence<T>::end() noexcept
{
    return iterator(data + size);
}

template <typename T> typename ArrSequence<T>::iterator ArrSequence<T>::cbegin() const noexcept
{
    return iterator(data);
}


template <typename T> typename ArrSequence<T>::iterator ArrSequence<T>::cend() const noexcept
{
    return iterator(data + size);
}


#endif