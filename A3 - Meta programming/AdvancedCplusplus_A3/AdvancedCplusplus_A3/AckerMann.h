template <size_t X, size_t Y>
struct Add
{
	static const size_t value = Add<X - 1, Y + 1>::value;
};

template <size_t Y>
struct Add<0, Y>
{
	static const size_t value = Y;
};

template <size_t m, size_t n>
struct Ackermann
{
	static const size_t value = Ackermann<m - 1, Ackermann<m, n - 1>::value>::value;
};

template <size_t n>
struct Ackermann<0, n>
{
	static const size_t value = n + 1;
};

template <size_t m>
struct Ackermann<m, 0>
{
	static const size_t value = Ackermann<m - 1, 1>::value;
};