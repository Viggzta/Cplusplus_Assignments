#pragma once
#include <cstdlib>
#include <cassert>
#include <iterator>
#include <stdexcept>
#include <vector>
#include <iostream>

#define MY_DEBUG

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
		Node<T>* Prev() { return static_cast<Node<T>*>(_prev); }

		Link<T>* insert(const T& value)
		{
			// Prev / Next kopplas rätt (dubbelkollat)
			Node<T>* newNode = new Node<T>(value);
			newNode->_next = this;
			newNode->_prev = _prev;
			_prev->_next = newNode;
			this->_prev = newNode;

			return newNode;
		}

		Link<T>* erase()
		{
			Link<T>* temp = _next;
			_prev->_next = _next;
			_next->_prev = _prev;

			delete this;
			return temp;
		}
	public:

		Node<T>* asNode()
		{
			return static_cast<Node<T>*>(this);
		}
	};

	template<class T>
	class Node : Link<T>
	{
		friend class List<T>;
		T _data;

	public:
		Node(const T& data) :_data(data) {};

		T data() const { return _data; }
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
	}

	~List()
	{
		if (_size != 0)
		{
			Link<T>* temp = _head._next;
			// Loops through all elements and deletes them
			while (temp != &_head)
			{
				temp = temp->_next;
				delete temp->Prev();
			}
			_size = 0;
		}
	}

	List(const List& other)
	{
		_head._next = &_head;
		_head._prev = &_head;
		_size = 0;

		Link<T>* temp = other._head._next;
		while (temp != &other._head)
		{
			push_back(static_cast<Node<T>*>(temp)->_data);
			temp = temp->_next;
		}
	}

	List(List&& other)
	{
		if (other._size == 0)
		{
			// Det finns inget att flytta
			_head._next = &_head;
			_head._prev = &_head;
			_size = 0;
		}
		else
		{
			// Länkar till nytt huvud
			_head._next = other._head._next;
			_head._prev = other._head._prev;
			_size = other._size;

			// Länka prev och next till rätt huvud
			_head._next->_prev = &_head;
			_head._prev->_next = &_head;

			// Länkar om other
			other._head._next = &other._head;
			other._head._prev = &other._head;
			other._size = 0;
		}
	}

	List(const char* other)
	{
		_head._next = &_head;
		_head._prev = &_head;
		_size = 0;

		int offset = 0;
		while (other[offset] != '\0')
		{
			push_back(other[offset]);
			++offset;
		}
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
			this->push_back(static_cast<Node<T>*>(temp2)->_data);
			temp2 = temp2->_next;
		}
		return *this;
	}

	List& operator=(List&& other)
	{
		// Det finns inget att flytta
		if (&_head == &other._head)
		{
			return *this;
		}

		if (_size != 0)
		{
			Link<T>* temp = _head._next;
			// Loops through all elements and deletes them
			while (temp != &_head)
			{
				temp = temp->_next;
				delete temp->Prev();
			}
			_size = 0;
		}

		if (other._size == 0)
		{
			// Det finns inget att flytta
			_head._next = &_head;
			_head._prev = &_head;
			_size = 0;
		}
		else
		{
			// Länkar till nytt huvud
			_head._next = other._head._next;
			_head._prev = other._head._prev;
			_size = other._size;

			// Länka prev och next till rätt huvud
			_head._next->_prev = &_head;
			_head._prev->_next = &_head;

			// Länkar om other
			other._head._next = &other._head;
			other._head._prev = &other._head;
			other._size = 0;
		}

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
		return *begin();
	}

	const T& back() const
	{
		auto temp = end();
		--temp;
		return *temp;
	}

	iterator begin() const
	{
		return ListIter<T>(_head._next);
	}

	ListIter<T> end() const
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
		Link<T>* temp = pos._linkPtr->insert(value);
		++_size;
		return iterator(temp);
	}

	iterator erase(const iterator& pos)
	{
		Link<T>* temp = pos._linkPtr->erase();
		--_size;
		return iterator(temp);
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
			equal = (a._linkPtr->asNode()->data() == b._linkPtr->asNode()->data());
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

	friend bool operator<(const List& lhs, const List& other)
	{
		auto a = lhs.begin(), b = other.begin();
		while (a != lhs.end())
		{
			if (a._linkPtr->asNode()->data() != b._linkPtr->asNode()->data())
			{
				return a._linkPtr->asNode()->data() < b._linkPtr->asNode()->data();
			}
			++a;
			++b;
		}

		if (lhs.size() < other.size())
		{
			return true;
		}

		return false; // Allt är lika
	}

	friend bool operator>(const List& lhs, const List& other)
	{
		auto a = lhs.begin(), b = other.begin();
		while (a != lhs.end())
		{
			if (a._linkPtr->asNode()->data() != b._linkPtr->asNode()->data())
			{
				return a._linkPtr->asNode()->data() > b._linkPtr->asNode()->data();
			}
			++a;
			++b;
		}

		if (lhs.size() > other.size())
		{
			return true;
		}

		return false; // Allt är lika
	}

	friend bool operator<=(const List& lhs, const List& other)
	{
		return !(lhs > other);
	}

	friend bool operator>=(const List& lhs, const List& other)
	{
		return !(lhs < other);
	}

	friend std::ostream& operator<<(std::ostream& cout, const List& other)
	{
		auto temp = other.begin();
		while (temp != other.end())
		{
			cout << temp._linkPtr->asNode()->data();
			++temp;
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

	void swap(List<T>& other)
	{
		if (other._size == 0 && _size == 0) // Båda är tomma. Gör inget.
		{
			return;
		}
		if (other._size == 0) // Det finns inget att flytta i OTHER
		{
			other._head._next = _head._next;
			other._head._prev = _head._prev;
			other._size = _size;
			other._head._next->_prev = &other._head;
			other._head._prev->_next = &other._head;

			_head._next = &_head;
			_head._prev = &_head;
			_size = 0;
		}
		else if (_size == 0) // Det finns inget att flytta i THIS
		{
			_head._next = other._head._next;
			_head._prev = other._head._prev;
			_size = other._size;
			_head._next->_prev = &_head;
			_head._prev->_next = &_head;

			other._head._next = &other._head;
			other._head._prev = &other._head;
			other._size = 0;
		}
		else
		{
			Link<T>* tempThisNxt = _head._next;
			Link<T>* tempThisPrv = _head._prev;
			size_t tempThisSize = _size;

			// Länkar till nytt huvud
			_head._next = other._head._next;
			_head._prev = other._head._prev;
			_size = other._size;

			// Länkar till nytt huvud
			other._head._next = tempThisNxt;
			other._head._prev = tempThisPrv;
			other._size = tempThisSize;

			// Länka prev och next till rätt huvud för båda
			_head._next->_prev = &_head;
			_head._prev->_next = &_head;
			other._head._next->_prev = &other._head;
			other._head._prev->_next = &other._head;
		}
	}
};

template <class T>
void swap(List<T>& lhs, List<T>& rhs)
{
	lhs.swap(rhs);
}