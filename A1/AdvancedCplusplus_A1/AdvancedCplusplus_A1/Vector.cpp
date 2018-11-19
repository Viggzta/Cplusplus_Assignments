#include "Vector.h"
#include <stdexcept>

template<class T>
Vector<T>::Vector()
{
	size_type = 4;
	pointer = new T[size_type];
}

template<class T>
Vector<T>::~Vector()
{
	delete &pointer;
}

template<class T>
Vector<T>::Vector(const Vector & other)
{
	if (pointer != nullptr)
	{
		delete &pointer;
	}

	size_type = other.size_type;
	pointer = new T[size_type];
}

template<class T>
Vector<T>::Vector(Vector && other)
{
	if (pointer != nullptr)
	{
		delete &pointer;
	}

	size_type = other.size_type;
	pointer = new T[size_type];
}

template<class T>
Vector<T>::Vector(const std::vector & other)
{
}

template<class T>
Vector & Vector<T>::operator=(const Vector & other)
{
}

template<class T>
Vector & Vector<T>::operator=(Vector && other)
{
	// TODO: insert return statement here
}

template<class T>
T & Vector<T>::operator[](size_t i)
{
	if (i >= this->size())
	{
		throw std::out_of_range("Vector<T>::at(size_t i) : Index out of range.");
	}
	return pointer + i;
}

template<class T>
T & Vector<T>::at(size_t i)
{
	if (i >= this->size())
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
	return data->size();
}

template<class T>
void Vector<T>::reserve(size_t n)
{
	// TODO: Add this
}

template<class T>
size_t Vector<T>::capacity() const noexcept
{
	return size_type * T.capacity();
}

template<class T>
void Vector<T>::shrink_to_fit()
{
	// TODO: Add this
}

template<class T>
void Vector<T>::push_back(T c)
{
	data->push_back(std::move(c));
}

template<class T>
void Vector<T>::resize(size_t n)
{
	T* t = new T[n];
	memcpy(t.begin(), begin(), size()); // TODO: If memcpy doesn't stop at t.end() then write how we should handle this.
	delete &pointer;
	pointer = t;
}

template<class T>
iterator Vector<T>::begin() const
{
	return pointer;
}

template<class T>
iterator Vector<T>::end() const
{
	return pointer + size();
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
