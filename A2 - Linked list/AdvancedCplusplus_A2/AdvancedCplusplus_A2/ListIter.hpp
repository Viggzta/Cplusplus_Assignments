#pragma once
#include <iterator>
#include <cstddef>

template <class T>
class ListIter : std::iterator<std::bidirectional_iterator_tag, T, ptrdiff_t>
{
	Link<T>* _ptr;
};