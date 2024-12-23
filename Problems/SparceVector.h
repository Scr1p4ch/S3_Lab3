#ifndef _SPARCE_VECTOR_H_
#define _SPARCE_VECTOR_H_

#include "../HashTable/IDictionary.h"
#include "ConceptVect.h"
#include <exception>

template <size_t dim, typename T>
requires AddableAndSubtractable<T>
class SparceVector {
private:
    IDictionary<size_t, T> dict;
    T default_elem;

public:

    SparceVector() requires DefaultConstructible<T> : dict{}, default_elem(T()) {}

    SparceVector(const T & _default_elem) : dict{}, default_elem(_default_elem) {} 

    SparceVector(const SparceVector & other) : dict(other.dict), default_elem(other.default_elem) {}

    SparceVector& operator=(const SparceVector & other) {
        if (this != &other) {
            dict = other.dict;
            default_elem = other.default_elem;
        }

        return *this;
    }

    size_t getDimension() const {
        return dim;
    }

    size_t getRealSize() const {
        return dict.getCount();
    }

    class Interm {
        friend class SparceVector;
        SparceVector* master;
        size_t index;

        Interm(SparceVector* a_master, size_t idx) : master(a_master), index(idx) {}
        T& Provide();
        void Remove();
    public:
        operator T();
        T operator=(const T& elem);
        T operator+=(const T& elem);
        T operator-=(const T& elem);

        T operator*=(const T& elem) requires MultipliableAndDivisible<T>;

        
        T operator/=(const T& elem) requires MultipliableAndDivisible<T>;

        T operator++() requires Incrementable<T>;
        T operator++(int) requires Incrementable<T>;

        T operator--() requires Decrementable<T>;
        T operator--(int) requires Decrementable<T>;
    };

    friend class Interm;

    Interm operator[](size_t idx) {
        if (idx >= dim) {
            throw std::out_of_range("Invalid index");
        }
        return Interm(this, idx);
    }

    SparceVector<dim, T>& operator+=(SparceVector & vect);
    SparceVector<dim, T>& operator-=(SparceVector & vect);

};





template <size_t dim, typename T>
requires AddableAndSubtractable<T>
SparceVector<dim, T>& SparceVector<dim, T>::operator+=(SparceVector & vect) {
    for (size_t i = 0; i < dim; ++i) {
        this->operator[](i) += vect[i];
    }

    return *this;
}

template <size_t dim, typename T>
requires AddableAndSubtractable<T>
SparceVector<dim, T>& SparceVector<dim, T>::operator-=(SparceVector & vect) {
    for (size_t i = 0; i < dim; ++i) {
        this->operator[](i) -= vect[i];
    }

    return *this;
}

template <size_t dim, typename T>
requires AddableAndSubtractable<T>
SparceVector<dim, T> operator+(SparceVector<dim, T>& v1, SparceVector<dim, T>& v2) requires DefaultConstructible<T> {
    SparceVector<dim, T> result;

    for (int i = 0; i < dim; ++i) {
        result[i] = v1[i] + v2[i];
    }
    return result;
}

template <size_t dim, typename T>
requires AddableAndSubtractable<T>
SparceVector<dim, T> SparceVectorSum(T default_elem, SparceVector<dim, T>& v1, SparceVector<dim, T>& v2) {
    SparceVector<dim, T> result(default_elem);

    for (int i = 0; i < dim; ++i) {
        result[i] = v1[i] + v2[i];
    }
    return result;
}

template <size_t dim, typename T>
requires AddableAndSubtractable<T>
SparceVector<dim, T> operator-(SparceVector<dim, T>& v1, SparceVector<dim, T>& v2) requires DefaultConstructible<T> {
    SparceVector<dim, T> result;

    for (int i = 0; i < dim; ++i) {
        result[i] = v1[i] - v2[i];
    }
    return result;
}

template <size_t dim, typename T>
requires AddableAndSubtractable<T>
SparceVector<dim, T> SparceVectorSubtraction(T default_elem ,SparceVector<dim, T>& v1, SparceVector<dim, T>& v2) {
    SparceVector<dim, T> result(default_elem);

    for (int i = 0; i < dim; ++i) {
        result[i] = v1[i] - v2[i];
    }
    return result;
}


template <size_t dim, typename T>
requires AddableAndSubtractable<T>
T SparceVector<dim, T>::Interm::operator=(const T& elem) {
    if (elem == master->default_elem) {
        Remove();
    }
    else {
        Provide() = elem;
    }
    return elem;
}

template <size_t dim, typename T>
requires AddableAndSubtractable<T>
T SparceVector<dim, T>::Interm::operator+=(const T& elem) {
    T& location = Provide();
    location += elem;
    T res = location;

    if (res == master->default_elem) {
        Remove();
    }
    return res;
}

template <size_t dim, typename T>
requires AddableAndSubtractable<T>
T SparceVector<dim, T>::Interm::operator-=(const T& elem) {
    T& location = Provide();
    location -= elem;
    T res = location;

    if (res == master->default_elem) {
        Remove();
    }
    return res;
}

template <size_t dim, typename T>
requires AddableAndSubtractable<T>
T SparceVector<dim, T>::Interm::operator*=(const T& elem) requires MultipliableAndDivisible<T> {
    T& location = Provide();
    location *= elem;
    T res = location;

    if (res == master->default_elem) {
        Remove();
    }
    return res;
}

template <size_t dim, typename T>
requires AddableAndSubtractable<T>
T SparceVector<dim, T>::Interm::operator/=(const T& elem) requires MultipliableAndDivisible<T> {
    T& location = Provide();
    location /= elem;
    T res = location;

    if (res == master->default_elem) {
        Remove();
    }
    return res;
}

template <size_t dim, typename T>
requires AddableAndSubtractable<T>
SparceVector<dim, T>::Interm::operator T() {
    if (master->dict.containsKey(index)) {
        return master->dict[index];
    }
    return master->default_elem;
}

template <size_t dim, typename T>
requires AddableAndSubtractable<T>
T& SparceVector<dim, T>::Interm::Provide() {
    if (master->dict.containsKey(index)) {
        return master->dict[index];
    }

    master->dict.add(index, T());

    return master->dict[index];
}

template <size_t dim, typename T>
requires AddableAndSubtractable<T>
void SparceVector<dim, T>::Interm::Remove() {
    if (master->dict.containsKey(index)) {
        master->dict.remove(index);
    }
    return;
}




template <size_t dim, typename T>
requires AddableAndSubtractable<T>
T SparceVector<dim, T>::Interm::operator++() requires Incrementable<T>{
    T& location = Provide();
    T res = ++location;

    if (location == master->default_elem) {
        Remove();
    }
    return res;
}

template <size_t dim, typename T>
requires AddableAndSubtractable<T>
T SparceVector<dim, T>::Interm::operator++(int) requires Incrementable<T>{
    T& location = Provide();
    T res = location++;

    if (location == master->default_elem) {
        Remove();
    }
    return res;
}

template <size_t dim, typename T>
requires AddableAndSubtractable<T>
T SparceVector<dim, T>::Interm::operator--() requires Decrementable<T>{
    T& location = Provide();
    T res = --location;

    if (location == master->default_elem) {
        Remove();
    }
    return res;
}

template <size_t dim, typename T>
requires AddableAndSubtractable<T>
T SparceVector<dim, T>::Interm::operator--(int) requires Decrementable<T>{
    T& location = Provide();
    T res = location--;

    if (location == master->default_elem) {
        Remove();
    }
    return res;
}

#endif