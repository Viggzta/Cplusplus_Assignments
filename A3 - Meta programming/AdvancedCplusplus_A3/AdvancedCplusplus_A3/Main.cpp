#include<iostream>
#include<cassert>
#include <vector>

#include "AckerMann.h"
#include "BaseType.h"
#include "DoSumLabb.h"

void TestAckerMann() {
	size_t x1 = Add<0, 4>::value;
	size_t x2 = Add<19, 4>::value;
	size_t x3 = Add<400, 4>::value;
	assert(x3 == 404 && x2 == 23);
	size_t a1 = Ackermann<0, 4> ::value;
	assert(a1 == 5);
	size_t a2 = Ackermann<1, 4> ::value;
	assert(a2 == 6);
	size_t a3 = Ackermann<2, 4> ::value;
	assert(a3 == 11);
	size_t a4 = Ackermann<3, 4> ::value;
	assert(a4 == 125);
	size_t a5 = Ackermann<4, 0> ::value;
	assert(a5 == 13);
}

#define AssertSame(X,Y) assert((std::is_same<X, Y>::value))

void TestBaseType() {
	AssertSame(int, SimplifyType_t<int>);
	AssertSame(int, SimplifyType_t<int*>);
	AssertSame(int**const*, SimplifyType_t<int**const**>);
	AssertSame(const int, SimplifyType_t<const int&>);

	SimplifyType_t<const int&> x = 0;

	BaseType_t<int*> y = 0;
	AssertSame(int, BaseType_t<int>);
	AssertSame(int, BaseType_t<int*>);
	AssertSame(int, BaseType_t<int***&>);
	AssertSame(int, BaseType_t<const int** const **&>);
	AssertSame(BaseType_t<const int>, BaseType_t< BaseType_t<const int>**>);
	AssertSame(BaseType_t<const int>, BaseType<const int>::type);

	std::is_same<int, int>::value;
	assert((std::is_same<int, int>::value));
	AssertSame(int, int);
}

void TestDoSum() {
	std::vector<int> v = { 1,2,3,-9 };
	int sum = DoSum(v);
	std::cout << sum << std::endl;
	assert(sum == -3);
}

int main() {
	TestAckerMann();
	TestBaseType();
	TestDoSum();

	char* s = new char[10];
	std::cin >> s;
	delete s;
}