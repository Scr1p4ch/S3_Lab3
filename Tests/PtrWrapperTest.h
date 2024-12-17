#include <assert.h>
#include "../Utility/PtrWrapper.h"
#include <iostream>

void PtrWrapperConstructTest() {
    int* a = new int(3);
    int* b = new int[3];

    b[0] = 10; b[1] = 20; b[2] = 30;

    {
        PtrWrapper ptr(a);
        PtrWrapper<int[]> ptrAr(b);

        assert(3 == *a);

        for (int i = 0; i < 3; ++i) {
            assert(10 * (i + 1) == b[i]);
        }
    }
}

void PtrWrapperFuncTest() {
    int* a = new int(5);
    int* b = new int[3];
    int* c = new int(3);

    b[0] = 10; b[1] = 20; b[2] = 30;

    {
        PtrWrapper ptr(a);
        PtrWrapper<int[]> ptrAr(b);

        PtrWrapper ptr2(Move(ptr));

        assert(nullptr == ptr);
        assert(ptr == nullptr);
        assert(a == ptr2.get());
        assert(static_cast<int*>(ptr2) == a);

        ptr2.reset(c);
        assert(3 == *ptr2.get());
        assert(3 == *ptr2);

        assert(10 == *ptrAr);
        assert(30 == ptrAr[2]);

    }

}


void PtrWrapperTest() {
    PtrWrapperConstructTest();
    PtrWrapperFuncTest();
}