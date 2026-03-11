#define _CRT_SECURE_NO_WARNINGS
#include"List.h"
#include<list>


void listtest1()
{
	list<int> l1;
	l1.push_back(2);
	l1.push_back(1);
	l1.push_back(4);
	l1.push_back(3);

	//list的迭代器是双向迭代器,无法使用需要随机迭代器的算法库快排
	//sort(l1.begin(), l1.end());

	l1.sort(greater<int>());//只能使用效率较低的成员函数排序

	reverse(l1.begin(), l1.end());//reverse使用双向迭代器
	//使用成员倒置函数l1.reverse()效果一样

	list<int>::iterator it = l1.begin();
	while (it != l1.end())
	{
		cout << *it << ' ';
		it++;
	}
	cout << endl;

	//不支持随机迭代器：l1.insert(l1.begin()+1, 1);
	auto pos = find(l1.begin(), l1.end(), 2);
	l1.insert(pos, 1);//list的insert不会使迭代器失效，指向原位置
	*pos *= 10;
	for (auto e : l1)
	{
		cout << e << ' ';
	}
	cout << endl;

	l1.erase(pos);//erase则会使迭代器失效,继续使用原迭代器编译会报错
	//cout << *pos;

}

void listtest2()
{
	list<int> l1;
	l1.push_back(1);
	l1.emplace_back(2);//与push_back用法相似
	l1.emplace_back(3);

	for (auto e : l1)
	{
		cout << e << ' ';
	}
	cout << endl;

	struct A
	{
		A(int a = 0, int b = 0)
		{}
	};
	list<A> l2;
	l2.push_back(A(1, 2));//传匿名对象
	l2.emplace_back(1, 2);//emplace_back现阶段用法：支持直接传构造函数参数
}

void listtest3()
{
	list<int> first, second;
	first.push_back(1);
	first.push_back(4);
	first.push_back(5);

	second.push_back(2);
	second.push_back(3);
	second.push_back(6);

	first.merge(second);//按升序合并有序链表,会置空second列表

}

void listtest4()
{
	list<int> lt;
	lt.push_back(1);
	lt.push_back(2);
	lt.push_back(2);
	lt.push_back(5);
	lt.push_back(5);
	lt.push_back(7);
	lt.push_back(9);

	lt.unique();//去重，要求链表有序

	for (auto e : lt)
	{
		cout << e << ' ';
	}
	cout << endl;
}

void listtest5()
{
	list<int> mylist1, mylist2;
	list<int>::iterator it;

	// set some initial values:
	for (int i = 1; i <= 4; ++i)
		mylist1.push_back(i);      // mylist1: 1 2 3 4

	for (int i = 1; i <= 3; ++i)
		mylist2.push_back(i * 10);   // mylist2: 10 20 30

	it = mylist1.begin();
	++it;                         // points to 2

	mylist1.splice(it, mylist2); 
	// mylist1: 1 10 20 30 2 3 4
	// mylist2 (empty)
	// "it" still points to 2 (the 5th element)

	list<int> lt;
	lt.push_back(1);
	lt.push_back(2);
	lt.push_back(3);
	lt.push_back(4);
	lt.push_back(5);
	lt.push_back(6);

	for (auto e : lt)
	{
		cout << e << ' ';
	}
	cout << endl;

	//splice也可以自己剪切自己，调整当前链表顺序
	int x = 0; cin >> x;
	it = find(lt.begin(), lt.end(), x);
	if (it != lt.end())
	{
		//lt.splice(lt.begin(), lt, it);//转移一个节点
		lt.splice(lt.begin(), lt, it,lt.end());
	}

	for (auto e : lt)
	{
		cout << e << ' ';
	}
	cout << endl;
}

void listtest6()
{
	Mercury::list<int> lt;
	lt.push_back(1);
	lt.push_back(2);
	lt.push_back(3);
	
	Mercury::list<int>::iterator it = lt.begin();
	while (it != lt.end())
	{
		cout << *it << ' ';
		++it;
	}
	cout << endl;
	for (auto e : lt)
	{
		cout << e << ' ';
	}
	cout << endl;

	//拷贝构造
	Mercury::list<int> lt2(lt);
	for (auto e : lt)
	{
		cout << e << ' ';
	}
	cout << endl;
}

void listtest7()
{
	Mercury::list<int> l1;
	l1.push_back(0);

	Mercury::list<int> l2;
	l2.push_back(2);
	l2.push_back(3);
	l2.push_back(4);

	l1 = l2;
	l1.push_front(1);
	for (auto e : l1)
	{
		cout << e << ' ';
	}
	cout << endl;

	l1.pop_back();
	l1.pop_front();
	for (auto e : l1)
	{
		cout << e << ' ';
	}
	cout << endl;
}

void listtest8()
{
	list<int> l1 = { 1,2,3,4,5 };//{, , ,}为初始化列表initializer_list, 底层类似数组
	for (auto e : l1)
	{
		cout << e << ' ';
	}
	cout << endl;

	Mercury::list<int> l2 = { 1,2,3,4,5 };//{, , ,}为临时对象初始化列表initializer list, 底层是数组
	for (auto e : l2)
	{
		cout << e << ' ';
	}
	cout << endl;

}
struct AA
{
	int _a1 = 1;
	int _a2 = 1;
};

void listtest9()
{
	list<AA> lta;
	lta.push_back(AA());
	lta.push_back(AA());
	lta.push_back(AA());
	lta.push_back(AA());
	list<AA>::iterator ita = lta.begin();
	while (ita != lta.end())
	{
		//cout << (*ita)._a1 << ":" << (*ita)._a2 << endl;
		// 特殊处理，本来应该是两个->才合理，为了可读性，省略了一个->
		cout << ita->_a1 << ":" << ita->_a2 << endl;
		cout << ita.operator->()->_a1 << ":" << ita.operator->()->_a2 << endl;

		++ita;
	}
	cout << endl;
}

int main()
{
	
	listtest9();
	
	return 0;
}