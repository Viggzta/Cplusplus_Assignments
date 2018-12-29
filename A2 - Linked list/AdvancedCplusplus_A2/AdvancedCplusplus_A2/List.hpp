#pragma once
#include <cstdlib>
#include <cassert>
#include <iterator>
#include <stdexcept>
#include <vector>
#include <iostream>

template<class T>
class List
{
	template <class T>
	class Node;

	template <class T>
	class Link
	{
		friend class List<T>;
		Link* _next, *_prev;
		Node<T>* Next() { return static_cast<Node<T>*>(_next); }
		Node<T>* Prev() { return static_cast<Node<T>*>(_next); }

		void insert(const T& value)
		{
			// Prev / Next kopplas rätt (dubbelkollat)
			Node<T>* newNode = new Node<T>(value);
			newNode->_next = this;
			newNode->_prev = _prev;
			_prev->_next = newNode;
			this->_prev = newNode;
		}

		void erase()
		{
			Link<T> temp = _prev;
			_prev->_next = _next;
			_next->_prev = temp;
		}

		Node<T> asNode()
		{
			return static_cast<Node<T>>(this);
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
	class ListIter
	{
	public:
		Link<T>* _linkPtr;

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
			return static_cast<Node<T>*>(_linkPtr)->_data;
		}

		T* operator->()
		{
			return &(static_cast<Node<T>*>(_linkPtr)->_data);
		}

		ListIter& operator++() // ++it
		{
			_linkPtr = _linkPtr->_next;
			return *this;
		}

		ListIter& operator--() // --it
		{
			_linkPtr = _linkPtr->_prev;
			return *this;
		}

		ListIter operator++(int) // it++
		{
			ListIter out = *this;
			_linkPtr = _linkPtr->_next;
			return out;
		}

		ListIter operator--(int) // it--
		{
			ListIter out = *this;
			_linkPtr = _linkPtr->_prev;
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
		_head._next = &_head;
		_head._prev = &_head;
		_size = 0;
		std::cout << "Ran default ctor." << std::endl;
	}

	~List()
	{
		if (_size != 0)
		{
			Link<T>* temp = _head._next;
			// Loops through all elements and deletes them
			std::cout << "Head on " << &_head << std::endl;
			while (temp != &_head)
			{
				std::cout << "temp on " << temp << std::endl;
				temp = temp->_next;
				std::cout << "temp move " << temp << std::endl;
				std::cout << "Delete on " << temp->_prev << std::endl;
				delete temp->Prev();
			}
		}
		std::cout << "Ran destructor." << std::endl;
	}

	List(const List& other)
	{
		this->~List();

		_head._next = &_head;
		_head._prev = &_head;
		_size = 0;

		Link<T>* temp = other._head._next;
		while (temp != &other._head)
		{
			push_back(static_cast<Node<T>*>(temp)->_data);
			temp = temp->_next;
		}

		std::cout << "Ran copy ctor." << std::endl;
	}

	List(List&& other)
	{
		_head = other._head;
		_size = other._size;

		std::cout << "Ran move ctor." << std::endl;
	}

	List(const char* other)
	{
		_head._next = &_head;
		_head._prev = &_head;
		_size = 0;

		int offset = 0;
		while (other[offset] != '\0')
		{
			std::cout << "Pushing! " << other[offset] << std::endl;
			push_back(other[offset]);
			++offset;
		}

		std::cout << "Ran cstring ctor." << std::endl;
	}

	List& operator=(const List& other)
	{
		if (&_head == &other._head)
		{
			return *this;
		}

		this->~List();

		_head._next = &_head;
		_head._prev = &_head;
		_size = 0;
		Link<T>* temp2 = other._head._next;
		while (temp2 != &other._head)
		{
			std::cout << "Adding stuff at " << temp2 << std::endl;
			this->push_back(static_cast<Node<T>*>(temp2)->_data);
			temp2 = temp2->_next;
		}
		std::cout << "Ran assign ctor." << std::endl;
		return *this;
	}

	List& operator=(List&& other)
	{
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

		_head = other._head;
		_size = other._size;
		std::cout << "Ran move assign ctor." << std::endl;
		return *this;
	}

	T& front()
	{
		return _head.Next()->_data;
	}

	T& back()
	{
		return _head.Prev()->_data;
	}

	const T& front() const
	{
		return _head.Next()->_data;
	}

	const T& back() const
	{
		return head.Prev()->_data;
	}

	iterator begin() const
	{
		return ListIter<T>(_head._next);
	}

	ListIter<T> end() const// Tog bort const pga bugg
	{
		return ListIter<T>( const_cast<Link<T>*>(&_head) ); // Varför går detta att const_cast:a?
	}

	bool empty() const noexcept
	{
		if (_head._next == &_head)
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
		pos._linkPtr->insert(value);
		++_size;
		return pos;
	}

	iterator erase(const iterator& pos)
	{
		pos._linkPtr->erase();
		--_size;
		return *this;
	}

	void push_back(const T& value)
	{
		insert(end(), value);
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

		if (lhs.size() == 0)
		{
			return true;
		}

		bool equal = false;
		auto a = lhs.begin(), b = other.begin();
		while (a != lhs.end())
		{
			equal = (a._linkPtr == b._linkPtr);
			if (!equal)
			{
				return false;
			}

			++a;
			++b;
		}

		return true;
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

	bool Invariant() const
	{
		if (_size == 0)
		{
			return this->empty();
		}

		return !(this->empty());
	}

	void swap(List<T>& lhs, List<T>& rhs)
	{
		Link<T> temp = lhs._head;
		lhs._head = rhs._head;
		rhs._head = temp;
	}
};