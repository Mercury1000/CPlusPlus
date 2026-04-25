#define _CRT_SECURE_NO_WARNINGS
#include "AVLTree.h"

int main()
{
	AVLTree<int,int> tr;
	tr.insert({ 1,1 });
	tr.insert({ 5,2 });
	tr.insert({ 7,5 });
	tr.insert({ 2,5 });
	tr.insert({ 9,7 });
	tr.insert({ 22,42 });

	tr.InOrder();
	if (tr.isAVLTree()) cout << "yes" << endl;
	else cout << "no" << endl;

	return 0;
}