#pragma once

#include <cassert>
#include <iostream>

template <class T>
class SharedPtr
{
private:
	T* _pointer;
	int* _refCount;

	void addRef(T* ptr)
	{
		if (ptr != nullptr)
		{
			if (_refCount == nullptr)
			{
				_refCount = new int(1);
			}
			else
			{
				++*_refCount;
			}
		}
	}

	void removeRef()
	{
		if (_refCount != nullptr)
		{
			--*_refCount;
			if (*_refCount == 0)
			{
				std::cout << "Refrence is dead!(" << _refCount << "). " << std::endl;
				delete _pointer;
				delete _refCount;
			}
			_refCount = nullptr;
		}
		_pointer = nullptr;
	}

	bool isSelf(SharedPtr& other)
	{
		if (_refCount == other._refCount)
		{
			std::cout << "I'm me." << std::endl;
		}

		return (_refCount == other._refCount);
	}

public:
	SharedPtr()
	{
		_pointer = nullptr;
		_refCount = nullptr;

		std::cout << "Ran void ctor(" << _refCount << "). " << std::endl;
	}

	SharedPtr(T* other)
	{
		_pointer = other;
		_refCount = nullptr;
		addRef(other);

		std::cout << "Ran _ptr assign ctor(" << _refCount << "). " << std::endl;
	}

	SharedPtr(SharedPtr& other)
	{
		if (isSelf(other))
		{
			return;
		}

		_pointer = other._pointer;
		_refCount = other._refCount;
		addRef(_pointer);

		std::cout << "Ran copy ctor(" << _refCount << "). " << *_refCount << std::endl;
	}

	SharedPtr(SharedPtr&& other)
	{
		if (isSelf(other))
		{
			return;
		}

		_pointer = other._pointer;
		_refCount = other._refCount;
		addRef(_pointer);
		other.removeRef();

		std::cout << "Ran move ctor(" << _refCount << "). " << *_refCount << std::endl;
	}

	~SharedPtr()
	{
		if (_refCount != nullptr)
		{
			std::cout << "Ran destructor(" << _refCount << "). " << *_refCount << std::endl;
		}
		else
		{
			std::cout << "Ran destructor(nullptr). " << std::endl;
		}
		removeRef();
	}

	SharedPtr* operator=(SharedPtr& other)
	{
		if (isSelf(other))
		{
			return this;
		}

		removeRef();
		_pointer = other._pointer;
		_refCount = other._refCount;
		addRef(_pointer);

		std::cout << "Ran copy assign(" << _refCount << "). " << std::endl;
		return this;
	}

	SharedPtr* operator=(std::nullptr_t other)
	{
		if (_pointer == nullptr)
		{
			return this;
		}

		removeRef();
		_pointer = nullptr;
		_refCount = nullptr;

		std::cout << "Ran nullptr assign(" << _refCount << "). " << std::endl;
		return this;
	}

	friend bool operator==(SharedPtr& lhs, std::nullptr_t rhs)
	{
		return !lhs;
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
		return (lhs.get() < rhs.get());
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
		removeRef();
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
		if (_refCount == nullptr && _pointer == nullptr)
		{
			return true;
		}
		else if (_refCount != nullptr && _pointer != nullptr)
		{
			return true;
		}
		
		return false;
	}
};

template<class T>
void swap(SharedPtr<T>& a, SharedPtr<T>& b) noexcept
{
	SharedPtr<T> c(a);
	a = b;
	b = c;
}