#ifndef _CONCEPT_VECT_H_
#define _CONCEPT_VECT_H_

#include <concepts>

template <typename T>
concept AddableAndSubtractable = requires(T a, T b) {
    { a + b } -> std::same_as<T>; 
    { a - b } -> std::same_as<T>; 
};

template <typename T>
concept MultipliableAndDivisible = requires(T a, T b) {
    { a * b } -> std::same_as<T>;
    { a / b } -> std::same_as<T>;
};

template <typename T>
concept Incrementable = requires(T t) {
    { ++t } -> std::same_as<T&>;
    { t++ } -> std::same_as<T>;
};


template <typename T>
concept Decrementable = requires(T t) {
    { --t } -> std::same_as<T&>;
    { t-- } -> std::same_as<T>;
};


template <typename T>
concept IncrementableAndDecrementable = Incrementable<T> && Decrementable<T>;

#endif