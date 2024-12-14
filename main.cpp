#include <iostream>

#include "HashTable/Hash.h"
#include "HashTable/HashTable.h"
#include "HashTable/List.h"

int main() {
    

    HashTable<std::string, int> table(16);

    table.insert("bob", 3);
    table.insert("cat", 15);
    table.insert("double", 29);
    

    table.print();

    std::cout << table.contains("bob") << " " << table.contains("who") << std::endl;

    table.remove("bob");

    std::cout << table.contains("bob") << " " << table.contains("who") << std::endl;


    return 0;
}