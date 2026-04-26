#pragma once
#include<iostream>
#include<assert.h>
using namespace std;

template<class K,class V>
struct AVLNode
{
	pair<K,V> _kv;
	AVLNode<K,V>* _left;
	AVLNode<K,V>* _right;
	AVLNode<K,V>* _parent;
	int _bf;

	AVLNode(const pair<K,V>& kv)
		:_kv(kv)
		,_left(nullptr)
		,_right(nullptr)
		,_parent(nullptr)
		,_bf(0)
	{}
};

template<class K, class V>
class AVLTree
{
public:
	typedef AVLNode<K,V> Node;
	AVLTree()
		:_root(nullptr)
	{}

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
			subL->_parent = parentParent;
			if (parentParent->_left == parent)
			{
				parentParent->_left = subL;
			}
			else
			{
				parentParent->_right = subL;
			}
		}
		else
		{
			_root = subL;
			subL->_parent = nullptr;

		}
		parent->_bf= subL->_bf = 0;

	}
	void RotateL(Node* parent)
	{
		Node* subR = parent->_right;
		Node* subRL = subR->_left;

		parent->_right = subRL;
		if (subRL)
			subRL->_parent=parent;
		//parent有可能是整棵树的根，也可能是局部的子树
		// 如果是整棵树的根，要修改_root
		// 如果是局部的指针要跟上一层链接
		Node* parentParent = parent->_parent;
		parent->_parent = subR;
		subR->_left = parent;

		if (parentParent)
		{
			subR->_parent = parentParent;
			if (parentParent->_left == parent)
			{
				parentParent->_left = subR;
			}
			else
			{
				parentParent->_right = subR;
			}
		}
		else
		{
			_root = subR;
			subR->_parent = nullptr;
		}
		parent->_bf = subR->_bf = 0;

	}

	void RotateLR(Node* parent)
	{
		Node* subL = parent->_left;
		Node* subLR = subL->_right;
		int bf = subLR->_bf;

		RotateL(subL);
		RotateR(parent);
		
		if (bf == 0)
		{
			parent->_bf = subL->_bf = subLR->_bf = 0;
		}
		else if (bf == 1)
		{
			parent->_bf = 0;
			subL->_bf = -1;
			subLR->_bf = 0;
		}
		else if (bf == -1)
		{
			parent->_bf = 1;
			subL->_bf = 0;
			subLR->_bf = 0;
		}
		else
		{
			assert(false);
		}
	}
	void RotateRL(Node* parent)
	{
		Node* subR = parent->_right;
		Node* subRL = subR->_left;
		int bf = subRL->_bf;

		RotateR(subR);
		RotateL(parent);

		if (bf == 0)
		{
			parent->_bf = subR->_bf = subRL->_bf = 0;
		}
		else if (bf == -1)
		{
			parent->_bf = 0;
			subR->_bf = 1;
			subRL->_bf = 0;
		}
		else if (bf == 1)
		{
			parent->_bf = -1;
			subR->_bf = 0;
			subRL->_bf = 0;
		}
		else
		{
			assert(false);
		}
	}

	bool insert(const pair<K,V>& kv)
	{
		//与普通搜索二叉树一样按key值插入
		if (_root == nullptr)
		{
			_root = new Node(kv);
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

		//更新平衡因子
		while (parent)
		{
			if (parent->_left == cur)
			{
				parent->_bf--;
			}
			else
			{
				parent->_bf++;
			}
			if (parent->_bf == 0) break;
			else if (parent->_bf == -1 || parent->_bf == 1)
			{
				cur = parent;
				parent = cur->_parent;
			}
			else if (parent->_bf == -2 || parent->_bf == 2)
			{
				if (parent->_bf == -2)
				{
					if (cur->_bf == -1)
						RotateR(parent);
					else
						RotateLR(parent);
				}
				else
				{
					if (cur->_bf == 1)
						RotateL(parent);
					else
						RotateRL(parent);
				}
				break;//旋转后parent->_bf==0
			}
			else
			{
				assert(false);
			}
		}
		return true;
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
	void InOrder()
	{
		_InOrder(_root);
		cout << endl;
	}
	bool isAVLTree()
	{
		return _isAVLTree(_root) != -1;
	}
private:
	void _InOrder(Node* root)
	{
		if (root == nullptr) return;
		_InOrder(root->_left);
		cout << root->_kv.first<<":"<<root->_kv.second<< " ";
		_InOrder(root->_right);
	}
	int _isAVLTree(Node* root)
	{
		if (root == nullptr) return 0;

		int leftH = _isAVLTree(root->_left);
		if (leftH == -1) return -1;
		int rightH = _isAVLTree(root->_right);
		if (rightH == -1) return -1;

		if (abs(leftH - rightH) > 1 || abs(root->_bf) > 1) return -1;

		return leftH > rightH ? leftH + 1 : rightH + 1;
	}
	Node* _root;
};
