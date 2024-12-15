#include <iostream>

#include "HashTable/Hash.h"
#include "HashTable/HashTable.h"
#include "HashTable/List.h"
#include "HashTable/IDictionary.h"
#include "Problems/MostFrequent.h"
#include "Utility/Sequence.h"

#include "AlphabetIndex/AlphabetIndex.h"


template<typename K, typename T>
std::ostream& operator<<(std::ostream& os, const std::pair<K, T>& p) {
    os << p.first << ": " << p.second;
    return os;
}

int main() {
    
    startBuildingAlphabetIndex("InputText.txt", 4, 3);

    




    return 0;
}