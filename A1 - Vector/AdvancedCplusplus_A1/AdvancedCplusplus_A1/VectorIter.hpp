#pragma once
#include <iterator>
#include <cstddef>

template <class T>
class VectorIter : std::iterator<std::random_access_iterator_tag, T, ptrdiff_t, T*, T&>
{

private:
	T * _index;
	T * _start;

public:
	typedef T value_type;
	typedef ptrdiff_t difference_type;
	typedef T* pointer;
	typedef T& reference;
	typedef std::random_access_iterator_tag iterator_category;

	VectorIter(T* p)
	{
		_start = p;
		_index = p;
	}

	VectorIter()
	{
		_start = nullptr;
		_index = nullptr;
	}

	VectorIter(const VectorIter& other)
	{
		_start = other._start;
		_index = other._index;
	}

	VectorIter& operator=(const VectorIter& other)
	{
		_start = other._start;
		_index = other._index;
		return *this;
	}

	T & operator*()
	{
		return *_index;
	}

	T* operator->()
	{
		return _index;
	}

	T& operator[](size_t i)
	{
		return _start[i];
	}

	VectorIter& operator++()
	{
		++_index;
		return *this;
	}

	VectorIter& operator--()
	{
		--_index;
		return *this;
	}

	VectorIter operator++(int)
	{
		VectorIter out = *this;
		++_index;
		return out;
	}

	VectorIter operator--(int)
	{
		VectorIter out = *this;
		--_index;
		return out;
	}

	VectorIter operator+(ptrdiff_t i) const
	{
		return (_index + i);
	}

	VectorIter operator-(ptrdiff_t i) const
	{
		return (_index - i);
	}

	ptrdiff_t operator-(const VectorIter& other) const
	{
		return (_index - other._index);
	}

	friend bool operator==(const VectorIter& lhs, const VectorIter& rhs)
	{
		if (lhs._start == rhs._start)
		{
			return true;
		}

		return false;
	}

	friend bool operator!=(const VectorIter& lhs, const VectorIter& rhs)
	{
		if (lhs._start == rhs._start)
		{
			return false;
		}

		return true;
	}

	friend bool operator<(const VectorIter& lhs, const VectorIter& rhs)
	{
		if (lhs._index - rhs._index < 0)
		{
			return true;
		}

		return false;
	}

	friend bool operator>(const VectorIter& lhs, const VectorIter& rhs)
	{
		if (rhs._index - lhs._index < 0)
		{
			return true;
		}

		return false;
	}

	friend bool operator<=(const VectorIter& lhs, const VectorIter& rhs)
	{
		return !(lhs._index > rhs._index);
	}

	friend bool operator>=(const VectorIter& lhs, const VectorIter& rhs)
	{
		return !(lhs._index < rhs._index);
	}
};