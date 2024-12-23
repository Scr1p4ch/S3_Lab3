#ifndef _SPARCE_VECTOR_TEST_H_
#define _SPARCE_VECTOR_TEST_H_

#include <assert.h>
#include "../Problems/SparceVector.h"

void sparceVectorTest() {
    SparceVector<5, int> a;

    assert(0 == a.getRealSize());
    assert(5 == a.getDimension());

    for (int i = 0; i < 5; ++i) {
        a[i] = i;
    }

    ++a[0];
    assert(1 == a[0]);

    a[0]++;
    assert(2 == a[0]);

    --a[0];
    assert(1 == a[0]);

    a[0]--;
    assert(0 == a[0]);

    ++a[0];
    a[0] *= 2;

    assert(2 == a[0]);

    a[0] /= 2;
    assert(1 == a[0]);

    --a[0];

    assert(4 == a.getRealSize());

    SparceVector<5, int> b;
    for (int i = 0; i < 5; ++i) {
        b[i] = 1;
    }

    a += b;
    for (int i = 0; i < 5; ++i) {
        assert((i + 1) == a[i]);
    }

    a -= b;

    for (int i = 0; i < 5; ++i) {
        assert(i == a[i]);
    }

    for (int i = 0; i < 5; ++i) {
        b[i] = 2;
    }

    a = a + b;

    for (int i = 0; i < 5; ++i) {
        assert((2 + i) == a[i]);
    }

    a = a - b;

    for (int i = 0; i < 5; ++i) {
        assert(i == a[i]);
    }


    SparceVector<5, int> c(4);

    assert(0 == c.getRealSize());

    c[1] = 4;

    assert(0 == c.getRealSize());

    c[1] = 0;

    assert(1 == c.getRealSize());
    
    c = SparceVectorSum(1, a, b);
    --c[0];
    assert(4 == c.getRealSize());

    assert(1 == c[0]);
    assert(6 == c[4]);
}

#endif