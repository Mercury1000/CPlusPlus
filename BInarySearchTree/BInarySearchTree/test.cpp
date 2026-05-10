#define _CRT_SECURE_NO_WARNINGS
#include"BinarySearchTree.h"

void test1()
{
	BSTree<int> T1;
	T1.insert(3);
	T1.insert(1);
	T1.insert(5);
	T1.insert(8);
	T1.insert(2);

	T1.InOrder();

	T1.Erase(8);
	T1.Erase(1);
	T1.InOrder();

	int x; 
	while(cin >> x)
	{
		if (x == -1) break;
		if (T1.find(x)) cout << x << ":´æÔÚ" << endl;
		else cout << x << ":²»´æÔÚ" << endl;
	}
}


int main()
{
	test1();

	return 0;
}