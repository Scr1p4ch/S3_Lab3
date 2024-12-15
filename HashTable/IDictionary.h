#ifndef _IDICTIONARY_H_
#define _IDICTIONARY_H_

#include <utility>

#include "Concepts.h"
#include "HashTable.h"
#include "Hash.h"

template <typename K, typename T, typename hashFunc = std::hash<K>>
class IDictionary {
private:
    HashTable<K, T, hashFunc> hashTable;

public:
    IDictionary(size_t _num_buckets = 8) : hashTable(_num_buckets) {}
    
    size_t getCount() const {
        return hashTable.size();
    }

    size_t getCapacity() const {

        return static_cast<size_t>(0.75 * hashTable.bucketCount()) - hashTable.size();
    }

    T& get(const K& key) {
        return hashTable[key];
    }

    const T& get(const K& key) const {
        return hashTable[key];
    }

    bool containsKey(const K& key) const {
        return hashTable.contains(key);
    }

    void add(K key, T elem) {
        if (hashTable.contains(key)) {
            throw std::invalid_argument("Key exists");
        } else {
            hashTable.insert(key, elem);
        }
    }

    void remove(K key) {
        hashTable.remove(key);
    }

    class Iterator {
    private:
        typename HashTable<K, T, hashFunc>::Iterator it;
    public:
        Iterator(typename HashTable<K, T, hashFunc>::Iterator ittr) : it(ittr) {}

        std::pair<K, T> operator*() const{
            return {(*it).key, (*it).elem};
        }

        Iterator& operator++() {
            ++it;
            return *this;
        }

        Iterator operator++(int) {
            Iterator i = *this;
            ++(*this);
            return i;
        }

        bool operator==(const Iterator& other) const {
            return it == other.it;
        }

        bool operator!=(const Iterator& other) const {
            return it != other.it;
        }   
    };

    Iterator begin() {
        return Iterator(hashTable.begin());
    }

    Iterator end() {
        return Iterator(hashTable.end());
    }
};

#endif