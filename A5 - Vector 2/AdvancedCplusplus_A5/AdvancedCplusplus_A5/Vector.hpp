#pragma once
#include <cstdlib>
#include <iterator>
#include <stdexcept>
#include <vector>
#include <cassert>

#include "VectIter.hpp"

template<class T>
class Vector
{
private:
	std::allocator<T> _alloc = std::allocator<T>();
	T* _pointer;
	size_t _size;
	size_t _capacity;

public:
	using value_type = T;
	using size_type = size_t;
	using difference_type = ptrdiff_t;
	using reference = T & ;
	using const_reference = const T&;
	using pointer = T * ;
	using const_pointer = const T*;
	using iterator = VectIter<T>;
	using const_iterator = VectIter<const T>;
	using reverse_iterator = std::reverse_iterator<VectIter<T>>;
	using const_reverse_iterator = std::reverse_iterator<VectIter<const T>>;

	// O(1) Done
	Vector()
	{
		_size = 0;
		_capacity = 4;
		_pointer = _alloc.allocate(_capacity);
		std::cout << "Ran default ctor." << std::endl;
	}

	// O(N) Done
	~Vector()
	{
		if (_capacity != 0)
		{
			_alloc.deallocate(_pointer, _capacity);
		}
		std::cout << "Ran destructor." << std::endl;
	}

	// O(n) Done
	Vector(const Vector& other)
	{
		_capacity = other._capacity;
		_size = other._size;
		_pointer = _alloc.allocate(_capacity);

		for (size_t i = 0; i < _size; ++i)
		{
			new(_pointer + i) T(other._pointer[i]);
		}

		std::cout << "Ran copy ctor." << std::endl;
	}

	// O(1) Done
	Vector(Vector&& other) noexcept
	{
		_capacity = other._capacity;
		_size = other._size;
		_pointer = other._pointer;

		other._capacity = 0;
		other._size = 0;
		other._pointer = nullptr;
		std::cout << "Ran move ctor." << std::endl;
	}

	// O(n) Done
	template<class Titer>
	Vector(size_t newCapacity, const Titer& begin, const Titer& end)
	{
		_capacity = newCapacity;
		_size = 0;
		_pointer = _alloc.allocate(_capacity);

		for (auto it = begin; it != end; ++it)
		{
			push_back(it);
		}

		std::cout << "Ran copy loop ctor." << std::endl;
	}

	// O(n) Done
	Vector(const char* other)
	{
		_size = 0;
		_capacity = 4;
		_pointer = _alloc.allocate(_capacity);

		int offset = 0;
		while (other[offset] != '\0')
		{
			std::cout << "Pushing! " << other[offset] << std::endl;
			push_back(other[offset]);
			++offset;
		}

		std::cout << "Ran char ctor." << std::endl;
	}

	// O(n) Done
	Vector& operator=(const Vector& other)
	{
		if (*this == other)
		{
			return *this;
		}

		if (_capacity < other._size)
		{
			this->~Vector();
			_capacity = other._size;
			_pointer = _alloc.allocate(_capacity);;
		}
		_size = other._size;

		for (size_t i = 0; i < _size; ++i)
		{
			new(_pointer + i) T(other._pointer[i]);
		}

		std::cout << "Ran copy operator." << std::endl;
		return *this;
	}

	// O(n) Done
	Vector& operator=(Vector&& other) noexcept
	{
		this->~Vector();

		_capacity = other._capacity;
		_size = other._size;
		_pointer = other._pointer;

		other._capacity = 0;
		other._size = 0;
		other._pointer = nullptr;

		std::cout << "Ran move operator." << std::endl;
		return *this;
	}

	// O(1) Done
	T& operator[](size_t i)
	{
		return _pointer[i];
	}

	// O(1) Done
	const T& operator[](size_t i) const
	{
		return _pointer[i];
	}

	// O(1) Done
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

	// O(1) Done
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

	// O(1) Done
	T* data() noexcept
	{
		return _pointer;
	}

	// O(1) Done
	const T* data() const noexcept
	{
		return _pointer;
	}

	// O(1) Done
	size_t size() const noexcept
	{
		return _size;
	}

	// O(n) Done
	void reserve(size_t n)
	{
		if (_capacity < n)
		{
			if (_pointer != nullptr)
			{
				T* newData = _alloc.allocate(n);
				for (size_t i = 0; i < _size; ++i)
				{
					new(newData + i) T(_pointer[i]);
				}
				_alloc.deallocate(_pointer, _capacity);
				_pointer = newData;
			}
			else
			{
				_pointer = _alloc.allocate(n);
				_size = 0;
			}
			_capacity = n;
		}
	}

	// O(1) Done
	size_t capacity() const noexcept
	{
		return _capacity;
	}

	// O(n) Done
	void shrink_to_fit()
	{
		T* out = _alloc.allocate(_size);
		for (size_t i = 0; i < _size; ++i)
		{
			new(out + i) T(_pointer[i]);
		}
		_alloc.deallocate(_pointer, _capacity);
		_capacity = _size;
		_pointer = out;
	}

	// O(1) ammorterat och O(n) vid omallokering Done
	void push_back(const T& c)
	{
		if (_size == _capacity)
		{
			reserve(_capacity * 2);
		}

		new(_pointer + _size) T(c);
		++_size;
	}

	// O(1) ammorterat och O(n) vid omallokering Done
	void push_back(T&& c)
	{
		if (_size == _capacity)
		{
			reserve(_capacity * 2);
		}

		new(_pointer + _size) T(std::move(c));
		++_size;
	}

	// Inte med i uppgiften Done
	/*void resize(size_t n)
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
	}*/

	// O(1)
	iterator begin() noexcept
	{
		return iterator(_pointer);
	}

	const_iterator begin() const noexcept
	{
		return const_iterator(_pointer);
	}

	// O(1)
	const_iterator cbegin() const noexcept
	{
		return const_iterator(_pointer);
	}

	// O(1)
	reverse_iterator rbegin() noexcept
	{
		return reverse_iterator(_pointer + _size);
	}

	// O(1)
	const_reverse_iterator rbegin() const noexcept
	{
		return const_reverse_iterator(_pointer + _size);
	}

	// O(1)
	const_reverse_iterator crbegin() const noexcept
	{
		return const_reverse_iterator(_pointer + _size);
	}

	// O(1)
	iterator end() noexcept
	{
		return iterator(_pointer + _size);
	}

	// O(1)
	const_iterator end() const noexcept
	{
		return const_iterator(_pointer + _size);
	}

	// O(1)
	const_iterator cend() const noexcept
	{
		return const_iterator(_pointer + _size);
	}

	// O(1)
	reverse_iterator rend() noexcept
	{
		return reverse_iterator(_pointer);
	}

	// O(1)
	const_reverse_iterator rend() const noexcept
	{
		return const_reverse_iterator(_pointer);
	}

	// O(1)
	const_reverse_iterator crend() const noexcept
	{
		return const_reverse_iterator(_pointer);
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

		// Sök efter skillnader i datan
		for (size_t i = 0; i < loopSize; ++i)
		{
			if (lhs[i] == other[i])
			{
				continue;
			}

			return (lhs[i] < other[i]); // Hittade skillnad i datan
		}

		return (lhs.size() < other.size()); // Om datan är lika men har olika size
	}

	friend bool operator>(const Vector& lhs, const Vector& other)
	{
		// Hitta den minsta vektor storleken
		size_t loopSize = lhs.size();
		if (other.size() < loopSize)
		{
			loopSize = other.size();
		}

		// Sök efter skillnader i datan
		for (size_t i = 0; i < loopSize; ++i)
		{
			if (lhs[i] == other[i])
			{
				continue;
			}

			return (lhs[i] > other[i]); // Hittade skillnad i datan
		}

		return (lhs.size() > other.size()); // Om datan är lika men har olika size
	}

	friend bool operator<=(const Vector& lhs, const Vector& other)
	{
		return !(lhs > other);
	}

	friend bool operator>=(const Vector& lhs, const Vector& other)
	{
		return !(lhs < other);
	}

	bool Invariant() const
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
	Vector<T> temp(lhs);
	lhs = rhs;
	rhs = temp;
};