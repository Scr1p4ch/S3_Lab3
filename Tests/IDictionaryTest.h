#ifndef _IDICTIONARY_TEST_H_
#define _IDICTIONARY_TEST_H_

#include <iostream>
#include <assert.h>
#include "../HashTable/IDictionary.h"


void IDictionaryTest() {
    IDictionary<int, int> dict_1;
    assert(0 == dict_1.getCount());

    dict_1.add(0, 1);
    dict_1.add(1, 2);
    dict_1.add(2, 3);

    assert(3 == dict_1.getCount());

    assert(1 == dict_1[0]);
    assert(3 == dict_1[2]);
    assert(2 == dict_1.get(1));

    assert(false == dict_1.containsKey(4));
    assert(true == dict_1.containsKey(2));

    assert(3 == dict_1.getCapacity());

    dict_1.remove(2);
    assert(2 == dict_1.getCount());

    auto dict_2(dict_1);

    assert(2 == dict_2.getCount());

    auto dict_3 = dict_2;

    assert(2 == dict_3.getCount());

    assert(true == dict_2.containsKey(1));
    assert(true == dict_3.containsKey(0));
}


#endif