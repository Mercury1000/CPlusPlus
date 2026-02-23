#pragma once
#include<iostream>
#include<assert.h>
using namespace std;

class Date
{
	//friend 友元函数声明，允许外部访问私有成员变量
	friend ostream& operator<<(ostream& out,const Date& d);
	friend istream& operator>>(istream& in,Date& d);

public:
	Date(int year=2026,int month=1,int day=1)
	{
		_year = year;
		_month = month;
		_day = day;
		if (!CheckDate())
		{
			cout << "非法日期：";
			Print();
		}

	}
	bool CheckDate() const;
	bool operator<(const Date& d) const;
	bool operator<=(const Date& d) const;
	bool operator>(const Date& d) const;
	bool operator>=(const Date& d) const;
	bool operator==(const Date& d) const;
	bool operator!=(const Date& d) const;

	Date operator+(int day) const;
	Date& operator+=(int day);

	Date operator-(int day) const;
	Date& operator-=(int day);

	// d1++;
	// d1.operator++(0);
	Date operator++(int);

	// ++d1;
	// d1.operator++();
	Date& operator++();

	// d1--;
	// d1.operator--(0);
	Date operator--(int);

	// --d1;
	// d1.operator--();
	Date& operator--();

	// d1 - d2
	int operator-(const Date& d) const;

	//void operator<<(ostream& out);
	void Print() const;
	
	//默认内联
	int GetMonthDay(int year,int month) const
	{
		assert(month > 0 && month < 13);
		static int MonthDay[13] = { -1,31,28,31,30,31,30,31,31,30,31,30,31 };
		if (month == 2 && (year % 400 == 0 || (year % 4 == 0 && year % 100 != 0)))
		{
			return 29;
		}
		return MonthDay[month];
	}

	//&一般不用自己重载
	Date* operator&()
	{
		//return this;
		//return nullptr;
		return (Date*)0x2673FF40;
	}

	const Date* operator&() const
	{
		return this;
		//return nullptr;
		//return (Date*)0x2673FE30;
	}
private:
	int _year;
	int _month;
	int _day;
};