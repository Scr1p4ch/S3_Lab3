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
    size_t cnt;
    std::function <size_t(const K&)> hashFunc;

public:
    HashTable(size_t _num_buckets = 8, std::function <size_t(const K&)> _hashFunc = std::function<size_t(const K&)>(std::hash<K>())) : num_buckets(_num_buckets), hashFunc(_hashFunc), cnt(0) {
        buckets = new List<K, T>[num_buckets];
    }

    ~HashTable() {
        for (size_t i = 0; i < num_buckets; ++i) {
            buckets[i].clear();
        }

        delete[] buckets;
    }


    T& operator[](const K& key) {
        Node<K, T>* node = buckets[hashFunc(key) % num_buckets].find(key);

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
        return cnt;
    }

    bool empty() {
        return cnt == 0;
    }

    void insert(const K& key, const T& elem) {
        
        buckets[hashFunc(key) % num_buckets].append(key, elem);
        ++cnt;
        if (loadFactor() > 0.75) {
            resize();
        }
    }

    void remove(const K& key) {
        
        buckets[hashFunc(key) % num_buckets].remove(key);
        --cnt;
        if(loadFactor() < 0.25 && num_buckets > 8) {
            resize();
        }
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

    double loadFactor() const {
        return static_cast<double>(cnt) / num_buckets;
    }

    void rehash(size_t new_num_buckets) {
        List<K, T>* new_buckets = new List<K, T>[new_num_buckets];

        for (size_t i = 0; i < num_buckets; ++i) {
            Node<K, T>* node = buckets[i].head;
            while (node != nullptr) {
                new_buckets[hashFunc(node->key) % new_num_buckets].append(node->key, node->elem);
                node = node->next;
            }
        }

        for (int i = 0; i < num_buckets; ++i) {
            buckets[i].clear();
        }

        delete[] buckets;
        buckets = new_buckets;
        num_buckets = new_num_buckets;
    }

    void resize() {
        if (loadFactor() > 0.75) {
            rehash(num_buckets * 2);
        } else if (loadFactor() < 0.25 && num_buckets > 8) {
            rehash(num_buckets / 2);
        }
    }

    class iterator {
    private:
        HashTable<K, T>* ptr;
        Node<K, T>* node;
        size_t idx;
    public:
        iterator(HashTable<K, T>* _ptr, Node<K, T>* _node, size_t _idx) : ptr(_ptr), node(_node), idx(_idx) {}

        iterator& operator++() {
            if (!node) {
                return *this;
            }

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