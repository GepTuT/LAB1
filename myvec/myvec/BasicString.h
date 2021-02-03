#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include "dynarray.h"
#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <cmath>
#include <comdef.h> //for wchar to char
#include <wchar.h>
#include <iterator>

class BasicString;
class WideString;


class BasicString : public dynarray<char> {
public:
	typedef unsigned short int Index;
	typedef char* iterator;
	typedef const char* const_iterator;

	typedef std::reverse_iterator<iterator> reverse_iterator;
	typedef std::reverse_iterator<const_iterator> const_reverse_iterator;

	BasicString();
	BasicString(const BasicString& str);
	BasicString(const WideString& str);
	BasicString(BasicString&& str);
	BasicString(const char* str);
	BasicString(std::initializer_list<char>& il);
	BasicString(const std::string& str);
	BasicString(const char* str, size_t count);
	BasicString(size_t count, char c);
	BasicString(unsigned int num);
	~BasicString();
	char* c_str() const;

	BasicString& operator= (const char* str);
	BasicString& operator= (const std::string& str);
	BasicString& operator= (const BasicString& str);          // copy assigment
	BasicString& operator= (BasicString&& str);               // move assigment
	BasicString& operator= (char c);
	BasicString& operator= (const WideString& str);
	BasicString& operator+= (const char* str);
	BasicString& operator+= (const std::string& str);
	BasicString& operator+= (const BasicString& str);
	bool operator== (const BasicString& str) const;
	bool operator!= (const BasicString& str) const;
	bool operator> (const BasicString& str) const;
	bool operator< (const BasicString& str) const;
	bool operator>= (const BasicString& str) const;
	bool operator<= (const BasicString& str) const;

	friend std::ostream& operator<< (std::ostream& os, BasicString& str);
	friend std::istream& operator >> (std::istream& is, BasicString& str);


	void clear();
	void shrink_to_fit();

	char operator[] (Index i) const;
	char* data();
	size_t size() const;
	size_t capacity() const;
	bool empty() const;

	template <class inputiterator>
	void insert(const_iterator pos, inputiterator first, inputiterator last);
	void insert(Index i, const char* mid_str);
	void insert(Index i, size_t count, char c);
	void insert(Index i, char* mid_str, size_t count);
	void insert(Index i, const std::string& str);
	void insert(Index i, const std::string& str, size_t count);
	void insert(size_t count, iterator i, char c,int value);
	void insert(const std::string& str, iterator i, int value);
	void append(size_t count, char c);
	void append(const char* str);
	void append(const char* str, Index i, size_t count);

	void append(const std::string& str);
	void append(const std::string& str, Index i, size_t count);

	Index find(const char* substr) const;
	Index find(const char* substr, Index i_) const;
	Index find(const std::string& substr) const;
	Index find(const std::string& substr, Index i_) const;

	void replace(Index i, size_t count, const char* str);
	void replace(Index i, size_t count, const std::string& str);
	
	void replace(size_t count, iterator i, char* str);
	void replace(size_t count, iterator i, const std::string& str);

	BasicString substr(Index i, size_t count) const;
	BasicString substr(Index i) const;

	void erase(Index i, size_t count);
	void erase(size_t count, iterator i);
	int to_int() const;
	char at(int index) const;

	iterator begin() const;
	iterator end() const;
	const_iterator cbegin();
	const_iterator cend();
	reverse_iterator rbegin();
	reverse_iterator rend();
	const_reverse_iterator rbegin() const;
	const_reverse_iterator rend() const;
	const_reverse_iterator crbegin() const;
	const_reverse_iterator crend() const;




private:
	void change_capacity(size_t new_capacity);
	size_t round_size(size_t size);
	char* c_str_;
	char* data_;
	size_t size_, capacity_;
	static const int default_size=16;


};


BasicString operator+ (const BasicString& left, const char* right);
BasicString operator+ (const BasicString& left, const BasicString& right);
BasicString operator+ (const BasicString& left, const std::string& right);

std::ostream& operator<< (std::ostream& os, BasicString& str);
std::istream& operator >> (std::istream& is, BasicString& str);



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
	WideString(WideString&& str) ;
	WideString(const wchar_t* str);
	WideString(std::initializer_list<wchar_t>& il);
	WideString(const wchar_t* str, size_t count);
	WideString(size_t count, wchar_t c);
	WideString(unsigned int num);
	~WideString();
	wchar_t* c_str() const;

	WideString& operator= (const wchar_t* str);
	WideString& operator= (const WideString& str);          // copy assigment
	WideString& operator= (WideString&& str);               // move assigment
	WideString& operator= (wchar_t c);
	WideString& WideString::operator= (const BasicString& str);
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
	void insert(size_t count, iterator i, wchar_t c,int value);
	void insert(const std::string& str, iterator i,int value);
	
	void append(size_t count, wchar_t c);
	void append(const wchar_t* str);
	void append(const wchar_t* str, Index i, size_t count);
	void append(const std::string& str);
	void append(const std::string& str, Index i, size_t count);

	Index find(const wchar_t* substr) const;
	Index find(const wchar_t* substr, Index i_) const;
	Index find(const std::string& substr) const;
	Index find(const std::string& substr, Index i_) const;

	void replace(Index i, size_t count, const wchar_t* str);
	void replace(Index i, size_t count, const std::string& str);
	void replace(size_t count, iterator i, wchar_t* str);
	
	WideString substr(Index i, size_t count) const;
	WideString substr(Index i) const;

	void erase(Index i, size_t count);
	void erase(size_t count, iterator i);
	int to_int() const;
	wchar_t at(int index) const;

	template <class inputiterator>
	void insert(const_iterator pos, inputiterator first, inputiterator last);

	iterator begin() const;
	iterator end() const;
	const_iterator cbegin();
	const_iterator cend();
	reverse_iterator rbegin();
	reverse_iterator rend();
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
	static const int default_size=8;


};


WideString operator+ (const WideString& left, const wchar_t* right);
WideString operator+ (const WideString& left, const WideString& right);
WideString operator+ (const WideString& left, const std::wstring& right);

std::ostream& operator<< (std::ostream& os, WideString& str);
std::istream& operator >> (std::istream& is, WideString& str);



