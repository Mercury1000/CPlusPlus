#pragma once
#include<iostream>
#include<assert.h>
using namespace std;

enum Colour
{
	RED,
	BLACK
};

template<class T>
struct RBTNode
{
	T _data;
	RBTNode<T>* _left;
	RBTNode<T>* _right;
	RBTNode<T>* _parent;
	Colour _col;

	RBTNode(const T& data)
		: _data(data)
		, _left(nullptr)
		, _right(nullptr)
		, _parent(nullptr)
	{}
};

template<class T,class Ref,class Ptr>
struct RBTreeIterator
{
	typedef RBTNode<T> Node;
	typedef RBTreeIterator<T, Ref, Ptr> Self;

	Node* _node;
	Node* _root;

	RBTreeIterator(Node* node,Node* root)
		:_node(node)
		,_root(root)
	{}

	//中序遍历：左->根->右
	Self& operator++()
	{
		//当前节点已经是根，要访问右子树的最左节点
		if (_node->_right)
		{
			Node* leftmost = _node->_right;
			while (leftmost->_left)
			{
				leftmost = leftmost->_left;
			}
			_node = leftmost;
		}
		else //往上找孩子是父亲左的那个祖先
		{
			Node* cur = _node;
			Node* parent = cur->_parent;
			while (parent && parent->_left != cur)
			{
				cur = parent;
				parent = cur->_parent;
			}
			_node = parent;
		}
		return *this;
	}
	//反向遍历:右->根->左
	Self& operator--()
	{
		if (_node==nullptr)//end()
		{
			//--end()特殊处理，找最右节点
			Node* rightmost = _root;
			while (rightmost && rightmost->_right)
			{
				rightmost = rightmost->_right;
			}
			_node = rightmost;
		}
		else if (_node->_left)//找左子树的最右节点
		{
			Node* rightmost = _node->_left;
			while (rightmost->_right)
			{
				rightmost = rightmost->_right;
			}
			_node = rightmost;
		}
		else //往上找孩子是父亲右的那个祖先
		{
			Node* cur = _node;
			Node* parent = cur->_parent;
			while (parent && parent->_right!= cur)
			{
				cur = parent;
				parent = cur->_parent;
			}
			_node = parent;
		}
		return *this;
	}
	Ref operator*()
	{
		return _node->_data;
	}
	Ptr operator->()
	{
		return &_node->_data;
	}
	bool operator!= (const Self& s) const
	{
		return _node != s._node;
	}
	bool operator== (const Self& s) const
	{
		return _node == s._node;
	}
};


template<class K, class T,class KeyOfT>
class RBTree
{
	typedef RBTNode<T> Node;
public:
	typedef RBTreeIterator<T, T&, T*> Iterator;
	typedef RBTreeIterator<T, const T&, const T*> ConstIterator;
	RBTree()
		:_root(nullptr)
	{}
	~RBTree()
	{
		Destroy(_root);
		_root = nullptr;
	}
	Iterator Begin()
	{
		Node* leftmost = _root;
		while (leftmost && leftmost->_left)
		{
			leftmost = leftmost->_left;
		}
		return Iterator(leftmost, _root);
	}

	Iterator End()
	{
		return Iterator(nullptr, _root);
	}

	ConstIterator Begin() const
	{
		Node* leftmost = _root;
		while (leftmost && leftmost->_left)
		{
			leftmost = leftmost->_left;
		}
		return ConstIterator(leftmost, _root);
	}
	ConstIterator End() const
	{
		return ConstIterator(nullptr, _root);
	}

	pair<Iterator, bool> insert(const T& data)
	{
		//与普通搜索二叉树一样按key值插入
		if (_root == nullptr)
		{
			_root = new Node(data);
			_root->_col = BLACK;
			return {Iterator(_root,_root),true};
		}

		KeyOfT kot;
		Node* cur = _root;
		Node* parent = nullptr;

		while (cur)
		{
			if (kot(data) < kot(cur->_data))
			{
				parent = cur;
				cur = cur->_left;
			}
			else if (kot(data) > kot(cur->_data))
			{
				parent = cur;
				cur = cur->_right;
			}
			else
			{
				return { Iterator(cur,_root),false };
			}
		}
		Node* newnode = new Node(data);
		cur = newnode;
		//插入节点为红色
		cur->_col = RED;
                      
		if (kot(data) < kot(parent->_data))
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
		
		return {Iterator(newnode,_root),true};
	}

	Iterator find(const K& key)
	{
		KeyOfT kot;
		Node* cur = _root;
		while (cur)
		{
			if (key < kot(cur->_data))
			{
				cur = cur->_left;
			}
			else if (key > kot(cur->_data))
			{
				cur = cur->_right;
			}
			else
			{
				return Iterator(cur, _root);
			}
		}
		return End();
	}

	int size()
	{
		return _Size(_root);
	}
	int height()
	{
		return _Height(_root);
	}
private:
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
	void Destroy(Node* root)
	{
		if (root == nullptr) return;

		Destroy(root->_left);
		Destroy(root->_right);
		delete root;
	}
	Node* _root = nullptr;
};