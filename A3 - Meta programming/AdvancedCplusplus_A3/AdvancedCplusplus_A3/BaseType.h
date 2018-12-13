template<class T>
struct Simplifytype
{
	using type = T;
};

template<class T>
struct Simplifytype<T*>
{
	using type = T;
};

template<class T>
struct Simplifytype<T&>
{
	using type = T;
};

template<class T>
struct Simplifytype<const T>
{
	using type = T;
};

template<class T>
struct Simplifytype<const T*>
{
	using type = const T;
};

template<class T>
struct Simplifytype<const T&>
{
	using type = const T;
};

template<class T>
using SimplifyType_t = typename Simplifytype<T>::type;

// Base type

template<class T>
struct BaseType
{
	using type = T;
};

template<class T>
struct BaseType<T*>
{
	using type = typename BaseType<T>::type;
};

template<class T>
struct BaseType<T&>
{
	using type = typename BaseType<T>::type;
};

template<class T>
struct BaseType<const T>
{
	using type = typename BaseType<T>::type;
};

template<class T>
using BaseType_t = typename BaseType<T>::type;