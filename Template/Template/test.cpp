#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<string>

using namespace std;

//函数模版
template<class T>//class可与typename相替换
void Swap(T& a, T& b)
{
	T tmp = a;
	a = b;
	b = tmp;
}

int Add(int a, int b)
{
	cout << "current function" << endl;
	return (a + b);
}

template<typename T>
int Add(const T& a, const T& b)
{
	return (a + b);
}

template<typename T1, typename T2>
int Add(const T1& a, const T2& b)
{
	return(a + b);
}

//类模版
template<class T>
class Stack
{
public:
	Stack(size_t capacity = 4)
	{
		_array = new T[capacity];
		_capacity = capacity;
		_size = 0;
	}

	void Push(const T& x);

private:
	T* _array;
	size_t _capacity;
	size_t _size;
};

//类模版成员函数声明定义不建议分离到两个文件
template<class T>
void Stack<T>::Push(const T& x)
{
	if (_capacity == _size)
	{
		T* tmp = new T[_capacity*2];
		memcpy(tmp, _array, sizeof(T) * _capacity);
		delete _array;
		_array=tmp;
		_capacity *= 2;
	}
	_array[_size] = x;
	++_size;
}


void TemplateTest()
{
	int a1 = 1, a2 = 2;
	double b1 = 2.5, b2 = 2.3;

	//Add(a1,b2);----类型不同，无法匹配模版，编译报错-----函数存在类型自动转换，模版函数则不能
	Add((double)a1, b2);//隐式实例化，用户自行强转
	Add<double>(a1, b2);//显式实例化，指定模版类型

	//一个非模板函数可以和一个同名的函数模板同时存在，而且该函数模板还可以被实例化为这个非模板函数
	Add(1, 2);//如果参数与非模版函数完全匹配，优先使用非模版函数
	Add(1, 1.5);//如果模版能生成更匹配的实例，则调用模版函数
}


int main()
{
	TemplateTest();

	//类模板实例化与函数模板实例化不同，类模板实例化需要在类模板名字后跟<>
	//然后将实例化的类型放在<>中即可，类模板名字不是真正的类，而实例化的结果才是真正的类。
	//Stack是类名，Stack<int>才是类型
	Stack<int> st1;


	return 0;
}