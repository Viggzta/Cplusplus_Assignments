#include "VectorTestHelp.h"

#include "Vector.hpp"

#include <iostream>
#include <cassert>

//Generates all functions declared
//Uncomment this to check that all functions compiles.
//template class Vector<int>; 

using std::cout;

template <class T>
struct IsConstOrConstRef {
	static const bool value = std::is_const<std::remove_reference<T>::type>::value;
};

template <class T>
bool IsConstOrConstRefFun(T& x) {
	return std::is_const<std::remove_reference<T>::type>::value;
};


struct C {
	static std::string usedConstr;
	void Test() {}
	C() {
		usedConstr += "DC";
	}
	C(const C& c) {
		usedConstr += "CC";
	}
	C(C&& c) {
		usedConstr += "MC";
	}
	C& operator=(const C& c) {
		usedConstr += "CA";
		return *this;
	}
	C& operator=(C&& c) {
		usedConstr += "MA";
		return *this;
	}
};

std::string C::usedConstr{};

//Test av push_back&&
void TestMove() {
	Vector<C> a;
	C c;
	assert(C::usedConstr == "DC");
	a.reserve(4);
	C::usedConstr = "";
	a.push_back(c);
	assert(C::usedConstr == "CC");
	C::usedConstr = "";
	a.push_back(std::move(c));
	assert(C::usedConstr == "MC");
}


void AssertStrEqual(Vector<char>& lhs, const char* rhs) {
	size_t i;
	for (i = 0; i < lhs.size() && *rhs != '\0'; ++i) {
		assert(lhs[i] == rhs[i]);
		assert(rhs[i] != 0);
	}
	assert(i == lhs.size() && rhs[i] == '\0');
	assert(rhs[lhs.size()] == 0);
}

void TestPushBackReallocation() {
	Vector<char> cont("hej");
	assert(cont.size() <= cont.capacity());
	assert(cont.size() == 3);
	AssertStrEqual(cont, "hej");
	//we try to take 20 empty places: (size+1 < capacity)
	while (cont.size() + 20 >= cont.capacity() && cont.size() < 1000)
		cont.push_back('A' + rand() % 32);
	assert(cont.size() < 1000);	//If this fail it prbably the case that capacity is increased with a constant.

	auto internalBuf = &cont[0];
	auto cap = cont.capacity();
	auto siz = cont.size();
	size_t i;
	for (i = siz + 1; i <= cap; ++i) {
		cont.push_back(char(i) + 'a');
		assert(internalBuf == &cont[0]);
		assert(cap == cont.capacity());
		assert(i == cont.size());
	}
	cont.push_back(char(i));
	assert(internalBuf != &cont[0]);
	assert(cap < cont.capacity());
	assert(i == cont.size());
}

template<class C>
void TestRel(const C& lhs, const C& rhs,
	bool(*trueFun)(const C& lhs, const C& rhs),
	bool(*falseFun)(const C& lhs, const C& rhs)) {
	assert(trueFun(lhs, vhs));
	assert(falseFun(lhs, vhs));
}


void TestCapacity() {
	Vector<char> Bar("Bar");
	const Vector<char> BarC("Bar");

	//-	size(), capacity() and reloccation test;
	TestPushBackReallocation();


	//	reserve()
	auto internalBuf = &Bar[0];
	auto cap = Bar.capacity();
	auto siz = Bar.size();

	Bar.reserve(cap);
	assert(internalBuf == &Bar[0]);
	assert(cap == Bar.capacity());
	assert(siz == Bar.size());

	Bar.reserve(cap + 1);
	assert(internalBuf != &Bar[0]);
	assert(cap < Bar.capacity());
	assert(siz == Bar.size());

	// shrink_to_fit
	Bar = "hej";
	Bar.reserve(10);
	internalBuf = &Bar[0];
	cap = Bar.capacity();
	siz = Bar.size();

	Bar.shrink_to_fit();
	assert(internalBuf != &Bar[0]);
	assert(Bar.capacity() == Bar.size());
	//    AssertStrEqual(str, "hej");

	cout << "\nVectorTest för "
#ifdef VGBETYG
		"Väl "
#endif
		"Godkänt klar\n";
}

#ifdef VGBETYG
void TestVGAssignment() {
	{
		Vector<char> Bar("Bar");
		Vector<char> Foo("Foo");
		auto Bar2 = Foo.AssSimple(Bar);
		assert(Bar2 == Foo && Foo == Bar && Bar == "Bar");
	}
	{
		Vector<char> Bar("Bar");
		Vector<char> Foo("Foo");
		auto Bar2 = Foo.AssFast(Bar);
		assert(Bar2 == Foo && Foo == Bar && Bar == "Bar");
	}
	{
		Vector<char> Bar("Bar");
		Vector<char> Foo("Foo");
		auto Bar2 = Foo.AssStrong(Bar);
		assert(Bar2 == Foo && Foo == Bar && Bar == "Bar");
	}
}
#endif

void TestVector() {
	{
		Vector<char> Foo("Foo");
		const Vector<char> FooC("Foo");
		Vector<char> Bar("Bar");
		const Vector<char> BarC("Bar");
	}

	//-	Vector<char>() // Utkommenterat by default
	{
		//        Vector<char> vec0;	AssertStrEqual(vec0, "");
	}

	//Move constructor
	{
		Vector<char> a("foo");
		Vector<char> b(std::move(a));
		assert(b == "foo" && a.data() == nullptr);
	}

	//-	Vector<char>(char *)
	{
		Vector<char> v1("foo"); assert(v1 == "foo");
		Vector<char> vec(v1); assert(vec == "foo");
		Vector<char> v3("bar");  assert(v3 == "bar");
	}
	//-	Vector<char>(Copy constructor)
	{
		Vector<char> v1("foo"); assert(v1 == "foo");
		Vector<char> v2(v1); assert(v2 == "foo");
		Vector<char> v3("bar");  assert(v3 == "bar");

		//-	~Vector<char>() Kom ihåg destruktorn!
		delete new Vector<char>("hej");

		//	-	operator =(Sträng sträng)
		v2 = "hej";
		assert((v2 = v3) == v3);
		assert((v2 = v2) == v3);	//self assignment

									//Ej samma buffert
		v2 = "hej";
		v3 = v2;
		v2[0] = 'x';
		assert(v3[0] == 'h');
		v3[1] = 'y'; assert(v2[1] == 'e');


		Vector<char> vec1("foo"), vec2("bar"), vec3("hej");
		vec3 = v2 = vec1;
		assert(vec3 == v2);
		assert(vec1 == v2);

#ifdef VGBETYG
		//No extra realloc
		AssertStrEqual(vec1, "foo");
		auto xxx = vec1.data();
		Vector<char> tempRealloc("huj");
		vec1 = tempRealloc;
		assert(xxx == vec1.data());
#endif
	}
	// Move assignment
	{
		Vector<char> Foo("Foo");
		const Vector<char> FooC("Foo");
		Vector<char> Bar("Bar");
		const Vector<char> BarC("Bar");
		Foo.Check();
		Bar.Check();
		Foo = std::move(Bar);
		Foo.Check();
		Bar.Check();
		assert(Foo == "Bar");
		assert(Bar == "" || Bar == "Foo");
		assert(Bar == "");  //Vanliga resultatet men Foo är också okej
	}

	//-	operator[](size_t i) som indexerar utan range check.
	{
		Vector<char> Foo("Foo");
		const Vector<char> FooC("Foo");
		Vector<char> Bar("Bar");
		const Vector<char> BarC("Bar");


		Bar = "bar";
		Bar[-1]; Bar[1000];	//No error (std::vector pass this in release mode)
		assert(Bar[1] == 'a');
		Bar[1] = 'y';
		assert(Bar[1] == 'y');

		//-	operator[](size_t i) const.

		assert(IsConstOrConstRefFun(BarC[1]));
		assert(BarC[1] == 'a');
	}
	//-	at(size_t i) som indexerar med range check
	{
		Vector<char> Bar("Bar");
		const Vector<char> BarC("Bar");

		try {
			Bar.at(-1);
			assert(false);
		}
		catch (std::out_of_range&) {};
		try {
			Bar.at(3);
			assert(false);
		}
		catch (std::out_of_range&) {};

		//- at indexerar

		//-	at(size_t i) 
		Bar = "bar";
		assert(Bar.at(1) == 'a');
		Bar.at(1) = 'y';
		assert(Bar.at(1) == 'y');

		assert(BarC.at(1) == 'a');
		assert(IsConstOrConstRefFun(BarC.at(1)));
	}

	// data
	{
		Vector<char> Bar("Bar");
		const Vector<char> BarC("Bar");

		assert(Bar.data() == &Bar[0]);
		assert(!IsConstOrConstRefFun(*Bar.data()));
		assert(IsConstOrConstRefFun(*BarC.data()));
	}

	//-	push_back(char c) lägger till ett tecken sist.
	{
		Vector<char> Bar("Bar");
		const Vector<char> BarC("Bar");

		Bar.push_back('a');
		assert(Bar == "Bara");
	}


	// resize
	{
		Vector<char> Bar("Bar");
		const Vector<char> BarC("Bar");
		//size up
		Bar.shrink_to_fit();
		auto buf = Bar.data();
		//Bar.resize(6);
		//assert(Bar[2] == 'r' && Bar[3] == 0 && Bar[4] == 0 && Bar[5] == 0);
		//assert(buf != Bar.data() && Bar.capacity() >= 6 && Bar.size() == 6);
		//buf = Bar.data();
		//Bar.resize(5);
		//assert(buf == Bar.data() && Bar.capacity() >= 6 && Bar.size() == 5);
	}

	//Test push_back &&
	{
		//        Vector<C> Bar("Bar");

	}

	//-	operator== 
	//testas överallt!

	{
#define RelTest(a, b, c, d)  a c b && !(a d b)

		Vector<char> Abcdef("Abcdef");
		Vector<char> Bbcdef("Bbcdef");
		Vector<char> AbcdeF("AbcdeF");
		Vector<char> Abcdefg("Abcdefg");

		{ bool f = RelTest(Abcdef, Abcdef, == , != ); assert(f); }
		{ bool f = RelTest(Abcdef, AbcdeF, != , == ); assert(f); }
		{ bool f = RelTest(Abcdef, Bbcdef, != , == ); assert(f); }
		{ bool f = RelTest(Abcdef, Abcdefg, != , == ); assert(f); }
		{ bool f = RelTest(Abcdefg, Abcdef, != , == ); assert(f); }

		{ bool f = RelTest(Abcdef, Abcdef, == , <); assert(f); }
		{ bool f = RelTest(Abcdef, AbcdeF, >, <); assert(f); }
		{ bool f = RelTest(Abcdef, Bbcdef, <, >); assert(f); }
		{ bool f = RelTest(Abcdef, Abcdefg, <, >); assert(f); }

		{ bool f = RelTest(Abcdef, Abcdef, <= , != ); assert(f); }
		{ bool f = RelTest(Abcdef, AbcdeF, >= , <= ); assert(f); }
		{ bool f = RelTest(Abcdef, Bbcdef, <= , >= ); assert(f); }
		{ bool f = RelTest(Abcdef, Abcdefg, <= , >= ); assert(f); }

		swap(Abcdef, Abcdefg);
		assert(Abcdef == "Abcdefg");
		assert(Abcdefg == "Abcdef");
	}

	TestCapacity();
	TestMove();
#ifdef VGBETYG
	TestVGAssignment();
#endif
}



//Test of typedefs!
using std::is_same;
static_assert(is_same<int, Vector<int>::value_type>::value, "typdef missing");
static_assert(is_same<size_t, Vector<int>::size_type>::value, "typdef missing");
static_assert(is_same<ptrdiff_t, Vector<int>::difference_type>::value, "typdef missing");
static_assert(is_same<int&, Vector<int>::reference>::value, "typdef missing");
static_assert(is_same<const int&, Vector<int>::const_reference>::value, "typdef missing");
static_assert(is_same<int*, Vector<int>::pointer>::value, "typdef missing");
static_assert(is_same<const int*, Vector<int>::const_pointer>::value, "typdef missing");
static_assert(is_same<Vector<int>::iterator, Vector<int>::iterator>::value, "typdef missing");
static_assert(is_same<Vector<int>::const_iterator, Vector<int>::const_iterator>::value, "typdef missing");
static_assert(is_same<Vector<int>::reverse_iterator, Vector<int>::reverse_iterator>::value, "typdef missing");
static_assert(is_same<Vector<int>::const_reverse_iterator, Vector<int>::const_reverse_iterator>::value, "typdef missing");
