#pragma once
//#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <string>
#include <cstddef>  // for size_t
#include <cstring>
#include <cmath>
#include "dynarray.h"
#include <wchar.h>
#include <iterator>
#include <cstring>

class BasicString;

class WideString : dynarray<wchar_t> {
public:
	typedef unsigned short int Index;
	typedef wchar_t* iterator;
	typedef const wchar_t* const_iterator;

	typedef std::reverse_iterator<iterator> reverse_iterator;
	typedef std::reverse_iterator<const_iterator> const_reverse_iterator;
	
	WideString();
	WideString(const BasicString& str);
	WideString(const WideString& str);
	WideString(WideString&& str) noexcept;
	WideString(const wchar_t* str);
	WideString(std::initializer_list<wchar_t>& il);
	WideString(const std::string& str);
	WideString(const wchar_t* str, size_t count);
	WideString(size_t count, wchar_t c);
	WideString(unsigned int num);
	~WideString();
	wchar_t* c_str() const;

	WideString& operator= (const wchar_t* str);
	WideString& operator= (const std::string& str);
	WideString& operator= (const WideString& str);          // copy assigment
	WideString& operator= (WideString&& str);               // move assigment
	WideString& operator= (wchar_t c);
	WideString& operator= (const BasicString& str);
	WideString& operator+= (const wchar_t* str);
	WideString& operator+= (const std::string& str);
	WideString& operator+= (const WideString& str);

	bool operator== (const WideString& str) const;
	bool operator!= (const WideString& str) const;

	bool operator> (const WideString& str) const;
	bool operator< (const WideString& str) const;
	bool operator>= (const WideString& str) const;
	bool operator<= (const WideString& str) const;

	friend std::ostream& operator<< (std::ostream& os, WideString& str);
	friend std::istream& operator >> (std::istream& is, WideString& str);
	//Operator<<(std::basic_ofstream), Operator>>(std::basic_ifstream)

	void clear();
	void shrink_to_fit();

	wchar_t operator[] (Index i) const;
	wchar_t* data();
	size_t size() const;
	size_t capacity() const;
	bool empty() const;

	void insert(Index i, const wchar_t* mid_str);
	void insert(Index i, size_t count, wchar_t c);
	void insert(Index i, wchar_t* mid_str, size_t count);
	void insert(Index i, const std::string& str);
	void insert(Index i, const std::string& str, size_t count);
	//same with iterator:
	//void insert(iterator i, const wchar_t* mid_str);
	void insert(iterator i, size_t count, wchar_t c);
	//void insert(iterator i, wchar_t* mid_str, size_t count);
	void insert(iterator i, const std::string& str);
	//void insert(iterator i, const std::string& str, size_t count);

	void append(size_t count, wchar_t c);
	void append(const wchar_t* str);
	void append(const wchar_t* str, Index i, size_t count);
	//void append(const wchar_t* str, iterator i, size_t count);
	void append(const std::string& str);
	void append(const std::string& str, Index i, size_t count);

	Index find(const wchar_t* substr) const;
	Index find(const wchar_t* substr, Index i_) const;
	Index find(const std::string& substr) const;
	Index find(const std::string& substr, Index i_) const;

	void replace(Index i, size_t count, const wchar_t* str);
	void replace(Index i, size_t count, const std::string& str);
	// same with iterator:
	void replace(iterator i, size_t count, wchar_t* str);
	void replace(iterator i, size_t count, const std::string& str);

	WideString substr(Index i, size_t count) const;
	WideString substr(Index i) const;

	void erase(Index i, size_t count);
	void erase(iterator i, size_t count);
	int to_int() const;
	wchar_t at(int index) const;

	iterator begin() const;
	iterator end() const;
	const_iterator cbegin();
	const_iterator cend();
	reverse_iterator rbegin();
	reverse_iterator rend() ;
	const_reverse_iterator rbegin() const;
	const_reverse_iterator rend() const;
	const_reverse_iterator crbegin() const;
	const_reverse_iterator crend() const;




private:
	void change_capacity(size_t new_capacity);
	size_t round_size(size_t size);
	wchar_t* c_str_;
	wchar_t* data_;
	size_t size_, capacity_;
	static const int default_size;
	//BasicString* BasicString;


};


WideString operator+ (const WideString& left, const wchar_t* right);
WideString operator+ (const WideString& left, const WideString& right);
WideString operator+ (const WideString& left, const std::wstring& right);

std::ostream& operator<< (std::ostream& os, WideString& str);
std::istream& operator >> (std::istream& is, WideString& str);








