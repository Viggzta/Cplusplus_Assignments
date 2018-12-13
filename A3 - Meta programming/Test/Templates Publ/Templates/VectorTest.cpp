#ifdef _DEBUG
#ifndef DBG_NEW
#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
#define new DBG_NEW
#endif
#endif  // _DEBUG
#include <crtdbg.h>

#include "Vector.hpp"
//#include "ContOut.hpp"
//#include "SortSelect.hpp"
//#include <numeric>

void VectorTest() {

    Vector<int> vint;
    vint[0] = 3;
    Vector<int*> vintptr;
    vintptr[0] = new int(7);
    Vector<bool> vbool;
    vbool[0];
    vbool[2] = 0;
    bool f = vbool[2];
    vbool[2] = 1;
    f = vbool[2];
}