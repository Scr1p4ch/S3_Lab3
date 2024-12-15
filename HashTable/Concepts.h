#ifndef _HASHTABLE_CONCEPTS_H_
#define _HASHTABLE_CONCEPTS_H_

#include <concepts>


template <typename T, typename hashFunc>
concept Hashable = requires(T a, hashFunc hash) {
    { hash(a) } -> std::convertible_to<std::size_t>;
};

template <typename T>
concept EqualityComparable = requires(T a, T b) {
    { a == b } -> std::convertible_to<bool>;
    { b == a } -> std::convertible_to<bool>;
    { a != b } -> std::convertible_to<bool>;
    { b != a } -> std::convertible_to<bool>;
};


#endif