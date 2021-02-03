#include <iostream>
#include <cassert>
#include "BasicString.h"




void basictest_1()
{
	BasicString a, b, c, d;

	a = "123", b = "4567", c = "89";
	d = a + b + c + d;
	d += "1";

	assert(!std::strcmp(a.c_str(), "123"));
	assert(!std::strcmp(b.c_str(), "4567"));
	assert(!std::strcmp(c.c_str(), "89"));
	assert(!std::strcmp(d.c_str(), "1234567891"));
	assert(a.size() == 3);
	assert(b.size() == 4);
	assert(c.size() == 2);
	assert(d.size() == 10);
}

void basictest_2()
{
	BasicString a("bbbbbbbbbbbbbbbbbbbbbbbb");
	BasicString b(a);
	BasicString c(""), d, e;

	e += "1";
	e += a;
	c += e;
	e = a;
	a = b;
	b += "213";

	d = a + b + c;
	
	assert(!std::strcmp(a.c_str(), "bbbbbbbbbbbbbbbbbbbbbbbb"));
	assert(!std::strcmp(b.c_str(), "bbbbbbbbbbbbbbbbbbbbbbbb213"));
	assert(!std::strcmp(c.c_str(), "1bbbbbbbbbbbbbbbbbbbbbbbb"));
	assert(!std::strcmp(d.c_str(), "bbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbb2131bbbbbbbbbbbbbbbbbbbbbbbb"));
	assert(!std::strcmp(e.c_str(), "bbbbbbbbbbbbbbbbbbbbbbbb"));

}

void basictest_comparation()
{
	BasicString a, b, c;

	a = "...............................................................123";
	b = "...............................................................12";
	c = "...............................................................12345";

	assert(a > b);
	assert(a < c);
	assert(b < a);
	assert(b < c);
	assert(c > a);
	assert(c > b);

	assert(a >= b);
	assert(a <= c);
	assert(b <= a);
	assert(b <= c);
	assert(c >= a);
	assert(c >= b);

	a = b = c = "";

	assert(a.empty());
	assert(b.empty());
	assert(c.empty());
}

void basictest_insert()
{
	BasicString a("11111111111111111111111111111122222222222222222222"), b(a), c(a);
	BasicString a_expected("111111111111111111111111111111oooooooooo22222222222222222222");
	BasicString b_expected("oooooooooo11111111111111111111111111111122222222222222222222");
	BasicString c_expected("11111111111111111111111111111122222222222222222222oooooooooo");

	a.insert(30, 10, 'o');
	b.insert(0, 10, 'o');
	c.insert(50, 10, 'o');

	assert(a == a_expected);
	assert(b == b_expected);
	assert(c == c_expected);
}

void basictest_erase()
{
	BasicString a("0123456789..................................................");
	BasicString b("....................0123456789..............................");
	BasicString c("..................................................0123456789");
	BasicString expected("..................................................");

	a.erase(0, 10);
	b.erase(20, 10);
	c.erase(50, 10);

	assert(a == expected);
	assert(b == expected);
	assert(c == expected);
}

void basictest_append()
{
	BasicString a("******************************");
	BasicString a_expected("******************************..............................llllllllllllllllllllllllllllll");
	BasicString empty;

	a.append("..............................");
	a.append("llllllllllllllllllllllllllllll");

	assert(a == a_expected);
	a.clear();
	assert(a == empty);
}

void basictest_replace()
{
	BasicString a("..............................REPLACE_ME....................");
	BasicString b("REPLACE_ME..................................................");
	BasicString c("..................................................REPLACE_ME");

	BasicString a_expected("..............................NEW_STRING....................");
	BasicString b_expected("NEW_STRING..................................................");
	BasicString c_expected("..................................................NEW_STRING");

	a.replace(30, 10, "NEW_STRING");
	b.replace(0, 10, "NEW_STRING");
	c.replace(50, 10, "NEW_STRING");

	assert(a == a_expected);
	assert(b == b_expected);
	assert(c == c_expected);
}

void basictest_find()
{
	BasicString a("0123456789012345678901234567890123456789___FIND_ME________");

	assert(a.find("FIND_ME") == 43);
}

void basictest_itterator()
{
	BasicString a("HELLO WORLD");
	BasicString res_1, res_1_correct("H-E-L-L-O- -W-O-R-L-D-");
	BasicString res_2, res_2_correct("D-L-R-O-W- -O-L-L-E-H-");

	for (auto i = a.begin(); i != a.end(); ++i) {
		res_1.append(1, *i);
		res_1 += "-";
	}

	for (auto i = a.rbegin(); i != a.rend(); ++i) {
		res_2.append(1, *i);
		res_2 += "-";
	}

	//std::cout << res_1 << std::endl;
	//std::cout << res_2;

	assert(res_1 == res_1_correct);
	assert(res_2 == res_2_correct);
}

void basictest_substr()
{
	BasicString a("______________________________0123456789__________________________");
	BasicString substr, expected_substr("0123456789");

	substr = a.substr(30, 10);
	assert(substr == expected_substr);
}

void basictest_to_int()
{
	BasicString a("987654321");
	assert(a.to_int() == 987654321);

}




void widetest_1()
{
	WideString a, b, c, d;

	a = "123", b = "4567", c = "89";
	d = a + b + c + d;
	d += "1";
	
	assert(!std::strcmp(_bstr_t(a.c_str()), "123"));
	assert(!std::strcmp(_bstr_t(b.c_str()), "4567"));
	assert(!std::strcmp(_bstr_t(c.c_str()), "89"));
	assert(!std::strcmp(_bstr_t(d.c_str()), "1234567891"));
	assert(a.size() == 3);
	assert(b.size() == 4);
	assert(c.size() == 2);
	assert(d.size() == 10);
}

void widetest_2()
{
	WideString a("bbbbbbbbbbbbbbbbbbbbbbbb");
	WideString b(a);
	WideString c(""), d, e;

	e += "1";
	e += a;
	c += e;
	e = a;
	a = b;
	b += "213";

	d = a + b + c;

	assert(!std::strcmp(_bstr_t(a.c_str()), "bbbbbbbbbbbbbbbbbbbbbbbb"));
	assert(!std::strcmp(_bstr_t(b.c_str()), "bbbbbbbbbbbbbbbbbbbbbbbb213"));
	assert(!std::strcmp(_bstr_t(c.c_str()), "1bbbbbbbbbbbbbbbbbbbbbbbb"));
	assert(!std::strcmp(_bstr_t(d.c_str()), "bbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbb2131bbbbbbbbbbbbbbbbbbbbbbbb"));
	assert(!std::strcmp(_bstr_t(e.c_str()), "bbbbbbbbbbbbbbbbbbbbbbbb"));

}

void widetest_comparation()
{
	WideString a, b, c;

	a = "...............................................................123";
	b = "...............................................................12";
	c = "...............................................................12345";

	assert(a > b);
	assert(a < c);
	assert(b < a);
	assert(b < c);
	assert(c > a);
	assert(c > b);

	assert(a >= b);
	assert(a <= c);
	assert(b <= a);
	assert(b <= c);
	assert(c >= a);
	assert(c >= b);

	a = b = c = "";

	assert(a.empty());
	assert(b.empty());
	assert(c.empty());
}

void widetest_insert()
{
	WideString a("11111111111111111111111111111122222222222222222222"), b(a), c(a);
	WideString a_expected("111111111111111111111111111111oooooooooo22222222222222222222");
	WideString b_expected("oooooooooo11111111111111111111111111111122222222222222222222");
	WideString c_expected("11111111111111111111111111111122222222222222222222oooooooooo");

	a.insert(30, 10, 'o');
	b.insert(0, 10, 'o');
	c.insert(50, 10, 'o');

	assert(a == a_expected);
	assert(b == b_expected);
	assert(c == c_expected);
}

void widetest_erase()
{
	WideString a("0123456789..................................................");
	WideString b("....................0123456789..............................");
	WideString c("..................................................0123456789");
	WideString expected("..................................................");

	a.erase(0, 10);
	b.erase(20, 10);
	c.erase(50, 10);

	assert(a == expected);
	assert(b == expected);
	assert(c == expected);

	WideString Andrey_Yuryevich("Laboratory work is not credited");
	WideString I_Expect("Laboratory work is credited");

	Andrey_Yuryevich.erase(19, 4);
	assert(Andrey_Yuryevich == I_Expect);
}

void widetest_append()
{
	WideString a("******************************");
	WideString a_expected("******************************..............................llllllllllllllllllllllllllllll");
	WideString empty;

	a.append("..............................");
	a.append("llllllllllllllllllllllllllllll");

	assert(a == a_expected);
	a.clear();
	assert(a == empty);
}

void widetest_replace()
{
	WideString a("..............................REPLACE_ME....................");
	WideString b("REPLACE_ME..................................................");
	WideString c("..................................................REPLACE_ME");

	WideString a_expected("..............................NEW_STRING....................");
	WideString b_expected("NEW_STRING..................................................");
	WideString c_expected("..................................................NEW_STRING");

	a.replace(30, 10, "NEW_STRING");
	b.replace(0, 10, "NEW_STRING");
	c.replace(50, 10, "NEW_STRING");

	assert(a == a_expected);
	assert(b == b_expected);
	assert(c == c_expected);
}

void widetest_find()
{
	WideString a("0123456789012345678901234567890123456789___FIND_ME________");

	assert(a.find("FIND_ME") == 43);
}

void widetest_itterator()
{
	WideString a("HELLO WORLD");
	WideString res_1, res_1_correct("H-E-L-L-O- -W-O-R-L-D-");
	WideString res_2, res_2_correct("D-L-R-O-W- -O-L-L-E-H-");

	for (auto i = a.begin(); i != a.end(); ++i) {
		res_1.append(1, *i);
		res_1 += "-";
	}

	for (auto i = a.rbegin(); i != a.rend(); ++i) {
		res_2.append(1, *i);
		res_2 += "-";
	}

	//std::cout << res_1 << std::endl;
	//std::cout << res_2;

	assert(res_1 == res_1_correct);
	assert(res_2 == res_2_correct);
}

void widetest_substr()
{
	WideString a("______________________________0123456789__________________________");
	WideString substr, expected_substr("0123456789");

	substr = a.substr(30, 10);
	assert(substr == expected_substr);
}

void widetest_to_int()
{
	WideString a("987654321");
	assert(a.to_int() == 987654321);

}

void unit_TestsWide()
{
	widetest_1();
	widetest_2();

	widetest_comparation();
	widetest_insert();
	widetest_erase();
	widetest_append();
	widetest_replace();
	widetest_find();

	widetest_substr();
	widetest_to_int();


	widetest_itterator();

	std::cout << "All Wide test completed\n";
}

void unit_testsBasic()
{
	basictest_1();
	basictest_2();

	basictest_comparation();
	basictest_insert();
	basictest_erase();
	basictest_append();
	basictest_replace();
	basictest_find();

	basictest_substr();
	basictest_to_int();

	basictest_itterator();

	std::cout << "All Basic test completed\n";
}



int main(void)
{
	int N=1;
	dynarray<int> f(10);
	dynarray<int> ff(10);
	f = { 1,2,3,4,5 };
	BasicString c(1000);
	WideString d(1000);
	BasicString a("1213");
	WideString b("1213");
	unit_testsBasic();
	unit_TestsWide();
	std::cout << f.size() << std::endl;
	std::cout << f.capacity() << std::endl;
	f.shrink_to_fit();
	std::cout << f.size() << std::endl;
	std::cout << f.capacity() << std::endl;
	f.assign(5,10);
	f.at(0);
	f.push_back(10);
	//f.shrink_to_fit();
	int gg = 1;
	dynarray<int>::iterator pos = f.begin();
	f.insert(pos,1,2);
	f.at(0);
	dynarray<int>::iterator pos1 = f.begin();
	f.erase(pos1);
	f.swap(ff);
	f = ff;
	f == ff;
	f[1];
	system("pause");
	a.clear();
	b.clear();
	return 0;
}




