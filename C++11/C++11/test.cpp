#define _CRT_SECURE_NO_WARNINGS
#include"List.h"
#include<vector>
#include<map>
#include<functional>

class Date
 {
 public:
 Date(int year = 1 , int month = 1 , int day = 1)
     :_year(year)
     , _month(month)
     ,_day(day)
 {
     cout << "Date(int year , int month , int day)" << endl;
 }

  Date(const Date& d)
      :_year(d ._year)
      ,_month(d ._month)
      ,_day(d ._day)
  {
       cout << "Date(const Date& d)" << endl;
  }
 private:
        int _year;
        int _month;
        int _day;
 };
//列表初始化
void test1()
{
	//C++11支持的
	//内置类型支持
	int x1 = { 2 };

	Date d1= { 2020,1,1 };
    // 这里本质是用{ 2020,1,1 }构造一个Date临时对象
    // 临时对象再去拷贝构造d1，编译器优化后合二为一变成{ 2020,1,1 }直接构造初始化

	// {}初始化的过程中，可以省略掉=
	Date d2{ 2026,1,1 };

    vector<Date>v;
    v.push_back(d1);
    v.push_back(Date(2025, 1, 1));
    // 比起有名对象和匿名对象传参，使用{}更方便
    v.push_back({ 2025 , 1 , 1 });
}
//初始化列表
void test2()
{
    std::initializer_list<int> mylist;
    mylist = { 10 , 20 ,30 };
    cout << sizeof(mylist) << endl;
    
    // 这里begin和end返回的值initialize r_list对象中存的两个指针
    // 这两个指针的值跟i的地址跟接近，说明数组存在栈上
    int i = 0;
    cout << mylist.begin() << endl;
    cout << mylist.end() << endl;
    cout << &i << endl;
    
    //{}列表中可以有任意多个值
    //这两个写法语义上还是有差别的
    //第一个v1是直接构造
    vector<int>v1({ 1 ,2 ,3 ,4 ,5 });
    //第二个v2是构造临时对象+临时对象拷贝v2+优化为直接构造
    vector<int>v2 = { 1 ,2 ,3 ,4 ,5 };
    const vector<int>&v3 = { 1 ,2 ,3 ,4 ,5 };
    
    // 这里是pair对象的{}初始化和map的initialize r_list构造结合到⼀起用了
    map<string, string> dict = { {"sort", "排序"}, {"string", "字符串"} };
    
    // initialize r_list版本的赋值
    v1 = { 10 ,20 ,30 ,40 ,50 };
}
//左值引用和右值引用
void test3()
{
    //左值可取地址
    int* p = new int(0);
    int b = 1;
    const int c = b;
    *p = 10;
    string s("111111");
    s[0] = 'x';

    cout << &c << endl;
    cout << (void*)&s[0] << endl;   

    double x = 1.1, y = 2.2;
    //右值不可取地址
    //10;
    //x + y;
    //fmin(x, y);
    //string("11111");

    //cout <<&10 <<endl;
    //cout <<&(x+y) <<endl;
    //cout <<&(fmin(x, y)) <<endl;
    //cout <<&string ("11111") <<endl;

    //左值引用给左值取别名
    int& r1 = b;
    int*& r2 = p;
    int& r3 = *p;
    string& r4 = s;
    char& r5 = s[0];

    //右值引用给右值取别名
    int&& rr1 = 10;
    double&& rr2 = x + y;
    double&& rr3 = fmin(x, y);
    string&& rr4 = string("11111");

    //左值引用不能直接引用右值，但const左值引用可以引用右值
    const int& rx1 = 10;
    const double& rx2 = x + y;
    const double& rx3 = fmin(x, y);
    const string& rx4 = string("11111");

    //右值引用不能直接引用左值，但可以右值引用可以引用move（左值）
    int&& rrx1 = move(b);
    int*&& rrx2 = move(p);
    int&& rrx3 = move(*p);
    string&& rrx4 = move(s);
    char&& rrx5 = move(s[0]);

    //b,r1,rr1都是左值
    cout << &b << endl;
    cout << &r1 << endl;
    cout << &rr1 << endl;

    //注意右值引用rr1属性是左值，再使用右值引用需要move
    int&& rrx6 = move(rr1);

}

//左值右值参数匹配
void f(int& x)
{
    std::cout << "左值引用重载f(" << x << ")\n";
}
void f(const int& x)
{
    std::cout << "const左值引用重载f(" << x << ")\n";
}
void f(int&& x)
{
    std::cout << "右值引用重载f(" << x << ")\n";
}
void test4()
{
    int i = 1;
    const int ci = 1;

    f(1);
    f(i);
    f(ci);
    f(move(i));
}

//c++11移动构造与移动赋值
namespace mercury
{
	class string
	{
	public:
		typedef char* iterator;
		typedef const char* const_iterator;

		iterator begin()
		{
			return _str;
		}
		iterator end()
		{
			return _str + _size;
		}
		const_iterator begin() const
		{
			return _str;
		}
		const_iterator end() const
		{
			return _str + _size;
		}
		string(const char* str = "")
			:_size(strlen(str))
			, _capacity(_size)
		{
			cout << "string(char* str)-构造" << endl;
			_str = new char[_capacity + 1];
			strcpy(_str, str);
		}
		// 拷贝构造
		string(const string& s)
			:_str(nullptr)
		{
			cout << "string(const string& s) -- 拷贝构造" << endl;
			reserve(s._capacity);
			for (auto ch : s)
			{
				push_back(ch);
			}
		}
		// 移动构造
		string(string&& s) noexcept//右值引用提供修改右值的权限 
		{
			cout << "string(string&& s) -- 移动构造" << endl;
			// 转移掠夺你的资源
			swap(s);
		}
		// 移动赋值
		string& operator=(string&& s) noexcept
		{
			cout << "string& operator=(string&& s) -- 移动赋值" << endl;
			swap(s);
			return *this;
		}
		void swap(string& ss)
		{
			::swap(_str, ss._str);
			::swap(_size, ss._size);
			::swap(_capacity, ss._capacity);
		}
		string& operator=(const string& s)
		{
			cout << "string& operator=(const string& s) -- 拷贝赋值" <<
				endl;
			if (this != &s)
			{
				_str[0] = '\0';
				_size = 0;
				reserve(s._capacity);
				for (auto ch : s)
				{
					push_back(ch);
				}
			}
			return *this;
		}
		~string()
		{
			//cout << "~string() -- 析构" << endl;
			delete[] _str;
			_str = nullptr;
		}
		char& operator[](size_t pos)
		{
			assert(pos < _size);
			return _str[pos];
		}
		void reserve(size_t n)
		{
			if (n > _capacity)
			{
				char* tmp = new char[n + 1];
				if (_str)
				{
					strcpy(tmp, _str);
					delete[] _str;
				}
				_str = tmp;
				_capacity = n;
			}
		}
		void push_back(char ch)
		{
			if (_size >= _capacity)
			{
				size_t newcapacity = _capacity == 0 ? 4 : _capacity *
					2;
				reserve(newcapacity);
			}
			_str[_size] = ch;
			++_size;
			_str[_size] = '\0';
		}
		string& operator+=(char ch)
		{
			push_back(ch);
			return *this;
		}
		const char* c_str() const
		{
			return _str;
		}
		size_t size() const
		{
			return _size;
		}
	private:
		char* _str = nullptr;
		size_t _size = 0;
		size_t _capacity = 0;
	};
}
//旧版本编译器优化小，自定义类型传值返回，C++98只能用拷贝构造，C++11可替换拷贝构造为高效的移动构造
class Solution {
public:
	//传值返回需要拷贝
	mercury::string addStrings(mercury::string num1, mercury::string num2) {
		mercury::string str;
		size_t end1 = num1.size() - 1, end2 = num2.size() - 1;
		// 进位
		int next = 0;
		while (end1 >= 0 || end2 >= 0)
		{
			int val1 = end1 >= 0 ? num1[end1--] - '0' : 0;
			int val2 = end2 >= 0 ? num2[end2--] - '0' : 0;
			int ret = val1 + val2 + next;
			next = ret / 10;
			ret = ret % 10;
			str += ('0' + ret);
		}
		if (next == 1)
			str += '1';
		reverse(str.begin(), str.end());
		//cout << &str << endl;

		return str;
	}
};
void test5()
{
	mercury::string ret;
	ret = Solution().addStrings("11111111111111111111", "222222222222222222222222222");
	cout << ret.c_str() << endl;
	//cout << &ret<< endl;
}

//引用折叠：可把左值引用看成0，右值引用看成1,折叠看做乘法
//由于引用折叠限定，f1实例化以后总是一个左值引用
template<class T>
void f1(T& x)
{
}
//由于引用折叠限定，f2实例化后可以是左值引用，也可以是右值引用
template<class T>
void f2(T&& x)
{
}
//引用折叠测试
void test6()
{
	typedef int& lref;
	typedef int&& rref;
	int n = 0;
	lref& r1 = n; // r1 的类型是 int&
	lref&& r2 = n; // r2 的类型是 int&
	rref& r3 = n; // r3 的类型是 int&
	rref&& r4 = 1; // r4 的类型是 int&&

	//没有折叠->实例化为void f1(int& x) 
	f1<int>(n);
	//f1<int>(0); // 报错

	// 折叠->实例化为void f1(int& x) 左*左=左
	f1<int&>(n);
	//f1<int&>(0); // 报错

	// 折叠->实例化为void f1(int& x) 左*右=左
	f1<int&&>(n);
	//f1<int&&>(0); // 报错

	// const保留即可，不影响引用折叠
	// 折叠->实例化为void f1(const int& x) 左*左=左
	//f1<const int&>(n);
	//f1<const int&>(0);
	// 折叠->实例化为void f1(const int& x) 左*右=左
	f1<const int&&>(n);
	f1<const int&&>(0);

	// 没有折叠->实例化为void f2(int&& x) 
	//f2<int>(n); // 报错
	f2<int>(0);

	// 折叠->实例化为void f2(int& x) 右*左=左
	f2<int&>(n);
	//f2<int&>(0); // 报错

	// 折叠->实例化为void f2(int&& x) 右*右=右
	//f2<int&&>(n); // 报错
	f2<int&&>(0);
}

// 万能引用 
template<class T>
void Function(T&& t)
{
	int a = 0;
	T x = a;
	//x++;
	cout << &a << endl;
	cout << &x << endl << endl;
}
void test7()
{
	// 10是右值，推导出T为int，模板实例化为void Function(int&& t)
	Function(10);

	int a;
	// a是左值，推导出T为int&，引用折叠，模板实例化为void Function(int& t)
	Function(a); // 左值

	// std::move(a)是右值，推导出T为int，模板实例化为void Function(int&& t)
	Function(std::move(a));

	const int b = 8;
	// b是左值，推导出T为const int&，引用折叠，模板实例化为void Function(const int& t)
	// 所以Function内部会编译报错，x不能++
	Function(b);    // const 左值

	// std::move(b)右值，推导出T为const int，模板实例化为void Function(const int&& t)
	// 所以Function内部会编译报错，x不能++
	//Function(std::move(b)); // const 右值
}

//完美转发forward：
void Fun(int& x) { cout << "左值引用" << endl; }
void Fun(const int& x) { cout << "const 左值引用" << endl; }
void Fun(int&& x) { cout << "右值引用" << endl; }
void Fun(const int&& x) { cout << "const 右值引用" << endl; }
template <class T>
void function1(T&& t)
{
	Fun(t);
}
template <class T>
void function2(T&& t)
{
	Fun(forward<T>(t));
}
void test8()
{
	function1(1);//右值引用变量表达式的属性为左值，所以传给Fun()会匹配到左值引用的版本
	function2(1);//这里我们想保留对象属性继续传参,则需要靠完美转发forward实现
}

//可变参数模版
//template<class ...Args>
//void Print(Args ...args)
//{
//	cout << sizeof...(args) << endl;//sizeof...计算参数包中参数个数
//}

//int main()
//{
//	Print();//0个参数
//	Print(2);//1个参数
//	Print(1,"1111");//2个参数
//	Print(1, 1.0, 2);//3个参数
//	return 0;
//}

//原理1：编译本质上会结合引用折叠实例化出四个函数
//void Print();
//void Print(int&& arg1);
//void Print(int&& arg1, string && arg2);
//void Print(int&& arg1, double&& arg2, int&& arg3);

//如果没有可变参数模版，我们需要实现多个函数模版才能实现这样的功能
//void Print();
//template < class T1>
//void Print(T1 && arg1);
//template < class T1, class T2>
//void Print(T1 && arg1, T2 && arg2);
//template < class T1, class T2, class T3>
//void Print(T1 && arg1, T2 && arg2, T3 && arg3);

//编译时递归解析参数
void Show_list()
{
	//编译器递归的终止条件，当参数个数为0时匹配此函数
	cout << endl;
}
template<class T,class... Args>
void Show_list(T x,Args... args)
{
	cout << x << " ";
	//把参数包中第一个参数传给x,剩下的传给第二个参数包
	Show_list(args...);
}
template<class... Args>
void Print(Args... args)
{
	Show_list(args...);
}
//利用两个可变参数模版传参多次调用函数
template<class T>
const T& GetArg(const T& x)
{
	cout << x << " ";
	return x;
}
template<class... Args>
void Argument(Args... args)
{}
template<class... Args>
void print(Args... args)
{
	Argument(GetArg(args)...);
}
//int main()
//{
//	Print(1, '2', 3, "4 5 6");
//	print(1, string("xxxxx"), 2.2);
//
//	return 0;
//}


//C++11新增lambda表达式
void test9()
{
	//lambda函数格式：[capture-list] (parameters)-> return type {function boby}
	//lambda对象语法上没有类型,只能使用auto或包装器类型对象来接收
	auto add1 = [](double&& x, double&& y)->double {return x + y; };
	cout << add1(1, 1) << endl;
	function<double(double, double)> add2 = [](double&& x, double&& y) {return x + y; };
	cout << add2(1, 1) << endl;
	//捕获为空也不可省略
	//如果不用传参，可省略函数列表；
	//没有返回值可省略-> return type，一般返回值类型明确也可省略，编译器会自行推导
	
	int a = 1, b = 1, c = 1, d = 1;
	//捕获列表的使用：lambda表达式默认只能用函数体和传参的变量，使用外层作用域的变量则需要捕获
	//1.显式捕捉
	//[a,&b]中a表示传值捕捉，&b表示传引用捕捉
	auto func2 = [a, &b] {
		//a++;   //传值捕获相当于const修饰不可修改
		b++;     //传引用捕获可修改
	};
	//2.隐式捕捉：lambda中用了哪些变量,编译器会自动捕捉
	//=表示全传值捕获,&表示全传引用捕获
	auto func3 = [=] {/*a++;b++;*/};
	auto func4 = [&] { a++,b++;};
	//3.混合使用：第一个参数必须是&或=，后面的捕获必须是相反的捕获方式
	auto func5 = [=, &c, &d] {c++, d++; };
	auto func6 = [&, a, b] {c++, d++; };

	//在参数列表后使用mutable修饰，可修改传值捕获的对象
	auto func7 = [=]()mutable {
		a++, b++;
		cout << a << " " << b << endl;
		};
	func7();                                       
	//不过修改的还是形参，实参不会被影响
	cout << a << " " << b << endl;
}

int x = 1;
//全局变量和静态变量不能捕获也无需捕获，可直接使用
auto func1 = []
	{
		x++;
	};

//类新增关键字default表示生成默认函数，delete表示不生成默认函数
class Person
{
public :
        Person(const char* name = "", int age = 0)
               :_name (name)
               , _age(age)
        {}

        Person(const Person& p)
                :_name (p._name)
                ,_age(p._age)
         {}

         Person(Person&& p) = default;

        //Person(const Person&p) = delete;
 private :
         mercury::string _name;
         int _age;
 };

//包装器
//std::function(<functional>),实例对象可以包装存储其他的可以调用对象，包括函数指针、仿函数、lambda 、bind表达式等
//存储的可调用对象被称为std::function 的目标.若function不含目标，则称它为空，调用空function的目标会抛异常

int fun(int a , int b)
{
    return a + b;
}
struct Functor
{
 public :
     int operator() (int a , int b)
     {
            return a + b;
     }
 };
 class Plus
 {
 public :
     Plus(int n = 10)
             :_n (n)
     {}
     static int plusi(int a , int b)
     {
            return a + b;
     }
     double plusd(double a , double b)
     {
            return (a + b) * _n;
     }
 private :
     int _n;
 }; 

using placeholders::_1;
using placeholders::_2;
using placeholders::_3;

int main()
{
	//std ::function 的优势就是统一类型，对他们都可以进行包装，这样在很多地方就方便声明可调用对象的类型
	//包装各种可调用对象
	function<int(int , int)> f1 = fun;
	function<int(int , int)> f2 = Functor();
	function<int(int , int)> f3 = [](int a , int b) {return a + b; };
	
	cout << f1(1 , 1) << endl;
	cout << f2(1 , 1) << endl;
	cout << f3(1 , 1) << endl;

	// 包装静态成员函数
	// 成员函数要指定类域并且前面加&才能获取地址
	function<int(int , int)> f4 =&Plus::plusi;
	cout << f4(1 , 1) << endl;

	// 包装普通成员函数
	// 普通成员函数还有一个隐含的this指针参数，所以绑定时传对象或者对象的指针过去都可以
	// 对象调用成员函数指针时，使用.*运算符

	function<double(Plus*, double , double)> f5 =&Plus::plusd;
	Plus pd;
	cout << f5(&pd , 1.1 , 1.1) << endl;
	
	function<double(Plus, double , double)> f6 =&Plus::plusd;
	cout << f6(pd, 1.1, 1.1) << endl;
	cout << f6(Plus(), 1.1, 1.1) << endl;
	
	function<double(Plus&&, double , double)> f7 =&Plus::plusd;
	cout << f7(move(pd), 1.1, 1.1) << endl;
	cout << f7(Plus(), 1.1, 1.1) << endl;

	//bind可以用来调整参数个数和参数顺序(不常用)，可以把他看做一个函数适配器
	// bind 本质返回的一个仿函数对象
	// _1/_2/_3  这些占位符放到placeholders的一个命名空间中。
	//_1代表第一个实参
	//_2代表第二个实参
	// ...

	//bind一般用来绑死一些固定参数,就不需要每次都传递了
	function<double(double, double)> f8 = bind(&Plus::plusd, Plus(), _1, _2);
	cout << f8(1.1, 1.1) << endl;

	return 0;
}