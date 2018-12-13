#pragma once
#include <iostream>

//template <class C>
//std::ostream& operator<<(std::ostream& cout, const C& container) {
//    for (auto item : container)
//        cout << item;
//    cout << std::endl;
//}

template <class Titer>
std::ostream& Print(Titer iter, size_t size) {
    for (size_t i = 0; i < size; ++i)
        std::cout << *iter++ << ' ';
    return std::cout;
}

template<class T, size_t N>
std::ostream& Print(T (&arr)[N]) {
    return Print(arr, N);
}
