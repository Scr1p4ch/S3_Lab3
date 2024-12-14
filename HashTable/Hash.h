#ifndef _HASHTABLE_HASH_H_
#define _HASHTABLE_HASH_H_

#include <string>

class Hash {
public:
    size_t hash(int& a, size_t s) {
        return a % s;
    }

    size_t hash(std::string& str, size_t s) {
        size_t x = 5381;

        for (auto q: str) {
            x = ((x << 5) + x) + (q);
        }

        return x % s;
    }

    size_t hash(char* k, size_t s) {
        char x = *k;
        return x % s;
    }

};


#endif