#include "Vector.h"

template<class T>
Vector<T>::Vector()
{
}

template<class T>
Vector<T>::~Vector()
{
}

template<class T>
Vector<T>::Vector(const Vector & other)
{
}

template<class T>
Vector<T>::Vector(Vector && other)
{
}

template<class T>
Vector<T>::Vector(const std::vector & other)
{
}

template<class T>
Vector & Vector<T>::operator=(const Vector & other)
{
	// TODO: insert return statement here
}

template<class T>
Vector & Vector<T>::operator=(Vector && other)
{
	// TODO: insert return statement here
}

template<class T>
T & Vector<T>::operator[](size_t i)
{
	// TODO: insert return statement here
}

template<class T>
T & Vector<T>::at(size_t i)
{
	// TODO: insert return statement here
}

template<class T>
T * Vector<T>::data() noexcept
{
	return nullptr;
}

template<class T>
const T * Vector<T>::data() const noexcept
{
	return nullptr;
}

template<class T>
size_t Vector<T>::size() const noexcept
{
	return size_t();
}

template<class T>
void Vector<T>::reserve(size_t n)
{
}

template<class T>
size_t Vector<T>::capacity() const noexcept
{
	return size_t();
}

template<class T>
void Vector<T>::shrink_to_fit()
{
}

template<class T>
void Vector<T>::push_back(T c)
{
}

template<class T>
void Vector<T>::resize(size_t n)
{
}

template<class T>
iterator Vector<T>::begin() const
{
	return iterator();
}

template<class T>
iterator Vector<T>::end() const
{
	return iterator();
}

template<class T>
void Vector<T>::swap(Vector& lhs, Vector& rhs)
{
}

template<class T>
bool operator==(const Vector & lhs, const Vector & other)
{
	return false;
}

template<class T>
bool operator!=(const Vector & lhs, const Vector & other)
{
	return false;
}

template<class T>
bool operator<(const Vector & lhs, const Vector & other)
{
	return false;
}

template<class T>
bool operator>(const Vector & lhs, const Vector & other)
{
	return false;
}

template<class T>
bool operator<=(const Vector & lhs, const Vector & other)
{
	return false;
}

template<class T>
bool operator>=(const Vector & lhs, const Vector & other)
{
	return false;
}
