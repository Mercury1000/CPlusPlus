#pragma once
#include<iostream>
#include<assert.h>
using namespace std;

enum Colour
{
	RED,
	BLACK
};

template<class K, class V>
struct RBTNode
{
	pair<K, V> _kv;
	RBTNode<K, V>* _left;
	RBTNode<K, V>* _right;
	RBTNode<K, V>* _parent;
	Colour _col;

	RBTNode(const pair<K, V>& kv)
		:_kv(kv)
		, _left(nullptr)
		, _right(nullptr)
		, _parent(nullptr)
	{}
};

template<class K, class V>
class RBTree
{
public:
	typedef RBTNode<K,V> Node;
	RBTree()
		:_root(nullptr)
	{}

	bool insert(const pair<K, V>& kv)
	{
		//与普通搜索二叉树一样按key值插入
		if (_root == nullptr)
		{
			_root = new Node(kv);
			_root->_col = BLACK;
			return true;
		}
		Node* cur = _root;
		Node* parent = nullptr;

		while (cur)
		{
			if (kv.first < cur->_kv.first)
			{
				parent = cur;
				cur = cur->_left;
			}
			else if (kv.first > cur->_kv.first)
			{
				parent = cur;
				cur = cur->_right;
			}
			else
			{
				return false;
			}
		}
		cur = new Node(kv);
		//插入节点为红色
		cur->_col = RED;
                      
		if (kv.first < parent->_kv.first)
		{
			parent->_left = cur;
		}
		else
		{
			parent->_right = cur;
		}
		//更新插入节点的_parent
		cur->_parent = parent;
	
		//父亲是红色，出现连续的红色节点，需要处理    
		while (parent&&parent->_col==RED)
		{
			Node* grandfather = parent->_parent;
			if (parent == grandfather->_left)
			{
				Node* uncle = grandfather->_right;
				if (uncle && uncle->_col == RED)
				{
					//变色
					parent->_col = uncle->_col = BLACK;
					grandfather->_col = RED;
					//爷爷成新插入节点继续进入循环
					cur = grandfather;
					parent = cur->_parent;
				}
				else //uncle不存在或者为黑色
				{
					if (cur == parent->_left)
					{
						//单旋+变色
						RotateR(grandfather);
						parent->_col = BLACK;
						grandfather->_col = RED;
					}
					else
					{
						//双旋+变色
						RotateL(parent);
						RotateR(grandfather);
						cur->_col = BLACK; 
						grandfather->_col = RED;
					}
					break; 
				}

			}
			else
			{
				Node* uncle = grandfather->_left;
				if (uncle && uncle->_col == RED)
				{
					//变色
					parent->_col = uncle->_col = BLACK;
					grandfather->_col = RED;
					//爷爷成新插入节点继续进入循环
					cur = grandfather;
					parent = cur->_parent;
				}
				else //uncle不存在或者为黑色
				{
					if (cur == parent->_right)
					{
						//单旋+变色
						RotateL(grandfather);
						parent->_col = BLACK;
						grandfather->_col = RED;
					}
					else
					{
						//双旋+变色
						RotateR(parent);
						RotateL(grandfather);
						cur->_col = BLACK;
						grandfather->_col = RED;
					}
					break;
				}
			}
		} 
		_root->_col = BLACK;
		
		return true;
	}

	void RotateR(Node* parent)
	{
		Node* subL = parent->_left;
		Node* subLR = subL->_right;

		parent->_left = subLR;
		if (subLR)
		{
			subLR->_parent = parent;
		}
		//parent有可能是整棵树的根，也可能是局部的子树
		// 如果是整棵树的根，要修改_root
		// 如果是局部的指针要跟上一层链接
		Node* parentParent = parent->_parent;
		subL->_right = parent;
		parent->_parent = subL;

		if (parentParent)
		{
			if (parentParent->_left == parent)
			{
				parentParent->_left = subL;
			}
			else
			{
				parentParent->_right = subL;
			}
			subL->_parent = parentParent;
		}
		else
		{
			_root = subL;
			subL->_parent = nullptr;

		}

	}
	void RotateL(Node* parent)
	{
		Node* subR = parent->_right;
		Node* subRL = subR->_left;

		parent->_right = subRL;
		if (subRL)
			subRL->_parent = parent;

		//parent有可能是整棵树的根，也可能是局部的子树
		// 如果是整棵树的根，要修改_root
		// 如果是局部的指针要跟上一层链接
		Node* parentParent = parent->_parent;
		parent->_parent = subR;
		subR->_left = parent;

		if (parentParent)
		{
			if (parentParent->_left == parent)
			{
				parentParent->_left = subR;
			}
			else
			{
				parentParent->_right = subR;
			}
			subR->_parent = parentParent;
		}
		else
		{
			_root = subR;
			subR->_parent = nullptr;
		}


	}
	Node* find(const K& key)
	{
		Node* cur = _root;
		while (cur)
		{
			if (key < cur->_kv.first)
			{
				cur = cur->_left;
			}
			else if (key > cur->_kv.first)
			{
				cur = cur->_right;
			}
			else
			{
				return cur;
			}
		}
		return nullptr;
	}
	bool IsBalance()
	{
		if (_root == nullptr) return true;

		if (_root->_col == RED) return false;

		//计算一条从根到叶路径的黑节点数作为参考值
		int refNum = 0;
		Node* cur = _root;
		while (cur)
		{
			if (cur->_col == BLACK) refNum++;
			cur = cur->_left;
		}
		
		return check(_root,0,refNum);
	}
	
	int size()
	{
		return _Size(_root);
	}
	int height()
	{
		return _Height(_root);
	}

	void InOrder()
	{
		_InOrder(_root);
		cout << endl;
	}
private:
	bool check(Node* root, int blackNum, const int refNum)
	{
		if (root == nullptr)
		{
			if (blackNum != refNum) 
			{
				cout << "存在黑色结点的数量不相等的路径" << endl;
				return false;
			}
			else return true;
		}
		//检查有没有连续红色节点,检查父节点
		if (root->_col == RED && root->_parent->_col == RED)
		{
			cout << root->_kv.first << "存在连续红色节点路径" << endl;
			return false;
		}
		//计算黑色节点数
		if (root->_col == BLACK) blackNum++;

		return check(root->_left, blackNum, refNum) && check(root->_right, blackNum, refNum);

	}
	int _Height(Node* root)
	{
		if (root == nullptr)
			return 0;
		int leftHeight = _Height(root->_left);
		int rightHeight = _Height(root->_right);
		return leftHeight > rightHeight ? leftHeight + 1 : rightHeight + 1;
	}
	int _Size(Node* root)
	{
		if (root == nullptr)
			return 0;

		return _Size(root->_left) + _Size(root->_right) + 1;
	}
	void _InOrder(Node* root)
	{
		if (root == nullptr) return;
		_InOrder(root->_left);
		cout << root->_kv.first << ":" << root->_kv.second << " ";
		_InOrder(root->_right);
	}
	Node* _root = nullptr;
};