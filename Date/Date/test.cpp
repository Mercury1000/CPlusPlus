#define _CRT_SECURE_NO_WARNINGS
#include "Date.h"

void DateTest()
{
	/*Date d1;
	Date d2(2026, 2, 23);
	d1 = d2;

	d2.Print();
	Date d3(2026, 4, 11);
	d3.Print();
	cout << d3 - d1 << endl;*/

	Date d1, d2;
	cin >> d1 >> d2;
	cout << d2 - d1 << endl;
}



int main()
{
	//隐式类型转换,拷贝临时变量+构造
	Date aa = 2;
	Date bb = { 2020,1,3 };

	return 0;
}