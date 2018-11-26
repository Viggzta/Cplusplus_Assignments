#ifdef _DEBUG
#ifndef DBG_NEW
#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
#define new DBG_NEW
#endif
#endif  // _DEBUG
#include <crtdbg.h>
#include <iostream>
#include "List.hpp"

#include "TestHjälp.h"
#include <cassert>

//template class List<int>;

using std::cout;

//void AssertStrEqual(List<char>& lhs, const char* rhs) {
//    auto lIt = lhs.begin(); auto rIt = rhs;
//    for (; lIt != lhs.end() && *rIt; ++lIt, ++rIt) {
//        assert(*rIt == *rIt);
//        assert(*rhs != 0);
//    }
//    assert(lIt == lhs.end() && *rIt == '\0');
//}


void TestIterRel(); //Längst ner

void TestList() {
    {
        List<char> Foo("Foo");
        const List<char> FooC("Foo");
        List<char> Bar("Bar");
        const List<char> BarC("Bar");
    }

    //Typedef, måste fungera för att testprogrammet ska fungera!
    {
        std::string strHej("hej");
        List<std::string> a{}; a.push_back(strHej);
        List<std::string>::iterator i;
        i = a.begin();
        assert(*i == strHej);
    }
    //Tom testning av att alla constructorer och tilldelningsoperaoterer finns!
    {
        Cont a{};
        Cont b{ a };
        Cont c{ "hej" };
        Cont d{ std::move(c) };
        a = b;
        c = "hej";
        b = std::move(c);
        c.Check();
        d.Check();
        a.Check();
        b.Check();
    }
    //-	~List<char>() Kom ihåg destruktorn!
    {
        auto x = new List<char>("hej");
        noexcept(x -> ~List()); //Kolla om det kompilerar!
        delete x;
    }

    //-	copy constructor  , move
    {
        Cont a("Hej"), c("Foo");
        c = a;
        assert(c == "Hej" && a == c);
        a.front() = 'a';
        assert(a == "aej" && c == "Hej");

        Cont m(std::move(a));
        m.Check(); a.Check();
        assert(m == "aej" && a == "");
        //Move empty!
        Cont mm(std::move(a));
        mm.Check(); a.Check();
        assert(mm == "" && a == "");
    }

    //-	List<char>(char *)
    {
        List<char> v1("foo"); assert(v1 == "foo");
        List<char> vec(v1); assert(vec == "foo");
        List<char> v3("bar");  assert(v3 == "bar");
    }
    //	-	operator =(Sträng sträng)
    {
        List<char> Foo("Foo");
        const List<char> FooC("Foo");
        List<char> Bar("Bar");
        const List<char> BarC("Bar");
        Cont a("hej");
        Bar = a;
        Bar.Check();
        assert(Bar == "hej");
        assert((Bar = a) == a);
        assert((Bar = Bar) == a);	//self assignment
    }

        //move!
    {
        List<char> Foo("Foo");
        List<char> Bar("Bar");

        Bar = std::move(Foo);
        Bar.Check(); Foo.Check();
        assert(Bar == "Foo" && Foo == "");

        //move empty
        Bar = std::move(Foo);
        Bar.Check(); Foo.Check();
        assert(Bar == "" && Foo == "");

    }

        //move const
    {
        List<char> Foo("Foo");
        const List<char> FooC("Foo");
        List<char> Bar("Bar");
        const List<char> BarC("Bar");
        Bar = BarC;
        Bar = std::move(FooC);
        Bar.Check(); FooC.Check();
        assert(Bar == "Foo" && FooC == "Foo");
    }

    // front, back;
    {
        Cont a("Hej");
        assert(a.front() == 'H' && a.back() == 'j');
        a.front() = 'x'; assert(a == "xej");
    }

    //-	push och pop
    {
        Cont a{};
        a.push_front('b');
        assert(a == "b");
        a.push_back('c');
        assert(a == "bc");
        a.push_front('a');
        assert(a == "abc");
        a.pop_front();
        assert(a == "bc");
        a.pop_back();
        assert(a == "b");
        a.push_back('x');
        assert(a == "bx");
    }

    //size och empty
    {
        List<char> Bar("Bar");
        const List<char> BarC("Bar");
        Cont a{};
        a.Check();

        //-	size();
        assert(3 == BarC.size() && 0 == a.size());
        //-	empty();
        assert(!BarC.empty() && a.empty());

    }

    //Check const of some functions!
    //INTE GJORT!
    {
        List<char> Foo("Foo");
        const List<char> FooC("Foo");
        List<char> Bar("Bar");
        const List<char> BarC("Bar");
        BarC.front();
        assert(!IsConstOrConstRefFun(Bar.front()));
        assert(IsConstOrConstRefFun(BarC.front()));
        assert(!IsConstOrConstRefFun(Bar.back()));
        assert(IsConstOrConstRefFun(BarC.back()));
    }

    {
        //List<char> Foo("Foo");
        //List<char> Bar("Bar");
        //swap(Foo, Bar);
        //assert(Foo == "Bar" && Bar == "Foo");
    }
    TestIterRel();

}


template<class C>
void TestRel(const C& lhs, const C& rhs,
    bool(*trueFun)(const C& lhs, const C& rhs),
    bool(*falseFun)(const C& lhs, const C& rhs)) {
    assert(trueFun(lhs, vhs));
    assert(falseFun(lhs, vhs));
}

void TestIterRel() {
#define RelTest(a, b, c, d)  a c b && !(a d b)

    List<char> vecAbcdef("Abcdef");
    List<char> vecBbcdef("Bbcdef");
    List<char> vecAbcdeF("AbcdeF");
    List<char> vecAbcdefg("Abcdefg");

    { bool f = RelTest(vecAbcdef, vecAbcdef, == , != ); assert(f); }
    { bool f = RelTest(vecAbcdef, vecAbcdeF, != , == ); assert(f); }
    { bool f = RelTest(vecAbcdef, vecBbcdef, != , == ); assert(f); }
    { bool f = RelTest(vecAbcdef, vecAbcdefg, != , == ); assert(f); }
    { bool f = RelTest(vecAbcdefg, vecAbcdef, != , == ); assert(f); }

    bool f1 = vecAbcdeF < vecBbcdef;
    bool f2 = vecAbcdef < vecAbcdeF;
    bool f3 = vecAbcdef < vecAbcdef;
    { bool f = RelTest(vecAbcdef, vecAbcdef, == , <); assert(f); }
    { bool f = RelTest(vecAbcdef, vecAbcdeF, >, <); assert(f); }
    { bool f = RelTest(vecAbcdef, vecBbcdef, <, >); assert(f); }
    { bool f = RelTest(vecAbcdef, vecAbcdefg, <, >); assert(f); }

    { bool f = RelTest(vecAbcdef, vecAbcdef, <= , != ); assert(f); }
    { bool f = RelTest(vecAbcdef, vecAbcdeF, >= , <= ); assert(f); }
    { bool f = RelTest(vecAbcdef, vecBbcdef, <= , >= ); assert(f); }
    { bool f = RelTest(vecAbcdef, vecAbcdefg, <= , >= ); assert(f); }

    //swap(vecAbcdef, vecAbcdefg);
    //assert(vecAbcdef == "Abcdefg");
    //assert(vecAbcdefg == "Abcdef");
}
