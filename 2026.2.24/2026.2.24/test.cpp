#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<stdlib.h>

using namespace std;

class B
{
public:
	B(int b, int B = 2)
	{
		_b = b;
		_B = B;
	}
private:
	int _b;
	int _B;
};
class A
{
public:
	//构造函数,无需传实参则为默认构造
	A(int a1=1,int a2=1)//初始化列表,括号里给初始化值，空缺按缺省值
		:_a1(a1),
		_a2(a2),
		_b1(),
		_b2(_a1),
		_B1(1,2)
	{
	}

	//析构函数,对象生命周期结束时自动调用，无申请资源时可不写
	~A()
	{
		free(ptr);
	}

private:
	//变量声明，一般需要在初始化列表进行初始化,按声明顺序依次初始化,与初始化列表出现顺序无关；可给缺省值。
	int _a1=1;
	int _a2=1;
	int* ptr = (int*)malloc(4);//可写表达式
	
	//必须在初始化列表初始化的
	B _B1;//无默认构造的类
	const int _b1=1;//const成员变量
	int& _b2;//引用成员变量

	//不能列表初始化的
	static int _c1;//静态变量存放在静态区，应在类外部初始化
};
static int _c1 = 1;

class C
{
public:
	C(int c=1)
	{
		_c = c;
	}
	//拷贝构造函数是构造函数的重载，第一个参数必须是类引用的类型；如果有多参数，后面参数需要有缺省值
	//自定义类型的拷贝一定会调用拷贝构造
	C(const C& C,int i=1)
	{
		_c = C._c;
	}

	int _c;
};

int main()
{
	C cc1(1);
	cc1=C(6);//赋值重载
	//匿名函数，生命周期只有一行，便于临时使用
	cout << cc1._c << endl;

	// new/delete 和 malloc/free最大区别是 new/delete对于【自定义类型】除了开空间还会调用构造函数和析构函数
	
	C* p1 = new C(2);// 注意：如果构造函数有参数时，此处需要传参，缺省可不传
	C* p2 = new C[5]{ 1,2,3,4,5 };
	
	delete p1;
	delete[] p2;
	//当使用new[]时,如果含自定义类型的话,编译器开辟数组一般会在内存块前多开辟一个整型空间记录数组长度(或其他,需根据编译器)
	//如果不加[],delete就不会释放此空间,造成内存泄漏

	return 0;
}