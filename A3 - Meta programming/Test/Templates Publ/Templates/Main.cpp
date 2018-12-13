#ifdef _DEBUG
#ifndef DBG_NEW
#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
#define new DBG_NEW
#endif
#endif  // _DEBUG
#include <crtdbg.h>

#include "Vector.hpp"
#include "ContOut.hpp"
#include "SortSelect.hpp"
#include "Fakultet.h"
#include "Lookup.hpp"

#include <numeric>

void TestSum();


int main() {
#ifdef DBG_NEW
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif
    //TestSwap();
    TestFakultet();
    TestSum();

    //SortSelectTest();

    //VectorTest();

    std::cin.get();
}