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
#include "Problems/AlphabetIndex/HelperFunctions.h"
#include "Problems/AlphabetIndex/AlphabetIndex.h"






template<typename K, typename T>
std::ostream& operator<<(std::ostream& os, const std::pair<K, T>& p) {
    os << p.first << ": " << p.second;
    return os;
}

int main() {

    startBuildingIndex("input.txt", 3, 5);


    return 0;
}