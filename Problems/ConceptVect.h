#ifndef _CONCEPT_VECT_H_
#define _CONCEPT_VECT_H_

#include <concepts>
#include <type_traits>

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

template <typename T>
concept DefaultConstructible = std::is_default_constructible_v<T>;

#endif