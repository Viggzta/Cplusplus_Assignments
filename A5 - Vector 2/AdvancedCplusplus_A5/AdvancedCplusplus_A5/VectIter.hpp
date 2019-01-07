#pragma once
#include <iterator>
#include <cstddef>

template <class T>
class VectIter
{
private:
	T* _index;

public:
	using iterator_category = std::random_access_iterator_tag;
	using value_type = std::remove_const_t<T>;
	using difference_type = ptrdiff_t;
	using pointer = T*;
	using reference = T&;

	VectIter(T* p)
	{
		_index = p;
	}

	VectIter()
	{
		_index = nullptr;
	}

	VectIter(const VectIter& other)
	{
		_index = other._index;
	}

	VectIter& operator=(const VectIter& other)
	{
		_index = other._index;
		return *this;
	}

	T& operator*()
	{
		return *_index;
	}

	T* operator->()
	{
		return _index;
	}

	T& operator[](size_t i)
	{
		return _index[i];
	}

	VectIter& operator++()
	{
		++_index;
		return *this;
	}

	VectIter& operator--()
	{
		--_index;
		return *this;
	}

	VectIter operator++(int)
	{
		VectIter out = *this;
		++_index;
		return out;
	}

	VectIter operator--(int)
	{
		VectIter out = *this;
		--_index;
		return out;
	}

	VectIter operator+(ptrdiff_t i) const
	{
		return (_index + i);
	}

	VectIter operator-(ptrdiff_t i) const
	{
		return (_index - i);
	}

	ptrdiff_t operator-(const VectIter& other) const
	{
		return (_index - other._index);
	}

	friend bool operator==(const VectIter& lhs, const VectIter& rhs)
	{
		if (lhs._index == rhs._index)
		{
			return true;
		}

		return false;
	}

	friend bool operator!=(const VectIter& lhs, const VectIter& rhs)
	{
		if (lhs._index == rhs._index)
		{
			return false;
		}

		return true;
	}

	friend bool operator<(const VectIter& lhs, const VectIter& rhs)
	{
		if (lhs._index - rhs._index < 0)
		{
			return true;
		}

		return false;
	}

	friend bool operator>(const VectIter& lhs, const VectIter& rhs)
	{
		if (rhs._index - lhs._index < 0)
		{
			return true;
		}

		return false;
	}

	friend bool operator<=(const VectIter& lhs, const VectIter& rhs)
	{
		return !(lhs._index > rhs._index);
	}

	friend bool operator>=(const VectIter& lhs, const VectIter& rhs)
	{
		return !(lhs._index < rhs._index);
	}
};