#include "BasicString.h"


	
	WideString::WideString()
		: size_(0),
		capacity_(default_size),
		c_str_(new wchar_t[default_size]),
		data_(nullptr)
	{
		c_str_[0] = '\0';
	}

	WideString::WideString(const WideString& str)         // copy constructor
		: size_(str.size_),
		capacity_(str.capacity_),
		c_str_(new wchar_t[str.capacity_]),
		data_(nullptr)
	{
		std::wcscpy(this->c_str_, str.c_str_);
	}

	WideString::WideString(const BasicString& str) // copy constructor
		: size_(str.size()),
		capacity_(str.capacity()),
		c_str_(new wchar_t[str.capacity()]),
		data_(nullptr)
	{
		wcscpy(this->c_str_, _bstr_t(str.c_str()));
	}

	WideString::WideString(WideString&& str):
		size_(str.size()),
		capacity_(str.capacity()),
		c_str_(new wchar_t[str.capacity()]),
		data_(nullptr)          // move constructor
	{
		*this = std::move(str);
	}

	WideString::WideString(const wchar_t* str)
	{
		size_ = std::wcslen(str);
		capacity_ = round_size(size_);
		c_str_ = new wchar_t[capacity_];
		std::wcscpy(this->c_str_, str);

		data_ = nullptr;
	}

	WideString::WideString(std::initializer_list<wchar_t>& il)
		: size_(il.size()),
		capacity_(round_size(il.size())),
		c_str_(new wchar_t[round_size(il.size())]),
		data_(nullptr)
	{
		std::wcscpy(this->c_str_, il.begin());
	}

	

	WideString::WideString(const wchar_t* str, size_t count)
	{
		size_ = count;
		capacity_ = round_size(size_);
		c_str_ = new wchar_t[capacity_];
		std::memcpy(this->c_str_, str, count);

		data_ = nullptr;
	}

	WideString::WideString(size_t count, wchar_t c)
	{
		size_ = count;
		capacity_ = round_size(size_);
		c_str_ = new wchar_t[capacity_];
		std::memset(c_str_, c, count);

		data_ = nullptr;
	}

	WideString::WideString(unsigned int num)
	{
		wchar_t c;
		auto byte_size{ [](unsigned int num) -> int {
			return 1 + static_cast<int> (std::log2(num)) / 8;
		} };

		size_ = byte_size(num) * 2 + 2;        // 1 byte in hex = 2 symbols. + 2 symbols for '0', 'x'
		capacity_ = round_size(size());
		c_str_ = new wchar_t[capacity()];

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
	WideString::~WideString()
	{
		delete[] c_str_;
		c_str_ = nullptr;

		if (data_ != nullptr) {
			delete[] data_;
			data_ = nullptr;
		}
	}

	WideString& WideString::operator= (const wchar_t* str)
	{
		if (this->capacity_ < std::wcslen(str)) {
			change_capacity(round_size(std::wcslen(str)));
		}
		std::wcscpy(this->c_str_, str);
		this->size_ = std::wcslen(str);

		return*this;
	}

	WideString& WideString::operator= (const BasicString& str)
	{
		if (this->capacity_ < std::strlen(str.c_str())) {
			change_capacity(round_size(std::strlen(str.c_str())));
		}
		std::wcscpy(this->c_str_, _bstr_t(str.c_str()));
		this->size_ = std::strlen(str.c_str());
	
		return*this;
	}

	WideString& WideString::operator= (const WideString& str)     //  copy assigment
	{
		if (this != &str) {
			return (*this = str.c_str());
		}
		else {
			return*this;
		}
	}

	WideString& WideString::operator= (WideString&& str)  //  move assigment
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

	WideString& WideString::operator= (wchar_t c)
	{
		this->c_str_[0] = c;
		this->size_ = 1;

		return*this;
	}

	WideString& WideString::operator+= (const wchar_t* str)
	{
		if (this->capacity_ <= this->size_ + std::wcslen(str)) {
			change_capacity(round_size(this->size_ + std::wcslen(str)));
		}
		std::wcscat(this->c_str_, str);
		this->size_ += std::wcslen(str);

		return*this;
	}

	WideString& WideString::operator+= (const std::string& str)
	{
		return (*this += _bstr_t(str.c_str()));
	}

	WideString& WideString::operator+= (const WideString& str)
	{
		return (*this += str.c_str_);
	}
	bool WideString::operator== (const WideString& str) const
	{
		if (this == &str) {
			return true;
		}

		return (std::wcscmp(this->c_str_, str.c_str()) == 0);
	}

	bool WideString::operator!= (const WideString& str) const
	{
		return !(*this == str);
	}


	bool WideString::operator> (const WideString& str) const
	{
		return std::wcscmp(this->c_str(), str.c_str_) > 0;
	}

	bool WideString::operator< (const WideString& str) const
	{
		return std::wcscmp(this->c_str(), str.c_str_) < 0;
	}

	bool WideString::operator>= (const WideString& str) const
	{
		return std::wcscmp(this->c_str(), str.c_str_) >= 0;
	}

	bool WideString::operator<= (const WideString& str) const
	{
		return std::wcscmp(this->c_str(), str.c_str_) <= 0;
	}





	void WideString::clear()
	{
		*this = WideString();
	}



	void WideString::shrink_to_fit()
	{
		change_capacity(size() + 1);
	}

	wchar_t WideString::operator[] (Index i) const
	{
		return c_str_[i];
	}



	size_t WideString::size() const
	{
		return size_;
	}

	size_t WideString::capacity() const
	{
		return capacity_;
	}

	bool WideString::empty() const
	{
		return (size() == 0);
	}





	wchar_t* WideString::data()
	{
		if (data_ != nullptr) {
			delete[] data_;
		}

		data_ = new wchar_t[size()];
		std::memcpy(data_, c_str_, size());

		return data_;
	}



	void WideString::insert(Index i_, const wchar_t* mid_str)
	{
		if (i_ > size()) {
			throw "Out of range";
		}

		if (size_ + std::wcslen(mid_str) >= capacity_) {
			change_capacity(round_size(size_ + std::wcslen(mid_str) + 1));
		}


		for (int i = size_ + std::wcslen(mid_str) - 1; i >= i_ + std::wcslen(mid_str); --i) {
			c_str_[i] = c_str_[i - std::wcslen(mid_str)];
		}

		for (int i = i_, j = 0; i < i_ + std::wcslen(mid_str); ++i, ++j) {
			c_str_[i] = mid_str[j];
		}

		size_ += std::wcslen(mid_str);
		c_str_[size_] = '\0';
	}

	void WideString::insert(Index i, size_t count, wchar_t c)
	{
		wchar_t* mid_str = new wchar_t[((count / 8) + 1) * 8];
		std::wmemset(mid_str, c, count);
		mid_str[count] = '\0';
		insert(i, mid_str);
		delete[] mid_str;
	}
	void WideString::insert(Index i, wchar_t* mid_str, size_t count)
	{
		wmemcpy(mid_str, static_cast<const wchar_t*>(mid_str), count);
		mid_str[count] = '\0';
		insert(i, mid_str);
	}

	template <class inputiterator>
	void WideString::insert(const_iterator pos, inputiterator first, inputiterator last) //insert(iterators)
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

	void WideString::insert(Index i, const std::string& str)
	{
		insert(i, _bstr_t(str.c_str()));
	}

	void WideString::insert(Index i, const std::string& str, size_t count)
	{
		insert(i, _bstr_t(str.c_str()), count);
	}
	void WideString::insert(size_t count, iterator i, wchar_t c,int value)
	{
		insert(i - c_str_, count, c);
	}

	void WideString::insert(const std::string &str, iterator i,int value)
	{
		insert(i - c_str_, _bstr_t(str.c_str()));
	}

	void WideString::append(size_t count, wchar_t c)
	{
		wchar_t* tmp_str = new wchar_t[((count / 8) + 1) * 8];
		wmemset(tmp_str, c, count);
		tmp_str[count] = '\0';

		append(tmp_str, (int)0, count);

		delete[] tmp_str;
	}

	void WideString::append(const wchar_t* str)
	{
		append(str, 0, std::wcslen(str));
	}

	void WideString::append(const wchar_t* str, Index i, size_t count)
	{
		if (size_ + count > capacity_) {
			change_capacity(round_size(size_ + count + 1));
		}
		std::wcsncpy(this->c_str_ + size_, str + i, count);
		size_ += count;
		c_str_[size()] = '\0';
	}

	void WideString::append(const std::string& str)
	{
		append(_bstr_t(str.c_str()), 0, str.size());
	}

	void WideString::append(const std::string& str, Index i, size_t count)
	{
		append(_bstr_t(str.c_str()), i, count);
	}


	WideString::Index WideString::find(const wchar_t* substr) const
	{
		return find(substr, 0);
	}

	WideString::Index WideString::find(const wchar_t* substr, Index i_) const
	{
		wchar_t c;
		for (int i = i_; i <= size_ - std::wcslen(substr); ++i) {
			c = *(c_str_ + i + std::wcslen(substr));
			*(c_str_ + i + std::wcslen(substr)) = 0;
			if (!std::wcscmp(c_str_ + i, substr)) {
				*(c_str_ + i + std::wcslen(substr)) = 0;
				return i;
			}
			*(c_str_ + i + std::wcslen(substr)) = c;
		}

		return static_cast <Index> (-1);
	}

	WideString::Index WideString::find(const std::string& substr) const
	{
		return find(_bstr_t(substr.c_str()), 0);
	}

	WideString::Index WideString::find(const std::string& substr, Index i_) const
	{
		return find(_bstr_t(substr.c_str()), i_);
	}



	void WideString::replace(Index i, size_t count, const wchar_t* str)
	{
		if (i + count > size_) {
			throw "Out of range";
		}

		erase(i, count);
		insert(i, str);
	}

	void WideString::replace(Index i, size_t count, const std::string& str)
	{
		replace(i, count, _bstr_t(str.c_str()));
	}

	void WideString::replace(size_t count, iterator i , wchar_t *str)
	{
		replace(i - c_str_, count, str);
	}

	WideString WideString::substr(Index i, size_t count) const
	{
		if (i + count >= size_) {
			throw "Out of range";
		}

		WideString ret;
		ret.insert(0, this->c_str() + i, count);

		return ret;
	}

	WideString WideString::substr(Index i) const
	{
		if (i >= size_) {
			throw "Out of range";
		}


		WideString ret;
		ret.insert(0, this->c_str() + i);

		return ret;
	}


	void WideString::erase(Index i_, size_t count)
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

	void WideString::erase(size_t count, iterator i)
	{
		erase(i - c_str_, count);
	}





	int WideString::to_int() const
	{
		return _wtoi(c_str());
	}

	wchar_t WideString::at(int i) const
	{
		if ((i < 0) || (i >= size_)) {
			throw "Out of range";
		}

		return c_str_[i];
	}

	WideString::iterator WideString::begin() const
	{
		return iterator(&c_str_[0]);
	}

	WideString::iterator WideString::end() const
	{
		return iterator(c_str_ + size_);
	}

	WideString::const_iterator WideString::cbegin()
	{
		return const_iterator(&c_str_[0]);
	}

	WideString::const_iterator WideString::cend()
	{
		return const_iterator(&c_str_[size_]);
	}

	WideString::reverse_iterator WideString::rbegin()
	{
		return reverse_iterator(end());
	}

	WideString::const_reverse_iterator WideString::rbegin() const
	{
		return const_reverse_iterator(end());
	}

	WideString::const_reverse_iterator WideString::crbegin() const
	{
		return const_reverse_iterator(end());
	}

	WideString::reverse_iterator WideString::rend()
	{
		return reverse_iterator(begin());
	}

	WideString::const_reverse_iterator WideString::rend() const
	{
		return const_reverse_iterator(begin());
	}

	WideString::const_reverse_iterator WideString::crend() const
	{
		return const_reverse_iterator(begin());
	}

	wchar_t* WideString::c_str() const
	{
		return c_str_;
	}


	void WideString::change_capacity(size_t new_capacity)
	{
		if (capacity() == new_capacity) {
			return;
		}

		wchar_t * tmp = c_str_;

		c_str_ = nullptr;
		c_str_ = new wchar_t[new_capacity];

		if (new_capacity > capacity()) {
			std::wcscpy(c_str_, tmp);
		}
		else {
			std::wcsncpy(c_str_, tmp, new_capacity - 1);
		}

		delete[] tmp;

		capacity_ = new_capacity;
		if (size() >= capacity()) {
			size_ = capacity() - 1;
		}
	}


	size_t WideString::round_size(size_t size)
	{
		return ((((size) / default_size) + 1) * default_size);
	}




WideString operator+ (const WideString& left, const wchar_t* right)
{
	WideString res = left;
	return (res += right);
}

WideString operator+ (const WideString& left, const WideString& right)
{
	return (left + right.c_str());
}

WideString operator+ (const WideString& left, const std::wstring& right)
{
	return (left + right.c_str());
}


std::ostream& operator<< (std::ostream& os, const WideString& str)
{
	return (os << str.c_str());
}


std::istream& operator >> (std::istream& is, WideString& str)
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