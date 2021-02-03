#include "BasicString.h"





BasicString::BasicString()
	: size_(0),
	capacity_(default_size),
	c_str_(new char[default_size]),
	data_(nullptr)
{
	c_str_[0] = '\0';
}



BasicString::BasicString(const BasicString& str)         // copy constructor
	: size_(str.size_),
	capacity_(str.capacity_),
	c_str_(new char[str.capacity_]),
	data_(nullptr)
{
	std::strcpy(this->c_str_, str.c_str_);
}

BasicString::BasicString(const WideString& str) // copy constructor
	: size_(str.size()),
	capacity_(str.capacity()),
	c_str_(new char[str.capacity()]),
	data_(nullptr)
{
	strcpy(this->c_str_, _bstr_t(str.c_str()));
}

BasicString::BasicString(BasicString&& str) :  // move constructor
	size_(str.size()),
	capacity_(str.capacity()),
	c_str_(new char[str.capacity()]),
	data_(nullptr)          
{
	*this = std::move(str);
}

BasicString::BasicString(const char* str)
{
	size_ = std::strlen(str);
	capacity_ = round_size(size_);
	c_str_ = new char[capacity_];
	std::strcpy(this->c_str_, str);

	data_ = nullptr;
}

BasicString::BasicString(std::initializer_list<char>& il)
	: size_(il.size()),
	capacity_(round_size(il.size())),
	c_str_(new char[round_size(il.size())]),
	data_(nullptr)
{
	std::strcpy(this->c_str_, il.begin());
}

BasicString::BasicString(const std::string& str)
	: size_(str.size()),
	capacity_(str.capacity()),
	c_str_(new char[str.capacity()]),
	data_(nullptr)
{
	std::memcpy(this->c_str_, str.c_str(), size_);
	c_str_[size_] = '\0';
}

BasicString::BasicString(const char* str, size_t count)
{
	size_ = count;
	capacity_ = round_size(size_);
	c_str_ = new char[capacity_];
	std::memcpy(this->c_str_, str, count);

	data_ = nullptr;
}

BasicString::BasicString(size_t count, char c)
{
	size_ = count;
	capacity_ = round_size(size_);
	c_str_ = new char[capacity_];
	std::memset(c_str_, c, count);

	data_ = nullptr;
}

BasicString::BasicString(unsigned int num)
{
	char c;

	auto byte_size{ [](unsigned int num) -> int {
		return 1 + static_cast<int> (std::log2(num)) / 8;
	} };

	size_ = byte_size(num) * 2 + 2;        // 1 byte in hex = 2 symbols. + 2 symbols for '0', 'x'
	capacity_ = round_size(size());
	c_str_ = new char[capacity()];

	c_str_[size()] = '\0';

	
	int i = size() - 1;
	while(i >= 2) {
		
		c = (num & 0xf);
		if (c <= 9) {
			c_str_[i] = c + '0';
		}
		else {
			c_str_[i] = c - 10 + 'a';
		}
		num >>= 4;
		--i;
	}

	c_str_[0] = '0';
	c_str_[1] = 'x';

	data_ = nullptr;
}




BasicString::~BasicString()
{
	delete[] c_str_;
	c_str_ = nullptr;

	if (data_ != nullptr) {
		delete[] data_;
		data_ = nullptr;
	}
}
BasicString& BasicString::operator= (const char* str)
{
	if (this->capacity_ < std::strlen(str)) {
		change_capacity(round_size(std::strlen(str)));
	}
	std::strcpy(this->c_str_, str);
	this->size_ = std::strlen(str);

	return*this;
}

BasicString& BasicString::operator= (const WideString& str)
{
	if (this->capacity_ < wcslen(str.c_str())) {
		change_capacity(round_size(wcslen(str.c_str())));
	}
	strcpy(this->c_str_, _bstr_t(str.c_str()));
	this->size_ = wcslen(str.c_str());

	return*this;
}

BasicString& BasicString::operator= (const std::string& str)
{
	return (*this = str.c_str());
}

BasicString& BasicString::operator= (const BasicString& str)     //  copy assigment
{
	if (this != &str) {
		return (*this = str.c_str());
	}
	else {
		return*this;
	}
}

BasicString& BasicString::operator= (BasicString&& str)  //  move assigment
{
	if (this != &str) {
		delete[] this->c_str_;

		this->c_str_ = str.c_str_;
		this->size_ = str.size_;
		this->capacity_ = str.capacity_;

		str.c_str_ = nullptr;
		str.size_ = 0;
		str.capacity_ = 0;
	}

	return*this;
}

BasicString& BasicString::operator= (char c)
{
	this->c_str_[0] = c;
	this->size_ = 1;

	return*this;
}

BasicString& BasicString::operator+= (const char* str)
{
	if (this->capacity_ <= this->size_ + std::strlen(str)) {
		change_capacity(round_size(this->size_ + std::strlen(str)));
	}
	std::strcat(this->c_str_, str);
	this->size_ += std::strlen(str);

	return*this;
}

BasicString& BasicString::operator+= (const std::string& str)
{
	return (*this += str.c_str());
}

BasicString& BasicString::operator+= (const BasicString& str)
{
	return (*this += str.c_str_);
}

bool BasicString::operator== (const BasicString& str) const
{
	if (this == &str) {
		return true;
	}

	return (std::strcmp(this->c_str_, str.c_str()) == 0);
}

bool BasicString::operator!= (const BasicString& str) const
{
	return !(*this == str);
}


bool BasicString::operator> (const BasicString& str) const
{
	return std::strcmp(this->c_str(), str.c_str_) > 0;
}

bool BasicString::operator< (const BasicString& str) const
{
	return std::strcmp(this->c_str(), str.c_str_) < 0;
}

bool BasicString::operator>= (const BasicString& str) const
{
	return std::strcmp(this->c_str(), str.c_str_) >= 0;
}

bool BasicString::operator<= (const BasicString& str) const
{
	return std::strcmp(this->c_str(), str.c_str_) <= 0;
}





void BasicString::clear()
{
	*this = BasicString();
}



void BasicString::shrink_to_fit()
{
	change_capacity(size() + 1);
}

char BasicString::operator[] (Index i) const
{
	return c_str_[i];
}



size_t BasicString::size() const
{
	return size_;
}

size_t BasicString::capacity() const
{
	return capacity_;
}

bool BasicString::empty() const
{
	return (size() == 0);
}





char* BasicString::data()
{
	if (data_ != nullptr) {
		delete[] data_;
	}

	data_ = new char[size()];
	std::memcpy(data_, c_str_, size());

	return data_;
}



void BasicString::insert(Index i_, const char* mid_str)
{
	if (i_ > size()) {
		throw "Out of range";
	}

	if (size_ + std::strlen(mid_str) >= capacity_) {
		change_capacity(round_size(size_ + std::strlen(mid_str) + 1));
	}


	for (int i = size_ + std::strlen(mid_str) - 1; i >= i_ + std::strlen(mid_str); --i) {
		c_str_[i] = c_str_[i - std::strlen(mid_str)];
	}

	for (int i = i_, j = 0; i < i_ + std::strlen(mid_str); ++i, ++j) {
		c_str_[i] = mid_str[j];
	}

	size_ += std::strlen(mid_str);
	c_str_[size_] = '\0';
}

void BasicString::insert(Index i, size_t count, char c)
{
	char* mid_str = new char[((count/16) + 1)*16];
	std::memset(mid_str, c, count);
	mid_str[count] = '\0';
	insert(i, mid_str);
	delete[] mid_str;
}

void BasicString::insert(Index i, char* mid_str, size_t count)
{
	std::memcpy(mid_str, static_cast<const char*>(mid_str), count);
	mid_str[count] = '\0';
	insert(i, mid_str);
}

template <class inputiterator>
void BasicString::insert(const_iterator pos, inputiterator first, inputiterator last) //insert(iterators)
{
	size_type temp = pos - begin();
	size_type n = distance(first, last);
	if (_size + n > _capacity)
		resize(_size + n);
	else
		_size += n;
	pos = begin() + temp;
	for (iterator i = end() - 1; i != pos + n - 1; --i)
		*i = *(i - n);
	for (iterator i = pos; i != pos + n && first != last; ++i)
		*i = *first++;
}

void BasicString::insert(Index i, const std::string& str)
{
	insert(i, str.c_str());
}

void BasicString::insert(Index i, const std::string& str, size_t count)
{
	insert(i, str.c_str(), count);
}
void BasicString::insert(size_t count,iterator i, char c,int value)
{
	insert(i - c_str_, count, c);
}

void BasicString::insert(const std::string &str, iterator i ,int value)
{
	insert(i - c_str_, str);
}

void BasicString::append(size_t count, char c)
{
	char* tmp_str = new char[((count/16)+1)*16];
	std::memset(tmp_str, c, count);
	tmp_str[count] = '\0';

	append(tmp_str, (int)0, count);

	delete[] tmp_str;
}

void BasicString::append(const char* str)
{
	append(str, 0, std::strlen(str));
}

void BasicString::append(const char* str, Index i, size_t count)
{
	if (size_ + count > capacity_) {
		change_capacity(round_size(size_ + count + 1));
	}
	std::strncpy(this->c_str_ + size_, str + i, count);
	size_ += count;
	c_str_[size()] = '\0';
}

void BasicString::append(const std::string& str)
{
	append(str.c_str(), 0, str.size());
}

void BasicString::append(const std::string& str, Index i, size_t count)
{
	append(str.c_str(), i, count);
}


BasicString::Index BasicString::find(const char* substr) const
{
	return find(substr, 0);
}

BasicString::Index BasicString::find(const char* substr, Index i_) const
{
	char c;
	for (int i = i_; i <= size_ - std::strlen(substr); ++i) {
		c = *(c_str_ + i + std::strlen(substr));
		*(c_str_ + i + std::strlen(substr)) = 0;
		if (!std::strcmp(c_str_ + i, substr)) {
			*(c_str_ + i + std::strlen(substr)) = 0;
			return i;
		}
		*(c_str_ + i + std::strlen(substr)) = c;
	}

	return static_cast <Index> (-1);
}

BasicString::Index BasicString::find(const std::string& substr) const
{
	return find(substr.c_str(), 0);
}

BasicString::Index BasicString::find(const std::string& substr, Index i_) const
{
	return find(substr.c_str(), i_);
}



void BasicString::replace(Index i, size_t count, const char* str)
{
	if (i + count > size_) {
		throw "Out of range";
	}

	erase(i, count);
	insert(i, str);
}

void BasicString::replace(Index i, size_t count, const std::string& str)
{
	replace(i, count, str.c_str());
}

void BasicString::replace(size_t count, iterator i , char *str)
{
	replace(i - c_str_, count, str);
}

void BasicString::replace(size_t count, iterator i, const std::string &str)
{
	replace(i - c_str_, count, str);
}

BasicString BasicString::substr(Index i, size_t count) const
{
	if (i + count >= size_) {
		throw "Out of range";
	}

	BasicString ret;
	ret.insert(0, this->c_str() + i, count);

	return ret;
}

BasicString BasicString::substr(Index i) const
{
	if (i >= size_) {
		throw "Out of range";
	}


	BasicString ret;
	ret.insert(0, this->c_str() + i);

	return ret;
}


void BasicString::erase(Index i_, size_t count)
{
	if ((i_ < 0) || (i_ > size_)) {
		throw "Out of range";
	}

	for (int i = i_; i < size_ - count; ++i) {
		c_str_[i] = c_str_[i + count];
	}

	for (int i = size_ - count; i < size_; ++i) {
		c_str_[i] = '\0';
	}

	size_ -= count;
}

void BasicString::erase(size_t count, iterator i)
{
	erase(i - c_str_, count);
}





int BasicString::to_int() const
{
	return atoi(c_str());
}

char BasicString::at(int i) const
{
	if ((i < 0) || (i >= size_)) {
		throw "Out of range";
	}

	return c_str_[i];
}


BasicString::iterator BasicString::begin() const
{
	return iterator(&c_str_[0]);
}

BasicString::iterator BasicString::end() const
{
	return iterator(c_str_ + size_);
}

BasicString::const_iterator BasicString::cbegin()
{
	return const_iterator(&c_str_[0]);
}

BasicString::const_iterator BasicString::cend()
{
	return const_iterator(&c_str_[size_]);
}


BasicString::reverse_iterator BasicString::rbegin()
{
	return reverse_iterator(end());
}

BasicString::const_reverse_iterator BasicString::rbegin() const
{
	return const_reverse_iterator(end());
}

BasicString::const_reverse_iterator BasicString::crbegin() const
{
	return const_reverse_iterator(end());
}

BasicString::reverse_iterator BasicString::rend()
{
	return reverse_iterator(begin());
}

BasicString::const_reverse_iterator BasicString::rend() const
{
	return const_reverse_iterator(begin());
}

BasicString::const_reverse_iterator BasicString::crend() const
{
	return const_reverse_iterator(begin());
}

char* BasicString::c_str() const
{
	return c_str_;
}


void BasicString::change_capacity(size_t new_capacity)
{
	if (capacity() == new_capacity) {
		return;
	}
	
	char * tmp = c_str_;

	c_str_ = nullptr;
	c_str_ = new char[new_capacity];

	if (new_capacity > capacity()) {
		std::strcpy(c_str_, tmp);
	}
	else {
		std::strncpy(c_str_, tmp, new_capacity - 1);
	}

	delete[] tmp;

	capacity_ = new_capacity;
	if (size() >= capacity()) {
		size_ = capacity() - 1;
	}
}


size_t BasicString::round_size(size_t size)
{
	return ((((size) / default_size) + 1) * default_size);
}




BasicString operator+ (const BasicString& left, const char* right)
{
	BasicString res = left;
	return (res += right);
}

BasicString operator+ (const BasicString& left, const BasicString& right)
{
	return (left + right.c_str());
}



std::ostream& operator<< (std::ostream& os, const BasicString& str)
{
	return (os << str.c_str());
}


std::istream& operator >> (std::istream& is, BasicString& str)
{
	str.clear();
	char tmp[100] = { 0 };
	int i;
	char c;
	for (i = 0; (c = is.get()) != '\n'; ++i) {
		tmp[i] = c;
	}
	tmp[i] = '\0';
	str.insert(str.size(), tmp, sizeof(tmp));
	return is;
}