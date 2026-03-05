#define _CRT_SECURE_NO_WARNINGS
#include"vector.h"

using namespace std;

void vectortest1()
{
	vector<int> v1(10, 1);
	vector<int>v2(v1);
	vector<int>v3(v1.begin(), v1.end());//迭代器区间初始化，其他容器也可
}

void vectortest2()
{
	vector<int> v1(10,1);
	v1.reserve(20);
	cout << v1.capacity() << endl;
	v1.reserve(5);
	cout << v1.capacity() << endl;

	v1.resize(15, 2);
	cout << v1.size() << endl;
	//顺序表[]遍历
	for (int i=0 ;i<v1.size();i++)
	{
		cout << v1[i]<< " ";
	}
	cout << endl;

	v1.resize(5);
	cout << v1.size() << endl;

	for (auto e : v1)
	{
		cout << e << " ";
	}
}

void vectortest3()
{
	vector<int> v1;
	v1.push_back(1);
	v1.push_back(1);
	v1.push_back(1);
	v1.insert(v1.begin() + v1.size(), 2);//用迭代器定位
	v1.erase(v1.begin());
	for (auto e : v1)
	{
		cout << e << " ";
	}
}

void vectortest4()
{
	//存放自定义类型
	vector<string> v1(1,"xxxx");
	v1.push_back("yyyy");
	for (const auto& e : v1)//自定义类型传值有拷贝构造，所以传引用
	{
		cout << e << " ";
	}
	cout << endl;

	//二维数组
	vector<int> v(10, 1);
	vector<vector<int>> vv;
	vv.push_back(v);
	vv.push_back(v);
	for (int i = 0; i < vv.size(); i++)
	{
		for (int j = 0; j < vv[i].size(); j++)
		{
			cout << vv[i][j] << " ";
		}
		cout << endl;
	}
}

void vectortest5()
{
	Mercury::vector<int> v1;
	v1.push_back(1);
	v1.push_back(1);
	v1.push_back(1);
	v1.push_back(1);
	v1.push_back(1);
	ContainerPrint(v1);

	Mercury::vector<int> v2(v1);
	v2.insert(v2.begin(), 0);
	ContainerPrint(v2);
	v2.erase(v2.begin());
	ContainerPrint(v2);
}

void vectortest6()
{
	vector<string> v4(10, "1111111");
	ContainerPrint(v4);
}

int main()
{
	vectortest6();
	return 0;
}