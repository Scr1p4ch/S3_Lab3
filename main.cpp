#include <iostream>

#include "HashTable/Hash.h"
#include "HashTable/HashTable.h"
#include "HashTable/List.h"
#include "HashTable/IDictionary.h"
#include "Problems/MostFrequent.h"


#include "Tests/PtrWrapperTest.h"
#include "Tests/DynamicArrayTest.h"
#include "Tests/IDictionaryTest.h"

#include "Utility/FirstLabUtility/Sequence.h"
#include "Problems/AlphabetIndex/Rows.h"
#include "Problems/AlphabetIndex/HelperFunctions.h"
#include "Problems/AlphabetIndex/AlphabetIndex.h"

#include "Problems/SparceVector.h"






template<typename K, typename T>
std::ostream& operator<<(std::ostream& os, const std::pair<K, T>& p) {
    os << p.first << ": " << p.second;
    return os;
}

int main() {

    SparceVector<3, int> a;

    std::cout << a.getRealSize() << std::endl;

    a[0] = 1;
    a[1] = 2;
    a[2] = 4;

    SparceVector<3, int> b;

    b[0] = -4;
    b[1] = -5;
    b[2] = -6;

    a += b;
    for (int i = 0; i < 3; ++i) {
        std::cout << a[i] << " ";
    }

    for (int i = 0; i < 3; ++i) {
        std::cout << b[i] << " ";
    }

    std::cout << std::endl;


}