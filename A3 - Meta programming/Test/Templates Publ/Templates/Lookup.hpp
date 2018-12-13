#pragma once
struct C;

//void Swap(C&, C&) {
//}

struct B {
    friend void Swap(B&, B&) {
    };
};
struct C {
    friend void Swap(C&, C&) {
    };
    static void Swap(C&, C&) {
    };
    void Swap(C&) {
    };
    void Test() {
        C a, b, c;
        Swap(a);
        Swap(a, b);
//        ::Swap(a, b);
    }
};

void TestSwap() {
    C a, b, c;
    B bbb;
    c.Test();
    a.Swap(a);
//    ::Swap(a, b);
    C::Swap(a, b);
    Swap(a, a);
}