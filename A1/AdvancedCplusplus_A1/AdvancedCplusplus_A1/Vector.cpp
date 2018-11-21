#include <cstdlib>
#include <iterator>
#include <stdexcept>
#include <vector>

#include "Vector.h"

template<class T>
Vector<T>::Vector()
{
	if (pointer != nullptr)
	{
		delete &pointer;
	}

	size_type = 0;
	capacity_type = 4;
	pointer = new T[capacity_type];
}

template<class T>
Vector<T>::~Vector()
{
	if (pointer != nullptr)
	{
		delete &pointer;
	}
}

template<class T>
Vector<T>::Vector(const Vector & other)
{
	if (pointer != nullptr)
	{
		delete &pointer;
	}

	capacity_type = other.capacity;
	size_type = other.size_type;
	pointer = new T[capacity_type];
}

template<class T>
Vector<T>::Vector(Vector && other)
{
	if (pointer != nullptr)
	{
		delete &pointer;
	}

	capacity_type = other.capacity_type;
	size_type = other.size_type;
	pointer = new T[capacity_type];
}

template<class T>
Vector<T>::Vector(const char & other)
{
	Vector();
	push_back(other);
}

template<class T>
Vector<T> & Vector<T>::operator=(const Vector<T> & other)
{
	if (pointer != nullptr)
	{
		delete &pointer;
	}

	capacity_type = other.capacity_type;
	size_type = other.size_type;
	pointer = new T[capacity_type];
	return *this;
}

template<class T>
Vector<T> & Vector<T>::operator=(Vector<T> && other)
{
	if (pointer != nullptr)
	{
		delete &pointer;
	}

	if (pointer != nullptr)
	{
		delete &pointer;
	}

	capacity_type = other.capacity_type;
	size_type = other.size_type;
	pointer = new T[capacity_type];
	return *this;
}

template<class T>
T & Vector<T>::operator[](size_t i)
{
	if (i >= size_type)
	{
		throw std::out_of_range("Vector<T>::at(size_t i) : Index out of range.");
	}
	return pointer + i;
}

template<class T>
T & Vector<T>::at(size_t i)
{
	if (i >= size_type)
	{
		throw std::out_of_range("Vector<T>::at(size_t i) : Index out of range.");
	}
	return pointer + i;
}

template<class T>
T * Vector<T>::data() noexcept
{
	return pointer;
}

template<class T>
const T * Vector<T>::data() const noexcept
{
	return pointer;
}

template<class T>
size_t Vector<T>::size() const noexcept
{
	return size_type;
}

template<class T>
void Vector<T>::reserve(size_t n) // TODO: Refector
{
	if (capacity_type < n)
	{
		if (pointer != nullptr)
		{
			T* newData = new T[n];
			memcopy(newData, pointer, size_type);
			delete &pointer;
			pointer = newData;
		}
		else
		{
			pointer = new T[n];
			size_type = 0;
		}
		capacity_type = n;
	}
}

template<class T>
size_t Vector<T>::capacity() const noexcept
{
	return capacity_type;
}

template<class T>
void Vector<T>::shrink_to_fit()
{
	resize(size_type);
}

template<class T>
void Vector<T>::push_back(T c)
{
	if (size_type == capacity_type)
	{
		reserve(capacity_type * 2);
	}

	&(pointer + size_type) = c;
	++size_type;
}

template<class T>
void Vector<T>::resize(size_t n)
{
	T* t = new T[n];
	memcpy(t.begin(), begin(), n);
	delete &pointer;
	pointer = t;
	capacity_type = n;
	if (n < size_type)
	{
		size_type = n;
	}
}

template<class T>
iterator Vector<T>::begin() const
{
	return pointer;
}

template<class T>
iterator Vector<T>::end() const
{
	return pointer + size_type;
}

template<class T>
void Vector<T>::swap(Vector& lhs, Vector& rhs)
{
	T temp(lhs);
	lhs = rhs;
	rhs = temp;
}

template<class T>
bool operator==(const Vector & lhs, const Vector & other)
{
	if (lhs.size() != other.size())
	{
		return false;
	}
	for (size_t i = 0; i < other.size(); ++i)
	{
		if (lhs[i] != rhs[i])
		{
			return false;
		}
	}
	return true;
}

template<class T>
bool operator!=(const Vector & lhs, const Vector & other)
{
	if (lhs.size() != other.size())
	{
		return true;
	}
	for (size_t i = 0; i < other.size(); ++i)
	{
		if (lhs[i] != rhs[i])
		{
			return true;
		}
	}
	return false;
}

template<class T>
bool operator<(const Vector & lhs, const Vector & other)
{
	if (lhs.size() < other.size())
	{
		return true;
	}
	return false;
}

template<class T>
bool operator>(const Vector & lhs, const Vector & other)
{
	if (lhs.size() > other.size())
	{
		return true;
	}
	return false;
}

template<class T>
bool operator<=(const Vector & lhs, const Vector & other)
{
	return !(lhs.size() > rhs.size());
}

template<class T>
bool operator>=(const Vector & lhs, const Vector & other)
{
	return !(lhs.size() < rhs.size());
}
