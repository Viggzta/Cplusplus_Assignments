#include "VectorTestHelp.h"

template <typename T>
class Vector;


#include "VectIter.hpp"

#include "Vector.hpp"

#include <cassert>
#include <iostream>
using std::cout;
using std::endl;


#pragma region help jox

using it = Vector<char>::iterator;
using cit = Vector<char>::const_iterator;
using rit = Vector<char>::reverse_iterator;
using crit = Vector<char>::const_reverse_iterator;

template<class T>
struct IsSameFun {
	template<class V>
	static void e(V v) {
		static_assert(std::is_same<T, V>::value, "Not right return type");
	}
};

template<class T, class U>
struct IsSameS {
	static_assert(std::is_same_v<T, U>, "Not right type");
	static const bool value = true;
};

template< class T, class U >
constexpr bool IsSameCheck = IsSameS<T, U>::value;

struct D {
	static std::string usedConstr;

	void Test() {}
	D() {
		usedConstr += "DC";
	}
	D(const D& c) {
		usedConstr += "CC";
	}
	D(D&& c) {
		usedConstr += "MC";
	}
	D& operator=(const D& c) {
		usedConstr += "CA";
		return *this;
	}
	D& operator=(D&& c) {
		usedConstr += "MA";
		return *this;
	}
};

std::string D::usedConstr{};

#pragma endregion help jox

#pragma region Test Begin
void TestAllBegin() {
	Vector<char> Foo("Foo");
	const Vector<char> FooC("Foo");
	Vector<char> Bar("Bar");
	const Vector<char> BarC("Bar");
	IsSameFun<it>::e(Foo.begin());
	IsSameFun<cit>::e(FooC.begin());
	IsSameFun<cit>::e(Foo.cbegin());
	IsSameFun<rit>::e(Foo.rbegin());
	IsSameFun<crit>::e(FooC.rbegin());
	IsSameFun<crit>::e(Foo.crbegin());

	IsSameFun<it>::e(Foo.end());
	IsSameFun<cit>::e(FooC.end());
	IsSameFun<cit>::e(Foo.cend());
	IsSameFun<rit>::e(Foo.rend());
	IsSameFun<crit>::e(FooC.rend());
	IsSameFun<crit>::e(Foo.crend());
}

void TestBegin() {
	Vector<char> Foo("Foo");
	const Vector<char> FooC("Foo");
	Vector<char> Bar("Bar");
	const Vector<char> BarC("Bar");
	{
		Vector<char> c;
		for (auto it = Bar.begin(); it != Bar.end(); ++it)
			c.push_back(*it);
		assert(c == "Bar");
	}
	{
		Vector<char> c;
		for (auto it = Bar.cbegin(); it != Bar.cend(); ++it)
			c.push_back(*it);
		assert(c == "Bar");
	}
}

void TestRevBegin() {
	Vector<char> Foo("Foo");
	const Vector<char> FooC("Foo");
	Vector<char> Bar("Bar");
	const Vector<char> BarC("Bar");
	{
		Vector<char> c;
		for (auto it = Bar.rbegin(); it != Bar.rend(); ++it)
			c.push_back(*it);
		assert(c == "raB");
	}
	{
		Vector<char> c;
		for (auto it = Bar.crbegin(); it != Bar.crend(); ++it)
			c.push_back(*it);
		assert(c == "raB");
	}
}
#pragma endregion Test Begin

#pragma endregion begin/end och ++

#pragma region relop
void TestRelOp() {
	Vector<char> Foo("Foo");
	{
		auto b = Foo.begin();
		auto a = b++;
		auto c = b;
		assert(b == c && !(b != c));
		assert(a != c && !(a == c));
		assert(a < c && !(a >= c));
		assert(c > a && !(c <= a));
	}
	{
		auto b = Foo.cbegin();
		auto a = b++;
		auto c = b;
		assert(b == c && !(b != c));
		assert(a != c && !(a == c));
		assert(a < c && !(a >= c));
		assert(c > a && !(c <= a));
	}
	{
		auto b = Foo.rbegin();
		auto a = b++;
		auto c = b;
		assert(b == c && !(b != c));
		assert(a != c && !(a == c));
		assert(a < c && !(a >= c));
		assert(c > a && !(c <= a));
	}
	{
		auto b = Foo.crbegin();
		auto a = b++;
		auto c = b;
		assert(b == c && !(b != c));
		assert(a != c && !(a == c));
		assert(a < c && !(a >= c));
		assert(c > a && !(c <= a));
	}
}

#pragma endregion relop

#pragma region constr och assignment
void TestConstr() {
	Vector<char> Foo("Foo");
	it a{}; a = Foo.begin();
	it b(a);
	assert(a == b);
	it c;
	c = a;
	assert(a == c);
}
#pragma endregion constr och assignment


#pragma region --
/*	--it, it-- */


void TestMM() {
	Vector<char> Foo("Foo");
	const Vector<char> FooC("Foo");
	Vector<char> Bar("Bar");
	const Vector<char> BarC("Bar");
	{
		Vector<char> c;
		for (auto it = Foo.end(); it != Foo.begin();)
			c.push_back(*--it);
		assert(c == "ooF");
	}
	{
		Vector<char> c;
		for (auto it = Foo.crend(); it != Foo.crbegin();)
			c.push_back(*--it);
		assert(c == "Foo");
	}
	{
		auto it = Bar.end(); --it;
		assert(*it == 'r');
		assert(*(it--) == 'r' && *it == 'a');
		*--it = 'y';
		assert(*it == 'y');
		assert(*(it + 1) == 'a');
	}
}
#pragma endregion --

#pragma region * -> []
void TestAccess() {
	{
		Vector<char> Bar("BarBar");
		const Vector<char> BarC("BarBar");
		auto it = Bar.begin();
		assert(*it == 'B');
		assert(it[2] == 'r');
		IsSameCheck<char&, decltype(*it)>;
		auto itC = BarC.begin();
		assert(*itC == 'B');
		assert(itC[2] == 'r');
		IsSameCheck<const char&, decltype(*itC)>;
		Vector<D> Dcont;
		Dcont.push_back(D());
		Dcont.begin()->Test();
	}
	{
		Vector<char> Bar("BarBar");
		const Vector<char> BarC("BarBar");
		auto it = Bar.rbegin();
		assert(*it == 'r');
		assert(it[2] == 'B');
		IsSameCheck<char&, decltype(*it)>;
		auto itC = BarC.rbegin();
		assert(*itC == 'r');
		assert(itC[2] == 'B');
		IsSameCheck<const char&, decltype(*itC)>;
		Vector<D> Dcont;
		Dcont.push_back(D());
		Dcont.rbegin()->Test();
	}
}
#pragma endregion * ->



/*	*it, ++it, it++, (it+i), it[i], == och !=	*/
void TestIterPart() {
	Vector<char> vecFooBar("FooBar");
	for (auto i = vecFooBar.begin(); i != vecFooBar.end(); i++)
		cout << *i;
	cout << " står det FooBar?" << endl;
	//    vecBar = "raboof";
	auto it = vecFooBar.begin();
	assert(*it == 'F');
	assert(*(it++) == 'F' && *it == 'o');
	*(++it) = 'y';
	assert(*++it == 'B');
	assert(*(it + 1) == 'a');
}


void TestIter() {
	TestAccess();
	TestAllBegin();
	TestBegin();
	TestRevBegin();
	TestRelOp();
	TestConstr();
	TestMM();
	//OLDDDDDDDDDDDD

	//-	typdefs för iterator
	Vector<char>::iterator iter;
	Vector<char> vec("hej12345678");
	iter = vec.begin();

	//-	funktionerna begin, end.
	TestIterPart();

	//Iteratorerna ska kunna göra:
	//-	*it, ++it, it++, (it+i), it[i], == och !=
	// Här saknas en massa tester, jag provar bara att de finns!
	assert(*(++iter)++ = 'e');
	ptrdiff_t i = iter - vec.begin();
	assert((*iter) == 'j');
	assert(*(iter + 5 - (iter - iter)) == '5');

	//-	default constructor, copy constructor och tilldelning (=) 
	Vector<char> s("foobar");
	iter = s.begin();
	*iter = 'a';
	assert(s == "aoobar");

	TestIterPart();

	cout << "\nIterator Test för "
#ifdef VGBETYG
		"Väl "
#endif
		"Godkänt klar\n";
}



//Test of typedefs!
using std::is_same;
template<class Iter>
struct CheckTypedefs {
	static_assert(is_same<int, typename Iter::value_type>::value, "value_type is missing");
	static_assert(is_same<ptrdiff_t, typename Iter::difference_type>::value, "typdef missing");
	static_assert(is_same<int&, typename Iter::reference>::value, "typdef missing, int&");
	static_assert(is_same<int*, typename Iter::pointer>::value, "typdef missing, int*");
	static_assert(is_same<std::random_access_iterator_tag, typename Iter::iterator_category>::value, "should be random_access_iterator_tag");
};

template<class Iter>
struct CheckTypedefsConst {
	static_assert(is_same<int, typename Iter::value_type>::value, "value_type should be without const");
	static_assert(is_same<ptrdiff_t, typename Iter::difference_type>::value, "typdef missing");
	static_assert(is_same<const int&, typename Iter::reference>::value, "should be with const");
	static_assert(is_same<const int*, typename Iter::pointer>::value, "should be with const");
	static_assert(is_same<std::random_access_iterator_tag, typename Iter::iterator_category>::value, "should be random_access_iterator_tag");
};

template struct CheckTypedefs<Vector<int>::iterator>;
template struct CheckTypedefsConst<Vector<int>::const_iterator>;
template struct CheckTypedefs<Vector<int>::reverse_iterator>;
template struct CheckTypedefsConst<Vector<int>::const_reverse_iterator>;
