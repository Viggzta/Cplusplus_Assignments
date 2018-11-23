#pragma once
#include <iterator>

template <class T>
class VectorIter : std::iterator<std::random_access_iterator_tag, T, int>
{
	template <VectorIter>
	struct IteratorTraits
	{
		using value_type = typename VectorIter::value_type;
		using difference_type = typename VectorIter::difference_type;
	};

	template<class T>
	struct IteratorTraits<T*>
	{
		using value_type = typename T;
		using difference_type = std::ptrdiff_t;
	};

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
		return &(start + i);
	}

	VectorIter& operator++()
	{
		return ++index;
	}

	VectorIter& operator--()
	{
		return --index;
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

	VectorIter operator+(difference_type i) const
	{
		return (index + i);
	}

	VectorIter operator-(difference_type i) const
	{
		return (index - i);
	}

	difference_type operator-(const VectorIter&) const
	{
		return std::distance(this, other);
	}

	friend bool operator==(const VectorIter& lhs, const VectorIter& rhs)
	{
		if (lhs.start == rhs.start)
		{
			return true;
		}

		return false;
	}
};