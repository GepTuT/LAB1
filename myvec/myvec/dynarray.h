#define _CRT_SECURE_NO_WARNINGS
#pragma once


#include <iostream>
#include <stdexcept>
#include <utility>
#include <iterator>
#include <memory>
#include <cstddef> // for size_t
#include <initializer_list>

//using std::rel_ops::operator!=;


//Class DynArray
template <class T, class Allocator = std::allocator<T>>
class dynarray
{

public:

	//Member type def
	typedef T value_type;
	typedef size_t size_type;

	typedef T* iterator;
	typedef const T* const_iterator;

	typedef std::reverse_iterator<iterator> reverse_iterator;
	typedef std::reverse_iterator<const_iterator> const_reverse_iterator;

	typedef Allocator allocator_type;

	typedef ptrdiff_t difference_type;

	typedef T* pointer;
	typedef const T* const_pointer;

	typedef T& reference;
	typedef const T& const_reference;
	//______________________________//



	//Constructors, Destructors, Copy, Move
	explicit dynarray(const Allocator& alloc = Allocator()) :
		_size(0), _capacity(_size),
		_alloc(alloc), _array(_alloc.allocate(_capacity))
	{}

	dynarray(size_type count,
		const T& value,
		const Allocator& alloc = Allocator()) :
		_size(count), _capacity(_size),
		_alloc(alloc), _array(_alloc.allocate(_capacity))
	{
		std::uninitialized_fill_n(begin(), _size, value);
	}

	explicit dynarray(size_type count) :
		_size(count), _capacity(_size),
		_alloc(), _array(_alloc.allocate(_capacity))
	{
		std::uninitialized_fill_n(begin(), _size, T());
	}

	template <class inputIterator>
	dynarray(inputIterator first, inputIterator last,
		const Allocator& alloc = Allocator(),
		typename std::enable_if<!std::is_integral
		<inputIterator>::value>::type* = nullptr) :
		_size(std::distance(first, last)), _capacity(_size),
		_alloc(alloc), _array(_alloc.allocate(_capacity))
	{
		std::uninitialized_copy(first, last, begin());
	}

	dynarray(std::initializer_list<T> init,
		const Allocator& alloc = Allocator()) :
		dynarray(init.begin(), init.end(), alloc)
	{}

	dynarray(const dynarray& other) :
		_size(other._size), _capacity(_size),
		_alloc(other._alloc), _array(_alloc.allocate(_capacity))
	{
		std::uninitialized_copy(other.begin(), other.end(), begin());
	}

	dynarray(const dynarray& other, const Allocator& alloc) :
		_size(other._size), _capacity(_size),
		_alloc(alloc), _array(_alloc.allocate(_capacity))
	{
		std::uninitialized_copy(other.begin(), other.end(), begin());
	}

	dynarray(dynarray&& other) :
		_size(std::move(other._size)), _capacity(std::move(other._capacity)),
		_alloc(std::move(other._alloc)), _array(std::move(other._array))
	{
		other._size = 0;
		other._capacity = 0;
		other._array = nullptr;
	}

	dynarray(dynarray&& other, const Allocator& alloc) :
		_size(std::move(other._size)), _capacity(std::move(other._capacity)),
		_alloc(alloc), _array(std::move(other._array))
	{
		other._size = 0;
		other._capacity = 0;
		other._array = nullptr;
	}

	~dynarray()
	{
		clear();
		if (_array && _capacity)
			_alloc.deallocate(_array, _capacity);
		_size = 0;
		_capacity = 0;
		_array = nullptr;
	}

	allocator_type get_allocator() const
	{
		return _alloc;
	}
	//________________________________________//


	//Operator=
	dynarray& operator= (const dynarray& other)
	{
		if (this != &other)
			dynarray(other).swap(*this);
		return *this;
	}

	dynarray& operator= (dynarray&& other)
	{
		if (this != &other)
		{
			_size = std::move(other._size);
			_capacity = std::move(other._capacity);
			_alloc = std::move(other._alloc);
			_array = std::move(other._array);
			other._size = 0;
			other._capacity = 0;
			other._array = nullptr;
		}
		return *this;
	}
	//____________________________//



	//Element access
	reference at(size_type pos)
	{
		if (pos >= _size)
			throw std::out_of_range("Out of range.");
		return _array[pos];
	}

	const_reference at(size_type pos) const
	{
		if (pos >= _size)
			throw std::out_of_range("Out of range.");
		return _array[pos];
	}

	reference operator[] (size_type pos)
	{
		return _array[pos];
	}

	const_reference operator[] (size_type pos) const
	{
		return _array[pos];
	}

	reference front()
	{
		return *begin();
	}

	const_reference front() const
	{
		return *begin();
	}

	reference back()
	{
		return *(end() - 1);
	}

	const_reference back() const
	{
		return *(end() - 1);
	}
	//_____________________________//


	//Capacity
	bool empty() const
	{
		return _size == 0;
	}

	size_type size() const
	{
		return _size;
	}

	size_type capacity() const
	{
		return _capacity;
	}


	//______________________________//



	//Modifiers
	void assign(size_type count, const T& value) //assign (ref)
	{
		dynarray(count, value).swap(*this);
	}

	template <class inputiterator>
	void assign(inputiterator first, inputiterator last)
	{
		dynarray(first, last).swap(*this);
	}

	void clear()
	{
		for (iterator i = end(); i != begin(); )
			_alloc.destroy(--i);
		_size = 0;
	}

	

	size_type max_size() const
	{
		return size_type(-1) / sizeof(T);
	}

	void reserve(size_type size)
	{
		if (capacity() < size)
		{
			size_type n = _size;
			pointer newelements = _alloc.allocate(size);
			std::uninitialized_copy(begin(), end(), newelements);
			clear();
			if (_array && _capacity)
				_alloc.deallocate(_array, _capacity);
			_array = newelements;
			_size = n;
			_capacity = size;
		}
	}

	
	iterator insert(const_iterator pos, const T& value)
	{
		return insert(pos, 1, value);
	}

	iterator insert(const_iterator pos, T&& value)
	{
		size_type n = std::distance(cbegin(), pos);
		if (size() + 1 > capacity())
			reserve(2 * (size() + 1));
		std::copy_backward(begin() + n, end(), end() + 1);
		++_size;
		back() = std::move(value);
		return begin() + n;
	}

	iterator insert(const_iterator pos, size_type count, const T& value)
	{
		size_type n = std::distance(cbegin(), pos);
		if (size() + count > capacity())
			reserve(2 * (size() + count));
		std::copy_backward(begin() + n, end(), end() + count);
		std::fill(begin() + n, begin() + n + count, value);
		_size += count;
		return begin() + n;
	}

	template <class inputIterator>
	typename std::enable_if<!std::is_integral<inputIterator>::value, iterator>::
		type insert(const_iterator pos, inputIterator first, inputIterator last)
	{
		size_type n = std::distance(cbegin(), pos);
		size_type count = std::distance(first, last);
		if (size() + count > capacity())
			reserve(2 * (size() + count));
		std::copy_backward(begin() + n, end(), end() + count);
		std::copy(first, last, begin() + n);
		m_size += count;
		return begin() + n;
	}



	iterator erase(const_iterator pos)
	{
		size_type beg = std::distance(cbegin(), pos);
		if (pos + 1 != cend())
			std::copy(begin() + beg + 1, end(), begin() + beg);
		--_size;
		//_alloc.destroy(end());
		return begin() + beg;
	}

	iterator erase(const_iterator first, const_iterator last)
	{
		size_type size = std::distance(first, last);
		size_type beg = std::distance(cbegin(), first);
		iterator loc = std::copy(begin() + beg + size, end(), begin() + beg);
		for (iterator i = end(); i != loc; )
			//_alloc.destroy(--i);
		return begin() + beg;
	}
	void push_back(const T& value)
	{
		insert(end(), value);
	}

	void push_back(T&& value)
	{
		insert(end(),1, std::move(value));
	}

	void pop_back()
	{
		if (!empty())
		{
			--_size;
			_alloc.destroy(end());
		}
	}

	void resize(size_type count)
	{
		resize(count, T());
	}


	void resize(size_type count, const value_type& value)
	{
		if (count < size())
			erase(begin() + count, end());
		else if (count > size())
			insert(end(), count - size(), value);
	}

	void shrink_to_fit()
	{
		if (_array && size() != capacity())
		{
			
			_capacity = _size;
		}
	}



	void swap(dynarray& other) //swap (member function)
	{
		if (this != &other)
		{
			std::swap(_size, other._size);
			std::swap(_capacity, other._capacity);
			std::swap(_alloc, other._alloc);
			std::swap(_array, other._array);
		}
	}


	//________________________________//

	//iterators
	iterator begin()
	{
		return _array;
	}

	const_iterator begin() const
	{
		return _array;
	}

	const_iterator cbegin() const
	{
		return _array;
	}

	iterator end()
	{
		return _array + _size;
	}

	const_iterator end() const
	{
		return _array + _size;
	}

	const_iterator cend() const
	{
		return _array + _size;
	}

	reverse_iterator rbegin()
	{
		return reverse_iterator(end());
	}

	const_reverse_iterator rbegin() const
	{
		return const_reverse_iterator(end());
	}

	const_reverse_iterator crbegin() const
	{
		return const_reverse_iterator(end());
	}

	reverse_iterator rend()
	{
		return reverse_iterator(begin());
	}

	const_reverse_iterator rend() const
	{
		return const_reverse_iterator(begin());
	}

	const_reverse_iterator crend() const
	{
		return const_reverse_iterator(begin());
	}
	//________________________________________//

private:
	size_type _size;
	size_type _capacity;
	allocator_type _alloc;
	pointer _array;


	template <class Integer>
	void _initialize(size_type count, const Integer& value, std::true_type)
	{
		_size = count;
		_capacity = 2 * _size;
		_array = _alloc.allocate(_capacity);
		std::uninitialized_fill_n(begin(), _size, value);
	}

	template <class inputiterator>
	void _initialize(inputiterator first, inputiterator last, std::false_type)
	{
		distance(first, last, _size);
		_capacity = 2 * _size;
		_array = _alloc.allocate(_capacity);
		std::uninitialized_copy(first, last, begin());
	}




};


template<class T, class Alloc>
bool operator== (dynarray<T, Alloc>& lhs, dynarray<T, Alloc>& rhs) //operator ==(!=) (non-member function)
{
	return (lhs.size() == rhs.size() && std::equal(lhs.begin(), lhs.end(), rhs.begin()));
}

template<class T, class Alloc>
bool operator!= (dynarray<T, Alloc>& lhs, dynarray<T, Alloc>& rhs) //operator ==(!=) (non-member function)
{
	return !(lhs.size() == rhs.size() && std::equal(lhs.begin(), lhs.end(), rhs.begin()));
}

template <class T, class Alloc>
void swap(dynarray<T, Alloc> &lhs, dynarray<T, Alloc> &rhs) //swap (non member function)
{
	lhs.swap(rhs);
}





















