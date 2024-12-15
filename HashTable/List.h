#ifndef _HASHTABLE_LIST_H_
#define _HASHTABLE_LIST_H_


template <typename K, typename T>
struct Node {
    K key;
    T elem;
    Node<K, T>* next;

    Node(const K& _key, const T& _elem) : key(_key), elem(_elem), next(nullptr) {}
};

template <typename K, typename T>
struct List {
    Node<K, T>* head;
    size_t size;

    List() : head(nullptr), size() {}

    void append(const K& _key, const T& _elem);
    void remove(const K& _key);
    void clear();

    size_t getSize();

    Node<K, T>* find(const K & _key);
    Node<K, T>* last();

    List<K, T> & operator=(const List<K, T>& other) {
        if (this != &other) {
            clear();

            if (nullptr != other.head) {
                Node<K, T>* node = other.head;
                Node<K, T>* prev = nullptr;

                while (nullptr != node) {
                    Node<K, T>* newNode = new Node<K, T>(node->key, node->elem);
                    if (nullptr == prev) {
                        head = newNode;
                    } else {
                        prev->next = newNode;
                    }


                    prev = newNode;
                    node = node->next;
                }
            }

        }

        return *this;
    }    
// не забыть потом убрать
    void print();
};

template <typename K, typename T>
size_t List<K, T>::getSize() {
    return size;
}

template <typename K, typename T>
void List<K, T>::clear() {
    if (nullptr != head) {
        Node<K, T>* node = head;

        while (nullptr != node) {
            Node<K, T>* tmp = node;
            node = node->next;
            delete tmp;
        }
    }

    head = nullptr;

    size = 0;
}

template <typename K, typename T>
void List<K, T>::append(const K& _key, const T& _elem) {
    Node<K, T>* newNode = new Node<K, T>(_key, _elem);

    if (nullptr == head) {
        head = newNode;
    }
    else {
        Node<K, T>* node = head;

        while (nullptr != node->next) {
            node = node->next;
        }

        node->next = newNode;
    }
    ++size;
}

template <typename K, typename T>
void List<K, T>::remove(const K& _key) {
    if (nullptr != head) {
        Node<K, T>* node = head;
        Node<K, T>* prev = nullptr;

        while (nullptr != node) {
            if (node->key == _key) {
                if (nullptr == prev) {
                    head = node->next;
                }
                else if (nullptr != node->next) {
                    prev->next = node->next;
                }
                else {
                    prev->next = nullptr;
                }

                delete node;
                --size;

                return;
            }

            prev = node;
            node = node->next;
        }
    }
}

template <typename K, typename T>
Node<K, T>* List<K, T>::find(const K& _key) {
    if (nullptr != head) {
        Node<K, T>* node = head;

        while (nullptr != node) {
            if (node->key == _key) {
                return node;
            }

            node = node->next;
        }
    }

    return nullptr;
}

template <typename K, typename T>
Node<K, T>* List<K, T>::last() {
    if (nullptr == head) {
        return nullptr;
    }
    else {
        Node<K, T>* node = head;

        while (nullptr != node->next) {
            node = node->next;
        }

        return node;
    }
}

template <typename K, typename T>
void List<K, T>::print() {
    if (nullptr != head) {
        Node<K, T>* node = head;

        while (nullptr != node) {
            std::cout << node->key << ": " << node->elem << std::endl;

            node = node->next;
        }
    }
}

#endif