#pragma once
#include<iostream>
#include<assert.h>
#include<algorithm>
using namespace std;
namespace Mercury
{
	template<class T>
	struct List_Node
	{
		List_Node(const T& data = T())
			: _data(data)
			, _prev(nullptr)
			, _next(nullptr)
		{}

		T _data;
		List_Node<T>* _prev;
		List_Node<T>* _next;
	};

	//迭代器模版，整合两种迭代器
	template<class T, class Ref, class Ptr>
	struct list_Iterator
	{
		typedef list_Iterator<T,T&,T*>  iterator;
		typedef list_Iterator<T, const T&, const T*>  const_iterator;
		typedef list_Iterator<T, Ref, Ptr> Self;

		typedef List_Node<T> Node;
		Node* _node;

		list_Iterator(Node* node)
			:_node(node)
		{}

		Ref operator*()
		{
			return _node->_data;
		}

		Self& operator++()
		{
			_node = _node->_next;
			return *this;
		}

		Self& operator++(int)
		{
			Self tmp = _node;
			_node = _node->_next;
			return tmp;
		}
		Self& operator--()
		{
			_node = _node->_prev;
			return *this;
		}
		Self& operator--(int)
		{
			Self tmp = _node;
			_node = _node->_prev;
			return tmp;
		}

		bool operator!=(const Self& it) const
		{
			return _node != it._node;
		}
		bool operator==(const Self& it) const
		{
			return _node == it._node;
		}
	};

	
	template<class T>
	class list
	{
		typedef List_Node<T> Node;
	public:
		typedef list_Iterator<T, T&, T*>  iterator;
		typedef list_Iterator<T, const T&, const T*>  const_iterator;

		list()
		{
			emptyinit();
		}
		//l2(l1)
		list(const list<T>& lt)
		{
			emptyinit();
			for (auto& e : lt)
			{
				push_back(e);
			}
		}
		list(const initializer_list<T>& il)
		{
			emptyinit();
			for (auto e : il)
			{
				push_back(e);
			}
		}

		~list()
		{
			clear();
			delete _head;
			_head = nullptr;
		}

		void clear()//保留哨兵位
		{
			auto it = begin();
			while (it != end())
			{
				it = erase(it);
			}
		}

		void emptyinit()
		{
			_head = new Node;
			_head->_prev = _head;
			_head->_next = _head;
			_size = 0;
		}

		iterator begin()
		{
			/*	iterator it(_head->_next);
			return it;*/
			//return iterator(_head->_next);
			return _head->_next;//隐式类型转换
		}
		iterator end()
		{
			return _head;
		}
		const_iterator begin() const
		{
			return _head->_next;
		}
		const_iterator end() const
		{
			return _head;
		}

		void swap(list<T>& lt)
		{
			std::swap(_head,lt._head);
			std::swap(_size,lt._size);
		}

		const list<T>& operator=(list<T> lt)
		{
			swap(lt);
			return *this;
		}

		void push_back(const T& x)
		{
			/*Node* newnode = new Node(x);
			newnode->_next = _head;
			newnode->_prev = _head->_prev;
			newnode->_prev->_next = newnode;
			_head->_prev = newnode;

			_size++;*/
			insert(end(), x);
		}

		void push_front(const T& x)
		{
			insert(begin(), x);
		}

		iterator insert(iterator pos,const T& x)
		{
			Node* cur = pos._node;
			Node* prev = cur->_prev;
			Node* newnode = new Node(x);

			newnode->_next = cur;
			newnode->_prev = prev;
			prev->_next = newnode;
			cur->_prev = newnode;

			_size++;

			return newnode;
		}

		iterator erase(iterator pos)
		{
			assert(pos != end());
			Node* cur = pos._node;
			Node* prev = cur->_prev;
			Node* next = cur->_next;
			
			prev->_next = next;
			next->_prev = prev;

			delete cur;
			--_size;

			return next;
		}

		void pop_back()
		{
			erase(--end());
		}

		void pop_front()
		{
			erase(begin());
		}

		size_t size() const
		{
			return _size;
		}
		bool empty() const
		{
			return _size == 0;
		}

	private:
		Node* _head;
		size_t _size=0;
	};

}

template<class Container>
void print_container(const Container& con)
{
	// const iterator -> 迭代器本身不能修改
	// const_iterator -> 指向内容不能修改
	typename Container::const_iterator it = con.begin();
	//auto it = con.begin();
	while (it != con.end())
	{
		//*it += 10;
		cout << *it << " ";
		++it;
	}
	cout << endl;

	for (auto e : con)
	{
		cout << e << " ";
	}
	cout << endl;
}