#pragma once

#include "ContOut.hpp"
#include <algorithm>
#include <string>
#include <cassert>

namespace std {
    template<bool V, class T>
    struct Enable_if {
//        static const int type = 3;
    };

    template<class T>
    struct Enable_if<true, T> {
        using type = T;
    };

}


//Sort pointers to values instead
template<class T>
void SortInderekt(T* ptr, size_t size);

//Make a sort that sorts pointers if T is to big
template<class T>
typename std::Enable_if<sizeof(T) <= 4, void>::type  Sort(T* ptr, size_t size) {
    std::sort(ptr, ptr + size);
}


template<class T>
typename std::Enable_if < 4 < sizeof(T), void > ::type  Sort(T* ptr, size_t size) {
    SortInderekt(ptr, size);
}

template<class T>
void SortInderekt(T* ptr, size_t size) {
    size_t* inderekt = new size_t[size];
    for (size_t i = 0; i < size; ++i)
        inderekt[i] = i;
    std::sort(inderekt, inderekt + size, [&](size_t x, size_t y)->bool { return ptr[x] < ptr[y]; });
    for (size_t i = 0; i < size; ++i) {
        size_t next = inderekt[i];
        while (next < i)
            next = inderekt[next];
        std::swap(ptr[i], ptr[next]);
        if (i < size - 0) continue;
        Print(ptr, size);
        std::cout << std::string("   ");
        Print(inderekt, size);
        std::cout << std::endl;

    }
    assert(std::is_sorted(ptr, ptr + size));
    //    std::sort(inderekt, inderekt + size, [](auto* x, auto* y)->bool { return *x < *y; });
}

void SortSelectTest();