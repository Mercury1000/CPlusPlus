#define _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<vector>
#include<list>
#include<stack>
#include<queue>
#include<algorithm>
using namespace std;

#include"Stack.h"
#include"Queue.h"
#include"PriorityQueue.h"

void test1()
{
	Mercury::stack<int, vector<int>> st;
	//Mercury::stack<int, list<int>> st;
	//Mercury::stack<int, vector<int>> st;

	// 类模板实例化时，按需实例化，使用哪些成员函数就实例化哪些，不会全实例化
	st.push(1);
	st.push(2);
	st.push(3);
	st.push(4);

	cout << st.top() << endl;
	st.pop();

	Mercury::queue<int, list<int>> q;
	//queue<int> q;
	q.push(1);
	q.push(2);
	q.push(3);
	q.push(4);

	cout << q.front() << endl;
	q.pop();
}

void test2()
{
	srand((unsigned int)time(0));
	const int N = 1000000;

	deque<int> dq;
	vector<int> v;

	for (int i = 0; i < N; ++i)
	{
		auto e = rand() + i;
		v.push_back(e);
		dq.push_back(e);
	}

	int begin1 = clock();
	sort(v.begin(), v.end());
	int end1 = clock();

	int begin2 = clock();
	sort(dq.begin(), dq.end());
	int end2 = clock();

	printf("vector:%d\n", end1 - begin1);
	printf("deque:%d\n", end2 - begin2);
}

void test3()
{
	// 仿函数：本质是一个类，这个类重载operator(),他的对象可以像函数一样使用
	Mercury::priority_queue<int, vector<int>, Greater<int>> pq;
	//bit::priority_queue<int> pq;
	pq.push(4);
	pq.push(1);
	pq.push(5);
	pq.push(7);
	pq.push(9);
	while (!pq.empty())
	{
		cout << pq.top() << " ";
		pq.pop();
	}
	cout << endl;

}

int main()
{
	test3();

	return 0;
}