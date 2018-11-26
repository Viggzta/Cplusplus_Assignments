#pragma once
template<class T>
class VectorTest
{
public:
	struct IsConstOrConstRef;
	bool IsConstOrConstRefFun(T& x);
	void AssertStrEqual(Vector<char>& lhs, const char* rhs);
	void TestPushBackReallocation();
	void TestRel(const C& lhs, const C& rhs,
		bool(*trueFun)(const C& lhs, const C& rhs),
		bool(*falseFun)(const C& lhs, const C& rhs));
	void TestCapacity();
	void TestVector();
};

