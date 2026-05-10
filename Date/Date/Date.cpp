#define _CRT_SECURE_NO_WARNINGS
#include"Date.h"

void Date::Print() const
{
	cout << _year << "-" << _month << "-" << _day << endl;
}

bool Date::CheckDate() const
{
	if (_month < 1 || _month>12||_day<1|| _day > GetMonthDay(_year, _month))
		return false;
	else
		return true;
}

bool Date::operator<(const Date& d) const
{
	if (_year < d._year)
	{
		return true;
	}
	else
	{
		if (_year == d._year)
		{
			if (_month < d._month)
			{
				return true;
			}
			if (_month == d._month)
			{
				return _day < d._day;
			}
		}
	}
	return false;
}
bool Date::operator<=(const Date& d) const
{
	return *this < d || *this == d;
}
bool Date::operator>(const Date& d) const
{
	return !(*this <= d);
}
bool Date::operator>=(const Date& d) const
{
	return !(*this < d);
}
bool Date::operator!=(const Date& d) const
{
	return !(*this == d);
}

bool Date::operator==(const Date& x) const
{
	return _year == x._year && _month == x._month && _day == x._day;
}

Date& Date::operator+=(int day)
{
	if (day < 0)
	{
		*this -= (-day);
	}
	else
	{
		_day += day;
		while (_day > GetMonthDay(_year, _month))
		{
			_day -= GetMonthDay(_year, _month);
			_month++;
			if (_month == 13)
			{
				_year++;
				_month = 1;
			}
		}
	}
	return *this;
}

Date Date::operator+(int day) const
{
	Date tmp = *this;
	tmp += day;
	return tmp;
}
Date Date::operator-(int day) const
{
	Date tmp = *this;
	tmp -= day;
	return tmp;
}
Date& Date::operator-=(int day)
{
	if (day < 0)
	{
		*this += (-day);
	}
	else
	{
		_day -= day;
		while (_day <= 0)
		{
			--_month;
			if (_month == 0)
			{
				_year--;
				_month = 12;
			}
			_day += GetMonthDay(_year, _month);

		}
	}
	return *this;
}
// d1++;
// d1.operator++(0);
Date Date::operator++(int)
{
	Date tmp = *this;
	*this += 1;
	return tmp;
}

// ++d1;
// d1.operator++();
Date& Date::operator++()
{
	*this += 1;
	return *this;
}

// d1--;
// d1.operator--(0);
Date Date::operator--(int)
{
	Date tmp = *this;
	*this -= 1;
	return tmp;
}

// --d1;
// d1.operator--();
Date& Date::operator--()
{
	*this -= 1;
	return *this;
}


int Date::operator-(const Date& d) const
{
	int n = 0,flag=1;
	Date max = *this, min = d;
	if (*this < d)
	{
		max = d;
		min = *this;
		flag = -1;
	}
	while (min != max)
	{
		++min;
		++n;
	}
	return n * flag;
}

ostream& operator<<(ostream& out, const Date& d)
{
	out << d._year << "年" << d._month << "月" << d._day <<"日" << endl;
		return out;
}
istream& operator>>(istream& in,Date& d)
{
	while (1)
	{
		cout << "请依次输入年月日：>";
		in >> d._year >> d._month >> d._day;

		if (!d.CheckDate())
		{
			cout << "输入日期非法：";
			d.Print();
			cout << "请重新输入!!" << endl;
		}
		else
		{
			break;
		}
	}
	return in;
}