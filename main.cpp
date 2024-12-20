#include <iostream>

#include "HashTable/Hash.h"
#include "HashTable/HashTable.h"
#include "HashTable/List.h"
#include "HashTable/IDictionary.h"
#include "Problems/MostFrequent.h"


#include "Tests/PtrWrapperTest.h"
#include "Tests/DynamicArrayTest.h"
//#include "Tests/SequenceTest.h"

#include "Utility/FirstLabUtility/Sequence.h"
#include "Problems/AlphabetIndex/Rows.h"






template<typename K, typename T>
std::ostream& operator<<(std::ostream& os, const std::pair<K, T>& p) {
    os << p.first << ": " << p.second;
    return os;
}

int main() {

    ArrSequence<int> a;

    std::cout << a.get_size() << std::endl;

    a.append(13);
    a.append(15);

    a.prepend(17);
    a.pop_back();
    a.pop_front();

    std::cout << a.get_size() << std::endl;

    for (int i : a) {
        std:: cout << i << " ";
    }

    std::cout << std::endl;
    
    return 0;
}