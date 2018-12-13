#ifdef _DEBUG
#ifndef DBG_NEW
#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
#define new DBG_NEW
#endif
#endif  // _DEBUG
//#include <crtdbg.h>
//
//#include "Vector.hpp"
#include "ContOut.hpp"
#include "SortSelect.hpp"
#include <numeric>

using std::cout;
using std::endl;

void SortSelectTest() {
    int s2[29];
    std::iota(s2, s2 + sizeof(s2) / sizeof(s2[0]), 0);
    std::random_shuffle(s2, s2 + sizeof(s2) / sizeof(s2[0]));
    Print(s2, sizeof(s2) / sizeof(s2[0])) << std::endl;
    Sort(s2, sizeof(s2) / sizeof(s2[0]));
    Print(s2) << std::endl;
    cout << endl << endl;

    double s3[29];
    std::iota(s3, s3 + sizeof(s3) / sizeof(s3[0]), 0);
    Print(s3) << std::endl;
    std::random_shuffle(s3, s3 + sizeof(s3) / sizeof(s3[0]));
    Print(s3) << std::endl;
    Sort(s3, sizeof(s3) / sizeof(s3[0]));
    Print(s3) << std::endl;

    SortInderekt(s3, sizeof(s3) / sizeof(s3[0]));

}