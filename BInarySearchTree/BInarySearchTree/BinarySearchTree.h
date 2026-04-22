#pragma once
#include<iostream>
using namespace std;

template<class K>
struct BSTNode
{
	K _key;
	BSTNode<K>* _left;
	BSTNode<K>* _right;

	BSTNode(const K& key=K())
		:_key(key),
		_left(nullptr),
		_right(nullptr)
	{}
};

template<class K>
class BSTree
{
public:
	typedef BSTNode<K> BSTNode;
	BSTree()
		:_root(nullptr)
	{ }

	bool insert(const K& key)
	{
		if (_root == nullptr)
		{
            _root = new BSTNode(key);
            return true;
		}
		
		BSTNode* cur = _root;
		BSTNode* parent = nullptr;

		while (cur)
		{
			if (key < cur->_key)
			{
				parent = cur;
				cur = cur->_left;
			}
			else if (key > cur->_key)
			{
				parent = cur;
				cur = cur->_right;
			}
			else
			{
				return false;
			}
		}
		cur = new BSTNode(key);
		if (key < parent->_key)
		{
			parent->_left = cur;
		}
		else
		{
			parent->_right = cur;
		}
		return true;
	}

	bool find(const K& key)
	{
		BSTNode* cur = _root;
		while (cur)
		{
			if (key < cur->_key)
			{
				cur = cur->_left;
			}
			else if(key > cur->_key)
			{
				cur = cur->_right;
			}
			else
			{
				return true;
			}
		}
		return false;
	}

	bool Erase(const K& key)
	{
		if (_root == nullptr)
		{
			return false;
		}
		BSTNode* cur = _root;
		BSTNode* parent = nullptr;

		while (cur)
		{
			if (key < cur->_key)
			{
				parent = cur;
				cur = cur->_left;
			}
			else if (key > cur->_key)
			{
				parent = cur;
				cur = cur->_right;
			}
			else //找到了
			{
				 //0 - 1个孩子的情况
				 // 删除情况1 2 3均可以直接删除，改变父亲对应孩子指针指向即可
				if (cur->_left == nullptr)
				{
					if (parent == nullptr)
					{
						_root = cur->_right;
					}
					if (parent->_left == cur)
					{
						parent->_left = cur->_right;
					}
					else
					{
						parent->_right = cur->_right;
					}
					delete cur;
					return true;
				}
				else if (cur->_right == nullptr)
				{
					if (parent == nullptr)
					{
						_root = cur->_left;
					}
					if (parent->_left == cur)
					{
						parent->_left = cur->_left;
					}
					else
					{
						parent->_right = cur->_left;
					}
					delete cur;
					return true;
				}
				else 
				{
					//有2个孩子，替换法删除
                    //假设这里我们取右子树的最小结点作为替代结点去删除
					//这里尤其要注意右子树的根就是最小情况的情况的处理
					//所以rightMinP初始化为cur，rightMin初始化为右子树的根

					BSTNode* rightMinP = cur;
					BSTNode* rightMin = rightMinP->_right;
					
					while (rightMin->_left)
					{
						rightMinP = rightMin;
						rightMin = rightMin->_left;
					}

					parent->_key = rightMin->_key;//直接覆盖即可

					if (rightMinP->_left == rightMin)
					rightMinP->_left = rightMin->_right;
					else //这里考虑了右子树的根是最小的情况
					rightMinP->_right = rightMin->_right;

					delete rightMin;
					return true;
				}
			}
		}
		return false;
	}

	void InOrder()
	{
		_InOrder(_root);
		cout << endl;
	}

private:
	void _InOrder(BSTNode* root)
	{
		if (root == nullptr) return;
		_InOrder(root->_left);
		cout << root->_key << " ";
		_InOrder(root->_right);
	}
	BSTNode* _root;
};

