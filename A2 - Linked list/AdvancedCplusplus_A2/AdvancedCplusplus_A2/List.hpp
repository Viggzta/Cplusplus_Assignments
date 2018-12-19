#pragma once
#include <cstdlib>
#include <iterator>
#include <stdexcept>
#include <vector>
#include <iostream>

template<class T>
class List : std::iterator<std::bidirectional_iterator_tag, T, ptrdiff_t, T*, T&>
{
	template <class T>
	class Link
	{
		template <class T>
		class Node;

		friend class List<T>;
		Link* _next, *_prev;
		Node<T>* Next() { return static_cast<Node<T>*>(_next); }
		Node<T>* Prev() { return static_cast<Node<T>*>(_next); }

		void insert(const T& value)
		{
			Node<T> newNode = Node<T>();
			newNode._data = value;
			newNode._next = this;
			newNode._prev = _prev;
			_prev->_next = newNode;
			_prev = newNode;
		}

		void erase()
		{
			Link<T> temp = _prev;
			_prev->_next = _next;
			_next->_prev = temp;
		}
	};

	template<class T>
	class Node : Link<T>
	{
		friend class List<T>;
		T _data;

	public:
		Node(const T& data) :_data(data) {};
	};

	template <class T>
	class ListIter : std::iterator<std::bidirectional_iterator_tag, T, ptrdiff_t, T*, T&>
	{
	private:
		Link<T>* _linkPtr;

	public:
		typedef T value_type;
		typedef ptrdiff_t difference_type;
		typedef T* pointer;
		typedef T& reference;
		typedef std::bidirectional_iterator_tag iterator_category;

		ListIter(Link<T>* p)
		{
			_linkPtr = p;
		}

		ListIter()
		{
			_linkPtr = nullptr;
		}

		ListIter(const ListIter& other)
		{
			_linkPtr = other._linkPtr;
		}

		ListIter& operator=(const ListIter& other)
		{
			_linkPtr = other._linkPtr;
			return *this;
		}

		T & operator*()
		{
			T out(_linkPtr->_data);
			return out;
		}

		T* operator->()
		{
			return &(static_cast<Node<T>*>(_linkPtr)->_data);
		}

		ListIter& operator++() // ++it
		{
			_linkPtr = _linkPtr._next;
			return *this;
		}

		ListIter& operator--() // --it
		{
			_linkPtr = _linkPtr._prev;
			return *this;
		}

		ListIter operator++(int) // it++
		{
			ListIter out = *this;
			_linkPtr = _linkPtr._next;
			return out;
		}

		ListIter operator--(int) // it--
		{
			ListIter out = *this;
			_linkPtr = _linkPtr._prev;
			return out;
		}

		friend bool operator==(const ListIter& lhs, const ListIter& rhs)
		{
			if (lhs._linkPtr == rhs._linkPtr)
			{
				return true;
			}

			return false;
		}

		friend bool operator!=(const ListIter& lhs, const ListIter& rhs)
		{
			if (lhs._linkPtr == rhs._linkPtr)
			{
				return false;
			}

			return true;
		}
	};

protected:
	Link<T> _head;
	size_t _size;

public:
	using iterator = ListIter<T>;

	List()
	{
		_head = new Link<T>();
		_head._next = &_head;
		_head._prev = &_head;
		_size = 0;
		std::cout << "Ran default ctor." << std::endl;
	}

	~List()
	{
		if (&_head == nullptr)
		{
			return;
		}

		if (_size != 0)
		{
			Link<T>* temp = _head._next;
			// Loops through all elements and deletes them
			while (temp != &_head)
			{
				temp = temp->_next;
				delete temp->_prev;
			}
		}
		delete &_head;
		std::cout << "Ran destructor." << std::endl;
	}

	List(const List& other)
	{
		_head = other._head;
		Link<T> temp = other._head._next;
		while (temp != other._head)
		{
			push_back(temp);
			temp = temp._next;
		}

		std::cout << "Ran copy ctor." << std::endl;
	}

	List(List&& other)
	{
		if (_head == null)
		{
			delete _head;
		}
		_head = &other._head;
		_size = &other._size;

		std::cout << "Ran move ctor." << std::endl;
	}

	List(const char* other)
	{
		List<char>();

		int offset = 0;
		while (other[offset] != '\0')
		{
			std::cout << "Pushing! " << other[offset] << std::endl;
			push_back(other[offset]);
			++offset;
		}

		std::cout << "Ran cstring ctor." << std::endl;
	}

	List& operator=(const List* other)
	{
		if (_head != nullptr)
		{
			~List();
		}
		
		List(other);
		std::cout << "Ran assign ctor." << std::endl;
		return *this;
	}

	List& operator=(List&& other)
	{
		~List(); // Move operator
		_head = other._head;
		_size = other._size;
		std::cout << "Ran move assign ctor." << std::endl;
		return *this;
	}

	T& front()
	{
		return _head._next._data;
	}

	T& back()
	{
		return _head._prev._data;
	}

	const T& front() const
	{
		return _head._next._data;
	}

	const T& back() const
	{
		return head._prev._data;
	}

	iterator begin() const
	{
		return _head.Next();
	}

	iterator end() const
	{
		return _head;
	}

	bool empty() const noexcept
	{
		if (_head._next == _head)
		{
			return true;
		}
		return false;
	}

	size_t size() const noexcept
	{
		return _size;
	}

	iterator insert(const iterator& pos, const T& value)
	{
		(&pos._linkPtr).insert(value);
		++_size;
	}

	iterator erase(const iterator& pos)
	{
		(&pos._linkPtr).erase(value);
		--_size;
	}

	void push_back(const T& value)
	{
		insert(end(), value);
		std::cout << "Push back." << std::endl;
	}

	void push_front(const T& value)
	{
		insert(begin(), value);
	}

	void pop_back()
	{
		erase(end()._linkPtr->Prev());
	}

	void pop_front()
	{
		erase(begin()._linkPtr);
	}

	friend bool operator==(const List& lhs, const List& other)
	{
		if (lhs.size() != other.size())
		{
			return false;
		}
		Node<T> temp1 = lhs._head._next;
		Node<T> temp2 = other._head._next;
		bool equal = (temp1._data == temp2._data);
		while (equal)
		{
			temp1 = temp1._next;
			temp2 = temp2._next;
			equal = (temp1._data == temp2._data);
		}
		return equal;
	}

	friend bool operator!=(const List& lhs, const List& other)
	{
		return !(lhs == other);
	}

	friend std::ostream& operator<<(std::ostream& cout, const List& other)
	{
		Node<T> temp = _head._next;
		while (temp != _head)
		{
			cout << temp._data;
			temp = temp._next;
		}

		return cout;
	};

	void Check() const
	{
		assert(Invariant());
	}

	void swap(List<T>& lhs, List<T>& rhs)
	{
		Link<T> temp = lhs._head;
		lhs._head = rhs._head;
		rhs._head = temp;
	}
};