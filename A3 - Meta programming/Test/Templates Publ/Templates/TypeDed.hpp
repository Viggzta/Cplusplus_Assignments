#pragma once
#include <vector>


#if false
//Försök 1

template<class T, class Cont >
T Sum(Cont cont, const T& defaultValue) {
    auto sum = defaultValue;
    for (auto item : cont)
        sum += item;
    return sum;
};

void TestSum() {
    std::vector<float> v = { 1, 4.1f, 8.3f, 3, 1 };
    float s = Sum<float, std::vector<float> >(v, 3.0f);
    float r = Sum(v, 3);    //Fel svar!
}

#elif false
//Försök 2, använd ::value_type

template<class Cont >
auto Sum(Cont cont, const typename Cont::value_type& defaultValue) {
    auto sum = defaultValue;
    for (auto item : cont)
        sum += item;
    return sum;
};

void TestSum() {
    std::vector<float> v = { 1, 4.1f, 8.3f, 3, 1 };
    float s = Sum<std::vector<float> >(v, 3.0f);
    float r = Sum(v, 3);
}

#elif false
//Försök 3  //ta fram de olika typerna!

template<class T, template <class, class> class Cont >
typename Cont<T, std::allocator<T> >::value_type Sum(Cont<T, std::allocator<T> > cont,
    const typename Cont<T, std::allocator<T> >::value_type& defaultValue) {
    auto sum = defaultValue;
    for (auto item : cont)
        sum += item;
    return sum;
};

void TestSum() {
    std::vector<float> v = { 1, 4.1f, 8.3f, 3, 1 };
    float s = Sum<float, std::vector>(v, 3.0f);
    float r = Sum(v, 3);
}

#elif false
//Försök 4  //använd T i stället för value_type

template<class T, template <class, class> class Cont >
T Sum(Cont<T, std::allocator<T> > cont, const T& defaultValue) {
    auto sum = defaultValue;
    for (auto item : cont)
        sum += item;
    return sum;
};

void TestSum() {
    std::vector<float> v = { 1, 4.1f, 8.3f, 3, 1 };
    float s = Sum<float, std::vector>(v, 3.0f);
    float r = Sum(v, 3.0f);
    //float t = Sum(v, 3);    //Error, ambigius
}

#elif false
//Försök 5  typedef std::vector utan allocator.

template<class X>
using Vect = std::vector<X, std::allocator<X> >;

template<class T, template <class> class Cont >
typename Cont<T>::value_type Sum(Cont<T > cont,
    const typename Cont<T>::value_type& defaultValue) {
    auto sum = defaultValue;
    for (auto item : cont)
        sum += item;
    return sum;
};

void TestSum() {
    Vect<float> v = { 1, 4.1f, 8.3f, 3, 1 };
    float s = Sum<float, Vect>(v, 3.0f);
    float r = Sum(v, 3.0f); //Error
    float t = Sum(v, 3);    //Error
}

#elif true
//Försök 6  gör ny klass Vect utan allocator.

template<class X>
class Vect : public std::vector<X, std::allocator<X> > {};
//Allt kommer att fungeraa UTOM konstruktorer!

template<class T, template <class> class Cont >
typename Cont<T>::value_type Sum(Cont<T > cont,
    const typename Cont<T>::value_type& defaultValue) {
    auto sum = defaultValue;
    for (auto item : cont)
        sum += item;
    return sum;
};

void TestSum() {
    Vect<float> v; 
    std::vector<float> vv = { 1, 4.1f, 8.3f, 3, 1 };
    //*(std::vector<float>*)(&v) = vv;
    *(dynamic_cast<std::vector<float>*>(&v)) = vv;
    float s = Sum<float, Vect>(v, 3.0f);
    float r = Sum(v, 3.0f);
    float t = Sum(v, 3);
}

#elif true
//Försök

#endif
