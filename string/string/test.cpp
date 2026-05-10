#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<string>

using namespace std;



int main()
{
	//构造
	string s1("hello world");
	//拷贝构造
	string s2(s1);
	string s3 = s1;
	//流运算符重载
	cout << s1 << endl;
	cout << s2 << endl;
	cout << s3 << endl;

	string s4(s1, 6, 5);//从指定位置开始拷贝,最后一个参数不输或超过长度默认到结尾
	cout << s4 << endl;

	string s5(10,'x');
	cout << s5 << endl;

	//遍历字符串
	//1.[]重载,用法与数组一致
	for (int i = 0; i < s1.size(); i++)
	{
		cout << s1[i] ;
	}
	cout << endl;
	//2.迭代器iterator
	string::iterator it = s1.begin();
	for (; it < s1.end(); it++)
	{
		cout << *it;
	}
	cout << endl;
	//3.字符赋值，自动迭代，自动结束（本质是第二种方法）
	for (auto ch : s1)
	{
		cout << ch;
	}
	cout << endl;

	//反向遍历，反向迭代器
	string::reverse_iterator rit = s1.rbegin();
	for (; rit!= s1.rend(); rit++)
	{
		cout << *rit;
	}
	cout << endl;
	//只读
	string::const_iterator cit = s1.cbegin();//直接写begin（）也可以
	string::const_reverse_iterator crit = s1.crbegin();

	//auto类型可在编译时自动推导接收值类型，必须初始化且不能作为函数参数，也不能作为数组类型
	auto a = 1.2;
	
	string s6("wow ");
	s6.reserve(64);//预留空间,避免频繁扩容

	//尾插
	s6.append(s6);//尾插字符串
	cout << s6 << endl;

	s6.push_back('6');//尾插字符
	cout << s6 << endl;

	s6 += "damn";
	s6 += '6';//最常用，都能插
	cout << s6 << endl;

	s6.insert(0,"1.");//指定插，有效率损失
	cout << s6 << endl;
	s6.erase(0,2);//指定删
	cout << s6 << endl;

	s6.clear();//清空字符串，但空间不会销毁
	s6 = "hello     world";
	size_t pos = s6.find(' ',0);//找到指定字符第一次出现的位置,从指定位置开始
	while (pos != string::npos)
	{
		s6.replace(pos, 1, "%%");//从pos位置开始往后替换n个字符，多换少不会覆盖，后面的数据会自动后移
		pos = s6.find(' ', pos + 2);//每次更新开始找的位置，提高效率
		cout << s6 << endl;
	}
	
	s6= "hello     world";
	//replace损耗效率，也不好提前预留位置，所以尾插到一个新string更好,效率损失相对较低
	string ret;
	for (auto ch : s6)
	{
		if (ch == ' ')
			ret += "%%";
		else
			ret += ch;
	}
	s6 = ret;
	cout << s6 << endl;


	s6 = "hello world";
	pos = s6.find_first_of("ol");//找到指定字符的所有位置
	while (pos != string::npos)
	{
		s6[pos]='*';
		pos = s6.find_first_of("ol", pos + 1);
	}
	cout << s6 << endl;
	//find_last_of则是倒着找，带not的则是找到指定字符之外的字符

	string sub = s1.substr(6);//子串创建,指定开始位置和长度
	cout << sub << endl;

	string s7;
	//std::swap(s7,s6)全局swap三次深拷贝，效率低下,但使用它还是会自动调用成员函数，所以两种是一样的
	s7.swap(s6);//深拷贝


	return 0;

}