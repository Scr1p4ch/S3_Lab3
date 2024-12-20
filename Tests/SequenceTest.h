#ifndef _SEQUENCE_TEST_H_
#define _SEQUENCE_TEST_H_

#include "../Utility/ArraySequence.h"
#include <assert.h>


void ArraySequenceConstrTest() {

    ArraySequence<int> a;

    assert(16 == a.getSize());
    for (int i = 0; i < 16; ++i) {
        a[i] = (3 + i) * (i - 2);
    }

    for (int i = 0; i < 16; ++i) {
        assert(a[i] == (3 + i) * (i - 2));
    }

    assert(a[5] == 24);

    ArraySequence<double> b(3);
    assert(3 == b.getSize());

    b.append(1.5);
    assert(6 == b.getSize());

    int* ptr = new int[5];

    for (int i = 0; i < 5; ++i) {
        ptr[i] = 10 * i;
    }

    ArraySequence<int> c(5, ptr);

    assert(5 == c.getSize());
    
    for (int i = 0; i < 5; ++i) {
        assert(i * 10 == c[i]);
    }

    c.clear();
    assert(0 == c.getCurrent());
}

void ArraySequenceFuncTest() {
    int* ptr_1 = new int[8];
    int* ptr_2 = new int[8];

    int cnt = 1;

    for (int i = 0; i < 8; ++i) {
        ptr_1[i] = cnt * 10;
        ptr_2[i] = (cnt + 8) * 10;
        ++cnt;
    }

    ArraySequence<int> a(8, ptr_1);
    ArraySequence<int> b(8, ptr_2);

    assert(8 == a.getSize());
    assert(8 == b.getSize());

    assert(10 == a.getFirst());
    assert(90 == b.getFirst());

    assert(80 == a.getLast());
    assert(160 == b.getLast());

    a.concat(&b);

    assert(16 == a.getSize());

    

    assert(10 == a.getFirst());
    assert(160 == a.getLast());
    assert(160 == b.getLast());

    for (int i = 0; i < a.getSize(); ++i) {
        assert(10 * (i + 1) == a[i]);
    }

    a.append(170);
    assert(32 == a.getSize());
    assert(170 == a.getLast());

    a.clear();
}


void ArraySequenceTest() {
    ArraySequenceConstrTest();
    ArraySequenceFuncTest();

}

#endif