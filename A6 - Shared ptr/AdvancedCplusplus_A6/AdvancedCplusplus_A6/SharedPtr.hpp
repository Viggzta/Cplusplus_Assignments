#pragma once

#include <cassert>
#include <iostream>

template <class T>
class SharedPtr
{
private:
	T* _pointer;
	int* _refCount;

	void removeRef()
	{
		if (*_refCount != 0)
		{
			--*_refCount;
		}
		if (*_refCount == 0)
		{
			std::cout << "Refrence is dead!" << std::endl;
			delete _pointer;
			delete _refCount;
		}
	}

public:
	SharedPtr()
	{
		_pointer = nullptr;
		_refCount = new int(0);

		std::cout << "Ran void ctor. " << *_refCount << std::endl;
	}

	SharedPtr(T* other)
	{
		if (_refCount != 0)
		{
			removeRef();
		}

		_pointer = other;
		_refCount = new int(1);

		std::cout << "Ran assign ctor. " << *_refCount << std::endl;
	}

	SharedPtr(SharedPtr& other)
	{
		if (*this == other)
		{
			return;
		}

		if (_refCount != nullptr)
		{
			removeRef();
		}

		_pointer = other._pointer;
		_refCount = other._refCount;
		++*_refCount;

		std::cout << "Ran copy ctor. " << *_refCount << std::endl;
	}

	SharedPtr(SharedPtr&& other)
	{
		if (*this == other)
		{
			return;
		}

		_pointer = other._pointer;
		_refCount = other._refCount;

		other._pointer = nullptr;
		other._refCount = new int(0);

		std::cout << "Ran move ctor. " << *_refCount << std::endl;
	}

	~SharedPtr()
	{
		if (_refCount != nullptr)
		{
			std::cout << "Ran destructor. " << *_refCount << std::endl;
		}
		else
		{
			std::cout << "Ran destructor. nullptr" << std::endl;
		}

		if (_refCount != nullptr)
		{
			if (--*_refCount == 0)
			{
				delete _pointer;
				delete _refCount;
			}
		}
	}

	SharedPtr* operator=(SharedPtr& other)
	{
		if (*this == other)
		{
			return this;
		}

		if (_refCount != 0)
		{
			removeRef();
		}

		_pointer = other._pointer;
		_refCount = other._refCount;
		++*_refCount;

		std::cout << "Ran copy assign. " << *_refCount << std::endl;
		return this;
	}

	SharedPtr* operator=(std::nullptr_t other)
	{
		if (this == other)
		{
			return this;
		}

		if (_refCount != 0)
		{
			removeRef();
		}

		_pointer = nullptr;
		_refCount = new int(0);

		std::cout << "Ran nullptr assign." << *_refCount << std::endl;
		return this;
	}

	friend bool operator==(SharedPtr& lhs, std::nullptr_t rhs)
	{
		return (*lhs == rhs);
	}
	friend bool operator<(SharedPtr& lhs, std::nullptr_t rhs)
	{
		return (*lhs.get() < *rhs.get());
	}

	friend bool operator==(SharedPtr& lhs, SharedPtr& rhs)
	{
		return (lhs.get() == rhs.get());
	}

	friend bool operator<(SharedPtr& lhs, SharedPtr& rhs)
	{
		return (*lhs < *rhs);
	}

	T& operator*()
	{
		return *_pointer;
	}

	T* operator->()
	{
		return _pointer;
	}

	operator bool() const
	{
		return (_pointer != nullptr);
	}

	void reset()
	{
		_pointer = nullptr;
		_refCount = 0;
	}

	T* get()
	{
		return _pointer;
	}

	bool unique()
	{
		return (*_refCount == 1);
	}

	void Check()
	{
		assert(Invariant());
	}

	bool Invariant()
	{
		return (*_refCount != -1);
	}
};

template<class T>
void swap(SharedPtr<T>& a, SharedPtr<T>& b) noexcept
{
	SharedPtr<T> c(a);
	a = b;
	b = c;
}