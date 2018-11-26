#ifdef _DEBUG
#ifndef DBG_NEW
#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
#define new DBG_NEW
#endif
#endif  // _DEBUG
#include <crtdbg.h>
#include <iostream>
#include "List.hpp"

using std::cout;

//template class List<int>;

void TestList();
void TestListIter();

int main() {
#ifdef DBG_NEW
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif

    TestList();
    TestListIter();
    std::cout << "There should be one memory leak!";
    std::cin.get();
}