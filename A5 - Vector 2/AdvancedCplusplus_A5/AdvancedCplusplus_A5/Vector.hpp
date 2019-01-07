#pragma once
#include <cstdlib>
#include <iterator>
#include <stdexcept>
#include <vector>

#include "VectIter.hpp"

template<class T>
class Vector
{
private:
	std::allocator<T> _alloc = std::allocator<T>();
	T* _pointer;
	/*const T* const_pointer;*/
	size_t _size;
	size_t _capacity;

public:
	using value_type = T;
	using size_type = size_t;
	using difference_type = ptrdiff_t;
	using reference = T&;
	using const_reference = const T&;
	using pointer = T*;
	using const_pointer = const T*;
	using iterator = VectIter<T>;
	using const_iterator = VectIter<const T>;
	using reverse_iterator = std::reverse_iterator<VectIter<T>>;
	using const_reverse_iterator = std::reverse_iterator<VectIter<const T>>;

	//typedef  iterator_category;

	// O(1)
	Vector()
	{
		_size = 0;
		_capacity = 4;
		_pointer = _alloc.allocate(_capacity);
	}

	// O(N)
	~Vector()
	{
		for (size_t i = _size; i >= 0 ; --i)
		{
			_alloc.destroy(_alloc[i]);
		}
		_alloc.deallocate(_pointer, _capacity);
		_size = 0;
		_capacity = 0;
	}

	// O(n)
	Vector(const Vector& other)
	{
		this->~Vector();

		_capacity = other._capacity;
		_size = other._size;
		_pointer = new T[_capacity];

		for (size_t i = 0; i < _size; ++i)
		{
			_pointer[i] = other._pointer[i];
		}
	}

	// O(1)
	Vector(Vector&& other) noexcept
	{
		this->~Vector();

		_capacity = other._capacity;
		_size = other._size;
		_pointer = other._pointer;

		other._capacity = 0;
		other._size = 0;
		other._pointer = nullptr;
	}

	// O(n)
	template<class Titer>
	Vector(size_t newCapacity, const Titer& begin, const Titer& end)
	{
	}

	// O(n)
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

	// O(n)
	Vector& operator=(const Vector& other)
	{
		if (*this == other)
		{
			return *this;
		}

		if (_capacity != other._capacity)
		{
			this->~Vector();
			_capacity = other._capacity;
			_pointer = new T[_capacity];
		}
		_size = other._size;

		for (size_t i = 0; i < _size; ++i)
		{
			_pointer[i] = other._pointer[i];
		}

		return *this;
	}

	// O(n)
	Vector& operator=(Vector&& other) noexcept
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

	// O(1)
	T& operator[](size_t i)
	{
		return _pointer[i];
	}

	// O(1)
	T& at(size_t i)
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

	// O(1)
	const T& operator[](size_t i) const
	{
		return _pointer[i];
	}

	// O(1)
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

	// O(1)
	T* data() noexcept
	{
		return _pointer;
	}

	// O(1)
	const T* data() const noexcept
	{
		return _pointer;
	}

	// O(1)
	size_t size() const noexcept
	{
		return _size;
	}

	// O(n)
	void reserve(size_t n)
	{
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
	}

	// O(1)
	size_t capacity() const noexcept
	{
		return _capacity;
	}

	// O(n)
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

	// O(1) ammorterat och O(n) vid omallokering
	void push_back(const T& c)
	{
		if (_size == _capacity)
		{
			reserve(_capacity * 2);
		}

		_pointer[_size++] = c;
	}

	// O(1) ammorterat och O(n) vid omallokering
	void push_back(T&& c)
	{
		if (_size == _capacity)
		{
			reserve(_capacity * 2);
		}

		_pointer[_size++] = c;
	}

	// Inte med i uppgiften
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

	// O(1)
	iterator begin() const
	{
		return iterator(_pointer);
	}

	// O(1)
	const_iterator begin() const
	{
		return const_iterator(_pointer);
	}

	// O(1)
	reverse_iterator rbegin() const
	{
		return _pointer;
	}

	// O(1)
	const_reverse_iterator rbegin() const
	{
		return _pointer;
	}

	// O(1)
	iterator end() const
	{
		return (_pointer + _size);
	}

	// O(1)
	const_iterator end() const
	{
		return (_pointer + _size);
	}

	// O(1)
	reverse_iterator& rend() const
	{
		return (_pointer + _size);
	}

	// O(1)
	const_reverse_iterator& rend() const
	{
		return (_pointer + _size);
	}

	// O(n)
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

	void swap(Vector& rhs)
	{
		T temp(lhs);
		lhs = rhs;
		rhs = temp;
	}

	bool Invariant()
	{
		return (_size <= _capacity);
	}

	void Check() const
	{
		assert(Invariant());
	}
};

template <class T>
void swap(Vector<T>& lhs, Vector<T>& rhs)
{
	lhs.swap(rhs);
};