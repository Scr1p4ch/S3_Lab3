#ifndef _DYNAMIC_ARRAY_TEST_H_
#define _DYNAMIC_ARRAY_TEST_H_

#include "../Utility/DynamicArray.h"
#include <assert.h>

void DynamicArrayConstrTest() {
    DynamicArray<int> arr_1;

    for (int i = 0; i < 16; ++i) {
        arr_1[i] = 10 * (i + 1);
    }

    assert(16 == arr_1.getSize());

    for (int i = 0; i < arr_1.getSize(); ++i) {
        assert(10 * (i + 1) == arr_1[i]);
    }

    DynamicArray<int> arr_2(arr_1);

    assert(arr_1.getSize() == arr_2.getSize());

    for (int i = 0; i < arr_1.getSize(); ++i) {
        assert(arr_1[i] == arr_2[i]);
    }

    DynamicArray<double> arr_3(8);
    assert(8 == arr_3.getSize());
}

void DynamicArrayFuncTest() {
    double* ptr = new double[16];

    for (int i = 0; i < 16; ++i) {
        *(ptr + i) = 1.5 * (i + 2);
    }

    DynamicArray<double> arr;

    assert(16 == arr.getSize());
    for (int i = 0; i < 16; ++i) {
        arr[i] = ptr[i];
    }

    for (int i = 0; i < 16; ++i) {
        assert(1.5 * (i + 2) == arr[i]);
    }

    arr.resize(32);
    assert(32 == arr.getSize());

    for (int i = 0; i < 16; ++i) {
        assert(ptr[i] == arr[i]);
    }

    DynamicArray<int> arr_2(8);

    for (int i = 0; i < 8; ++i) {
        arr_2[i] = 10 * (i + 1);
    }

    assert(8 == arr_2.getSize());
    assert(7 == arr_2.getCurrent());

    arr_2[3] = 15;
    assert(7 == arr_2.getCurrent());

    auto arr_3 = arr_2;

    arr_2.resize(64);
    assert(7 == arr_2.getCurrent());
    assert(64 == arr_2.getSize());

    for (int i = 0; i <= arr_2.getCurrent(); ++i) {
        assert(arr_3[i] == arr_2[i]);
    }
}


void DynamicArrayTest() {
    DynamicArrayConstrTest();
    DynamicArrayFuncTest();
}


#endif