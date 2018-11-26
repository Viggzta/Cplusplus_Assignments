#pragma once
#include <cstdlib>
#include <iterator>
#include <stdexcept>
#include <vector>

#include "VectorIter.hpp"

template<class T>
class Vector : std::iterator<std::random_access_iterator_tag, T>
{
private:
	//typedef T value_type;
	T* pointer;
	const T* const_pointer;
	size_t size_type;
	size_t capacity_type;

public:
	using iterator = VectorIter<T>;
	Vector()
	{
		if (pointer != nullptr)
		{
			delete &pointer;
		}

		size_type = 0;
		capacity_type = 4;
		pointer = new T[capacity_type];
	}

	~Vector()
	{
		if (pointer != nullptr)
		{
			delete &pointer;
		}
	}

	Vector(const Vector& other)
	{
		if (pointer != nullptr)
		{
			delete &pointer;
		}

		capacity_type = other.capacity;
		size_type = other.size_type;
		pointer = new T[capacity_type];
	}

	Vector(Vector&& other)
	{
		if (pointer != nullptr)
		{
			delete &pointer;
		}

		capacity_type = other.capacity_type;
		size_type = other.size_type;
		pointer = new T[capacity_type];
	}

	Vector(const char* other)
	{
		Vector<char>();

		int offset = 0;
		while ((other +offset) != '\0')
		{
			push_back((other +offset));
		}
	}

	Vector& operator=(const Vector& other)
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

	Vector& operator=(Vector&& other)
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

	T& operator[](size_t i) const
	{
		if (i >= size_type)
		{
			throw std::out_of_range("Vector::at(size_t i) : Index out of range.");
		}
		return &(pointer + i);
	}

	T& at(size_t i) const
	{
		if (i >= size_type)
		{
			throw std::out_of_range("Vector::at(size_t i) : Index out of range.");
		}
		return &(pointer + i);
	}

	T* data() noexcept
	{
		return pointer;
	}

	const T* data() const noexcept
	{
		return pointer;
	}

	size_t size() const noexcept
	{
		return size_type;
	}

	void reserve(size_t n)
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

	size_t capacity() const noexcept
	{
		return capacity_type;
	}

	void shrink_to_fit()
	{
		resize(size_type);
	}

	void push_back(T c)
	{
		if (size_type == capacity_type)
		{
			reserve(capacity_type * 2);
		}

		T* temp = pointer + size_type;
		&temp = c;
		++size_type;
	}

	void resize(size_t n)
	{
		T* t = new T[n];
		memcpy(t, pointer, n);
		delete pointer;
		pointer = t;
		capacity_type = n;
		if (n < size_type)
		{
			size_type = n;
		}
	}

	iterator begin() const
	{
		return pointer;
	}

	iterator end() const
	{
		return pointer + size_type;
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
		if (lhs.size() < other.size())
		{
			return true;
		}
		return false;
	}

	friend bool operator>(const Vector& lhs, const Vector& other)
	{
		if (lhs.size() > other.size())
		{
			return true;
		}
		return false;
	}

	friend bool operator<=(const Vector& lhs, const Vector& other)
	{
		return !(lhs.size() > other.size());
	}

	friend bool operator>=(const Vector& lhs, const Vector& other)
	{
		return !(lhs.size() < other.size());
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