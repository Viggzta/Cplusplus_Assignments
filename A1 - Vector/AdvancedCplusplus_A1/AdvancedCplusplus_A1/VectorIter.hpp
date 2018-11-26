#pragma once
#include <iterator>
#include <cstddef>

template <class T>
class VectorIter : std::iterator<std::random_access_iterator_tag, T, ptrdiff_t>
{
	/*template <VectorIter>
	struct IteratorTraits
	{
		using value_type = typename VectorIter::value_type;
		using difference_type = typename VectorIter::difference_type;
	};

	template<class T>
	struct IteratorTraits<T*>
	{
		using value_type = typename T;
		using difference_type = ptrdiff_t;
	};*/

private:
	T * index;
	T * start;

public:
	VectorIter(T* p)
	{
		start = p;
		index = p;
	}

	VectorIter()
	{
		start = nullptr;
		index = nullptr;
	}

	VectorIter(const VectorIter& other)
	{
		start = *other;
		index = *other;
	}

	VectorIter& operator=(const VectorIter& other)
	{
		start = *other;
		index = *other;
	}

	T & operator*()
	{
		return &index;
	}

	T* operator->()
	{
		return index;
	}

	T& operator[](size_t i)
	{
		T* a = start + i;
		//T out = &a;
		return a;
	}

	VectorIter& operator++()
	{
		VectorIter out = ++index;
		return out;
	}

	VectorIter& operator--()
	{
		VectorIter out = --index;
		return out;
	}

	VectorIter operator++(int)
	{
		VectorIter out = index;
		++index;
		return out;
	}

	VectorIter operator--(int)
	{
		VectorIter out = index;
		--index;
		return out;
	}

	VectorIter operator+(ptrdiff_t i) const
	{
		return (index + i);
	}

	VectorIter operator-(ptrdiff_t i) const
	{
		return (index - i);
	}

	ptrdiff_t operator-(const VectorIter& other) const
	{
		return (index - other.index);
	}

	friend bool operator==(const VectorIter& lhs, const VectorIter& rhs)
	{
		if (lhs.start == rhs.start)
		{
			return true;
		}

		return false;
	}

	friend bool operator!=(const VectorIter& lhs, const VectorIter& rhs)
	{
		if (lhs.start == rhs.start)
		{
			return false;
		}

		return true;
	}
};