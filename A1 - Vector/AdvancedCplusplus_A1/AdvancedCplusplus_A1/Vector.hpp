#pragma once
#include <cstdlib>
#include <iterator>
#include <stdexcept>
#include <vector>

#include "VectorIter.hpp"

template<class T>
class Vector : std::iterator<std::random_access_iterator_tag, T, ptrdiff_t, T*, T&>
{
private:
	T* _pointer;
	const T* const_pointer;
	size_t _size;
	size_t _capacity;

public:

	using iterator = VectorIter<T>;

	Vector()
	{
		_size = 0;
		_capacity = 4;
		_pointer = new T[_capacity];

		std::cout << "Ran default ctor!" << std::endl;
	}

	~Vector()
	{
		if (_pointer != nullptr)
		{
			delete[] _pointer;

			_size = 0;
			_capacity = 0;
			std::cout << "Ran destructor!" << std::endl;
		}
	}

	Vector(const Vector& other)
	{
		this->~Vector();

		_capacity = other._capacity;
		_size = other._size;
		_pointer = new T[_capacity];

		std::cout << "Ran copy ctor!" << std::endl;
	}

	Vector(Vector&& other)
	{
		this->~Vector();

		_capacity = other._capacity;
		_size = other._size;
		_pointer = new T[_capacity];

		std::cout << "Ran move ctor!" << std::endl;
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

		std::cout << "Ran char ctor!" << std::endl;
	}

	Vector& operator=(const Vector& other)
	{
		this->~Vector();

		_capacity = other._capacity;
		_size = other._size;
		_pointer = new T[_capacity];
		return *this;

		std::cout << "Ran assign ctor1!" << std::endl;
	}

	Vector& operator=(Vector&& other)
	{
		this->~Vector();

		_capacity = other._capacity;
		_size = other._size;
		_pointer = new T[_capacity];
		return *this;

		std::cout << "Ran assign ctor2!" << std::endl;
	}

	T& operator[](size_t i) const
	{
		if (i >= _size || i < 0)
		{
			throw std::out_of_range("Vector::at(size_t i) : Index out of range.");
		}
		return _pointer[i];
	}

	T& at(size_t i) const
	{
		if (i >= _size)
		{
			throw std::out_of_range("Vector::at(size_t i) : Index out of range.");
		}
		return _pointer[i];
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
		std::cout << "Starting reserve!" << std::endl;
		if (_capacity < n)
		{
			if (_pointer != nullptr)
			{
				T* newData = new T[n];
				for (size_t i = 0; i < _size; ++i)
				{
					newData[i] = _pointer[i];
				}

				delete[] _pointer;

				_pointer = newData;
			}
			else
			{
				_pointer = new T[n];
				_size = 0;
			}
			_capacity = n;
		}
		std::cout << "Ending reserve!" << std::endl;
	}

	size_t capacity() const noexcept
	{
		return _capacity;
	}

	void shrink_to_fit()
	{
		resize(_size);
	}

	void push_back(T c)
	{
		if (_size == _capacity)
		{
			reserve(_capacity * 2);
		}

		std::cout << "Size when pushing: " << _size << std::endl;
		_pointer[_size++] = c;
	}

	void resize(size_t n)
	{
		T* t = new T[n];
		memcpy(t, _pointer, n);
		this->~Vector();
		_pointer = t;
		_capacity = n;
		if (n < _size)
		{
			_size = n;
		}
		std::cout << "Ran resize!" << std::endl;
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
		if (lhs.size() != other.size())
		{
			return true;
		}
		for (size_t i = 0; i < other.size(); ++i)
		{
			if (lhs[i] != other[i])
			{
				return true;
			}
		}
		return false;
	}

	friend bool operator<(const Vector& lhs, const Vector& other)
	{
		for (size_t i = 0; i < other.size(); ++i)
		{
			if (lhs[i] == other[i])
			{
				continue;
			}

			if (lhs[i] < other[i])
			{
				return true;
			}
			else
			{
				return false;
			}
		}

		return false;
	}

	friend bool operator>(const Vector& lhs, const Vector& other)
	{
		for (size_t i = 0; i < other.size(); ++i)
		{
			if (lhs[i] == other[i])
			{
				continue;
			}

			if (lhs[i] > other[i])
			{
				return true;
			}
			else
			{
				return false;
			}
		}

		return false;
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

	// Testing
	friend std::ostream& operator<<(std::ostream& cout, const Vector& other)
	{
		for (size_t i = 0; i < other.size(); ++i)
			cout << other[i];
		return cout;
	};
};