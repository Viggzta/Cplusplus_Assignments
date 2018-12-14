#include <type_traits>

template <class T>
auto DoSum(T c)
{
	using unknown_type = decltype(*c.begin());
	typedef std::remove_reference<unknown_type>::type T_noref;
	T_noref sum{};
	for (auto i : c)
		sum += i;
	return sum;
}