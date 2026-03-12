#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<vector>
#include<list>
#include<stack>
#include<queue>
#include<algorithm>
#include<array>
#include"PriorityQueue.h"
using namespace std;

class Date
{
	friend ostream& operator<<(ostream& _cout, const Date& d);
public:
	Date(int year = 1900, int month = 1, int day = 1)
		: _year(year)
		, _month(month)
		, _day(day)
	{
	}

	bool operator<(const Date& d)const
	{
		return (_year < d._year) ||
			(_year == d._year && _month < d._month) ||
			(_year == d._year && _month == d._month && _day < d._day);
	}

	bool operator>(const Date& d)const
	{
		return (_year > d._year) ||
			(_year == d._year && _month > d._month) ||
			(_year == d._year && _month == d._month && _day > d._day);
	}
private:
	int _year;
	int _month;
	int _day;
};

ostream& operator<<(ostream& _cout, const Date& d)
{
	_cout << d._year << "-" << d._month << "-" << d._day;
	return _cout;
}

class DateLess
{
public:
	bool operator()(Date* p1, Date* p2)
	{
		return *p1 < *p2;
	}
};

void test1()
{
	    Mercury::priority_queue<Date> q1;
		q1.push(Date(2018, 10, 29));
		q1.push(Date(2018, 10, 28));
		q1.push(Date(2018, 10, 30));
		cout << q1.top() << endl;
		q1.pop();
	
		cout << q1.top() << endl;
		q1.pop();
	
		cout << q1.top() << endl;
		q1.pop();
	
		cout << endl;
	
		// 1、类类型不支持比较大小
		// 2、支持比较大小，但是比较的逻辑不是你想要的
		// 需要自己实现仿函数
	
		Mercury::priority_queue<Date*, vector<Date*>, DateLess> q2;
		//Mercury::priority_queue<Date*> q2;
		q2.push(new Date(2018, 10, 29));
		q2.push(new Date(2018, 10, 28));
		q2.push(new Date(2018, 10, 30));
		cout << *q2.top() << endl;
		q2.pop();
	
		cout << *q2.top() << endl;
		q2.pop();
	
		cout << *q2.top() << endl;
		q2.pop();
	
		//Mercury::priority_queue<int*> q3;
		Mercury::priority_queue<int*,vector<int*>,Less<int*>> q3;
		q3.push(new int(2));
		q3.push(new int(1));
		q3.push(new int(3));
	
		cout << *q3.top() << endl;
		q3.pop();
	
		cout << *q3.top() << endl;
		q3.pop();
	
		cout << *q3.top() << endl;
		q3.pop();
}
template<class T1, class T2>
class Data
{
public:
	Data() 
		:_d1(T1())
		,_d2(T2())
	{ 
		cout << "Data<T1, T2>" << endl; 
	}
private:
	T1 _d1;
	T2 _d2;
};

// 全特化
template<>
class Data<int, char>
{
public:
	Data() { cout << "Data<int, char>" << endl; }
};

// 偏特化/半特化
template<class T1>
class Data<T1, double>
{
public:
	Data() { cout << "Data<T1, double>" << endl; }
};

template<class T1>
class Data<T1, char>
{
public:
	Data() { cout << "Data<T1, char>" << endl; }
};

// 偏特化，传的类型是指针
template <typename T1, typename T2>
class Data <T1*, T2*>
{
public:
	Data()
	{
		cout << "Data<T1*, T2*>" << endl;
	}
};
//传引用
template <typename T1, typename T2>
class Data <T1&, T2&>
{
public:
	Data()
	{
		cout << "Data<T1&, T2&>" << endl;
	}
};
//同时传指针和引用
template <typename T1, typename T2>
class Data <T1&, T2*>
{
public:
	Data()
	{
		cout << "Data<T1&, T2*>" << endl;

		int a = 0;
		T1& x = a;
		T2* y = &a;
		T1 z = a;

		cout << typeid(x).name() << endl;
		cout << typeid(y).name() << endl;
	}

	void Push(const T1& x)
	{
	}
};
void test2()
{
	Data<int, int> d1;
	Data<int, char> d2;
	Data<int, double> d3;
	Data<char, double> d4;
	Data<char, char> d5;
	Data<char*, char*> d6;
	Data<int*, char*> d7;
	Data<int&, char&> d8;
	Data<int&, double&> d9;
	Data<int&, int*> d10;
}


int main()
{
	test2();

	return 0;
}