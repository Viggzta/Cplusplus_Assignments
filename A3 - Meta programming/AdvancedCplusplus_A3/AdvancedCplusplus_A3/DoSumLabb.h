#include <type_traits>

template <class T>
auto DoSum(T c)
{
	decltype(*c.begin()) x = AddLoop<std::begin(c), std::end(c)>::value;
	return x;
}

template <class T>
auto DoSum(T a, T b)
{
	return DoSum(a, b);
}

template <class T, class T>
struct AddLoop
{
	T value = from + AddLoop<from + 1, to>::value;
};

template <class T>
struct AddLoop<T, T>
{
	T value = 0; // End reached
};