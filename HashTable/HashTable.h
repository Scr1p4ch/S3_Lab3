#ifndef _HASHTABLE_H_
#define _HASHTABLE_H_

#include <functional>
#include "Hash.h"
#include "List.h"

template <typename K, typename T>
class HashTable {
private:
    List<K, T>* buckets;
    size_t num_buckets;
    std::function <size_t(const K&)> hashFunc;

public:
    HashTable(size_t _num_buckets = 8, std::function <size_t(const K&)> _hashFunc = std::function<size_t(const K&)>(std::hash<K>())) : num_buckets(_num_buckets), hashFunc(_hashFunc) {
        buckets = new List<K, T>[num_buckets];
    }

    ~HashTable() {
        for (size_t i = 0; i < num_buckets; ++i) {
            buckets[i].clear();
        }

        delete[] buckets;
    }


    T& operator[](const K& key) {
        List<K, T>* node = buckets[hashFunc(key) & num_buckets].find(key);

        if (nullptr == node) {
            throw std::invalid_argument("Invalid Key");
        }
        else {
            return node->elem;
        }
    }

    HashTable<K, T>& operator=(const HashTable<K, T>& other) {
        if (this == &other) {
            return *this;
        }

        num_buckets = other.num_buckets;
        hashFunc = other.hashFunc;

        for (int i = 0; i < num_buckets; ++i) {
            buckets[i].clear();
        }

        delete[] buckets;

        buckets = new List<K, T>[num_buckets];

        for (size_t i = 0; i < num_buckets; ++i) {
            buckets[i] = other.buckets[i];
        }

        return *this;
    }

     size_t size() {
        size_t size = 0;

        for (size_t i = 0; i < num_buckets; ++i) {
            size += buckets[i].getSize();
        }

        return size;
    }

    bool empty() {
        return size() == 0;
    }

    void insert(const K& key, const T& elem) {
        buckets[hashFunc(key) % num_buckets].append(key, elem);
    }

    void remove(const K& key) {
        buckets[hashFunc(key) % num_buckets].remove(key);
    }

    void print() {
        for (size_t i = 0; i < num_buckets; ++i) {
            std::cout << "Bucket #" << i << ":\n";
            buckets[i].print();
        }
    }

    bool contains(const K& key) const {
        return buckets[hashFunc(key) % num_buckets].find(key) != nullptr;
    }


    class iterator {
    private:
        HashTable<K, T>* ptr;
        Node<K, T>* node;
        size_t idx;
    public:
        iterator(HashTable<K, T>* _ptr, Node<K, T>* _node, size_t _idx) : ptr(_ptr), node(_node), idx(_idx) {}

        iterator& operator++() {
            if (nullptr != node->next) {
                node = node->next;
            }
            else {
                ++idx;

                while (idx != ptr->num_buckets && ptr->buckets[idx].getSize() == 0) {
                    ++idx;
                }

                if (idx == ptr->num_buckets) {
                    node = nullptr;
                }
                else {
                    node = ptr->buckets[idx].head;
                }
            }

            return *this;
        }

        iterator operator++(int) {
            iterator i = *this;
            ++(*this);

            return i;
        }

        bool operator!=(const iterator& i) const {
            return (ptr != i.ptr) || (node != i.node) || (idx != i.idx);
        }

        bool operator==(const iterator& i) const {
            return (ptr == i.ptr) && (node == i.node) && (idx == i.idx);
        }

        T& operator*() {
            return node->elem;
        }

        T* operator->() {
            return &node->elem;
        }
    };

    iterator begin() {
        size_t idx = 0;
        
        while (idx != num_buckets && buckets[idx].getSize() == 0) {
            ++idx;
        }

        iterator i(this, buckets[idx].head, idx);

        return i;
    }

    iterator end() {
        iterator i(this, nullptr, num_buckets);

        return i;
    }

};






#endif