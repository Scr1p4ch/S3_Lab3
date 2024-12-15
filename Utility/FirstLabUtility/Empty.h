#ifndef _EMPTY_H_
#define _EMPTY_H_

template <typename T>
struct Empty {
    struct Derived : public T {
        char smth;
    };

    static constexpr bool value = (sizeof(Derived) == sizeof(char));
};

template <typename T>
constexpr bool is_empty_value = Empty<T>::value;


#endif