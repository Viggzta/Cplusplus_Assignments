#pragma once
#include <iterator>

template<class T>
class Vector : std::iterator
{
	T value_type;
	unsigned int size_type;

public:
	using iterator = VectItt<T>;
	Vector();
	~Vector();
	Vector(const Vector& other);
	Vector(Vector&& other);
	Vector(const std::vector& other);
	Vector& operator=(const Vector& other);
	Vector& operator=(Vector&& other);
	T& operator[](size_t i);
	T& at(size_t i);
	T* data() noexcept;
	const T* data() const noexcept;	size_t size() const noexcept;
	void reserve(size_t n);
	size_t capacity() const noexcept;
	void shrink_to_fit();
	void push_back(T c);
	void resize(size_t n);
	iterator begin() const;
	iterator end() const;
	friend bool operator==(const Vector& lhs, const Vector& other);
	friend bool operator!=(const Vector& lhs, const Vector& other);
	friend bool operator<(const Vector& lhs, const Vector& other);
	friend bool operator>(const Vector& lhs, const Vector& other);
	friend bool operator<=(const Vector& lhs, const Vector& other);
	friend bool operator>=(const Vector& lhs, const Vector& other);
	void swap(Vector<T>& lhs, Vector<T>& rhs);

	// Testing
	friend std::ostream& operator<<(std::ostream& cout, const Vector& other)
	{
		for (size_t i = 0; i < other.size(); ++i)
			cout << other[i];
		return cout;
	}
};