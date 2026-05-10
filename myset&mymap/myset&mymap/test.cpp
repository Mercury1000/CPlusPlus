#define _CRT_SECURE_NO_WARNINGS
#include"Mymap.h"
#include"Myset.h"
void Print(const mercury::set<int>& s)
{
	mercury::set<int>::const_iterator it = s.end();
	while (it != s.begin())
	{
		--it;
		cout << *it << " ";
	}
	cout << endl;
}
void test_set1()
{
	mercury::set<int> s;
	int a[] = { 4 , 2 , 6 , 1 ,3 ,5 , 15 , 7 , 16 , 14 };
	for (auto e : a)
	{
		s.insert(e);
	}

	for (auto e : s)
	{
		cout << e << " ";
	}
	cout << endl;

	Print(s);
}
void test_set2()
{
	mercury::set<int> s;
	s.insert(5);
	s.insert(1);
	s.insert(3);
	s.insert(2);
	s.insert(6);

	mercury::set<int>::iterator sit = s.begin();
	//*sit += 10;
	while (sit != s.end())
	{
		cout << *sit << " ";
		++sit;
	}
	cout << endl;

	for (auto& e : s)
	{
		cout << e << " ";
	}
	cout << endl;

	Print(s);
}

void test_map()
{
    mercury::map<string, string> dict;
    dict.insert({ "sort", "≈≈–Ú" });
    dict.insert({ "left", "◊Û±ﬂ" });
    dict.insert({ "right", "”“±ﬂ" });

    dict["left"] = "◊Û±ﬂ£¨ £”‡";
    dict["insert"] = "≤Â»Î";
    dict["string"];

    mercury::map<string, string>::iterator it = dict.begin();
    while (it != dict.end())
    {
        // ≤ªƒ‹–ﬁ∏ƒfirst£¨ø…“‘–ﬁ∏ƒsecond
        //it->first += 'x ';
        it->second += 'x';

        cout << it->first << ":" << it->second << endl;
        ++it;
    }
    cout << endl;
}
int main()
{
	//test_set1();
	//test_set2();
	test_map();

	return 0;
}