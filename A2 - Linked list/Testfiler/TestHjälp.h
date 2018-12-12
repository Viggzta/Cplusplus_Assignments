#pragma once

typedef List<char> Cont;
typedef Cont::iterator Iter;

template <class T>
struct IsConstOrConstRef {
    static const bool value = std::is_const<std::remove_reference<T>::type>::value;
};

template <class T>
bool IsConstOrConstRefFun(T& x) {
    return std::is_const<std::remove_reference<T>::type>::value;
};

