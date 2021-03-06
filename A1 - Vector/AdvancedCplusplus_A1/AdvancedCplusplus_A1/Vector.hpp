#pragma once
#include <cstdlib>
#include <iterator>
#include <stdexcept>
#include <cassert>
#include <vector>

#include "VectorIter.hpp"

template<class T>
class Vector : std::iterator<std::random_access_iterator_tag, T, ptrdiff_t, T*, T&>
{
private:
	T * _pointer;
	size_t _size;
	size_t _capacity;

public:

	using iterator = VectorIter<T>;

	Vector()
	{
		_size = 0;
		_capacity = 4;
		_pointer = new T[_capacity];
	}

	~Vector()
	{
		delete[] _pointer;
	}

	Vector(const Vector& other)
	{
		_capacity = other._capacity;
		_size = other._size;
		_pointer = new T[_capacity];

		for (size_t i = 0; i < _size; ++i)
		{
			_pointer[i] = other._pointer[i];
		}
	}

	Vector(Vector&& other)
	{
		_capacity = other._capacity;
		_size = other._size;
		_pointer = other._pointer;

		other._capacity = 0;
		other._size = 0;
		other._pointer = nullptr;
	}

	Vector(const char* other)
	{
		_size = 0;
		_capacity = 4;
		_pointer = new T[_capacity];

		int offset = 0;
		while (other[offset] != '\0')
		{
			//std::cout << "Pushing! " << other[offset] << std::endl;
			push_back(other[offset]);
			++offset;
		}
	}

	Vector& operator=(const Vector& other)
	{
		if (*this == other)
		{
			return *this;
		}

		if (_capacity < other._size) // J�mf�r med size ist�llet >=
		{
			this->~Vector();
			_capacity = other._size;
			_pointer = new T[_capacity];
		}
		_size = other._size;

		for (size_t i = 0; i < _size; ++i)
		{
			_pointer[i] = other._pointer[i];
		}

		return *this;
	}

	Vector& operator=(Vector&& other)
	{
		this->~Vector();

		_capacity = other._capacity;
		_size = other._size;
		_pointer = other._pointer;

		other._capacity = 0;
		other._size = 0;
		other._pointer = nullptr;

		return *this;
	}

	T& operator[](size_t i)
	{
		return _pointer[i];
	}

	T& at(size_t i)
	{
		if (i >= _size)
		{
			throw std::out_of_range("");
		}
		return _pointer[i];
	}

	const T& operator[](size_t i) const
	{
		return _pointer[i];
	}

	const T& at(size_t i) const
	{
		if (i >= _size)
		{
			throw std::out_of_range("");
		}
		else
		{
			return _pointer[i];
		}
	}

	T* data() noexcept
	{
		return _pointer;
	}

	const T* data() const noexcept
	{
		return _pointer;
	}

	size_t size() const noexcept
	{
		return _size;
	}

	void reserve(size_t n)
	{
		if (_capacity < n)
		{
			T* newData = new T[n];
			for (size_t i = 0; i < _size; ++i)
			{
				newData[i] = _pointer[i];
			}

			delete[] _pointer;

			_pointer = newData;
			_capacity = n;
		}
	}

	size_t capacity() const noexcept
	{
		return _capacity;
	}

	void shrink_to_fit()
	{
		T* out = new T[_size];
		for (size_t i = 0; i < _size; ++i)
		{
			out[i] = _pointer[i];
		}
		delete[] _pointer;
		_capacity = _size;
		_pointer = out;

	}

	void push_back(T c)
	{
		if (_size == _capacity)
		{
			reserve(_capacity * 2);
		}

		_pointer[_size++] = c;
	}

	void resize(size_t n)
	{
		if (n > _capacity)
		{
			reserve(n);
		}
		if (n > _size)
		{
			for (size_t i = _size; i < n; ++i)
			{
				_pointer[i] = T();
			}
		}
		_size = n;
	}

	iterator begin() const
	{
		return _pointer;
	}

	iterator end() const
	{
		return (_pointer + _size);
	}

	friend bool operator==(const Vector& lhs, const Vector& other)
	{
		if (lhs.size() != other.size())
		{
			return false;
		}
		for (size_t i = 0; i < other.size(); ++i)
		{
			if (lhs[i] != other[i])
			{
				return false;
			}
		}
		return true;
	}

	friend bool operator!=(const Vector& lhs, const Vector& other)
	{
		return !(lhs == other);
	}

	friend bool operator<(const Vector& lhs, const Vector& other)
	{
		// Hitta den minsta vektor storleken
		size_t loopSize = lhs.size();
		if (other.size() < loopSize)
		{
			loopSize = other.size();
		}

		// S�k efter skillnader i datan
		for (size_t i = 0; i < loopSize; ++i)
		{
			if (lhs[i] == other[i])
			{
				continue;
			}

			return (lhs[i] < other[i]); // Hittade skillnad i datan
		}

		return (lhs.size() < other.size()); // Om datan �r lika men har olika size
	}

	friend bool operator>(const Vector& lhs, const Vector& other)
	{
		// Hitta den minsta vektor storleken
		size_t loopSize = lhs.size();
		if (other.size() < loopSize)
		{
			loopSize = other.size();
		}

		// S�k efter skillnader i datan
		for (size_t i = 0; i < loopSize; ++i)
		{
			if (lhs[i] == other[i])
			{
				continue;
			}

			return (lhs[i] > other[i]); // Hittade skillnad i datan
		}

		return (lhs.size() > other.size()); // Om datan �r lika men har olika size
	}

	friend bool operator<=(const Vector& lhs, const Vector& other)
	{
		return !(lhs > other);
	}

	friend bool operator>=(const Vector& lhs, const Vector& other)
	{
		return !(lhs < other);
	}

	void swap(Vector& lhs, Vector& rhs)
	{
		T temp(lhs);
		lhs = rhs;
		rhs = temp;
	}

	bool Invariant() const
	{
		if (_pointer == nullptr)
		{
			return false;
		}

		return (_size <= _capacity);
	}

	void Check() const
	{
		assert(Invariant());
	}

	// Testing
	friend std::ostream& operator<<(std::ostream& cout, const Vector& other)
	{
		for (size_t i = 0; i < other.size(); ++i)
			cout << other[i];
		return cout;
	};
};