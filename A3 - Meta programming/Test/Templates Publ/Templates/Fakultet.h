#pragma once


template<int n>
struct Fakultet {
    static const long long value = n * Fakultet<n - 1>::value;
};

template<>
struct Fakultet<0> {
    static const int value = 1;
};

void TestFakultet() {
    long long n = Fakultet<40>::value;
}