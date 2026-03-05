#pragma once
#include<iostream>
#include<vector>
#include<string>
#include<assert.h>
#include<algorithm>


namespace Mercury
{

	template<class T>
	class vector
	{
	public:
		typedef T* iterator;
		typedef const T* const_iterator;

		vector(size_t n,const T& x=T())//缺省值给默认构造
		{
			reserve(n);
			for (size_t i = 0; i < n; i++)
			{
				push_back(x);
			}
		}
     template<class inputiterator>
	 vector(inputiterator begin, inputiterator end)
	 {
		 auto it = begin;
		 while (it != end)
		 {
			 push_back(*it);
			 it++;
		 }
	 }


		vector() = default;//c++11,表示默认构造使用缺省值初始化
		//v1(v2);
		vector(const vector<T>& v)
		{
			reserve(v.size());//提前开好空间，提高效率
			for (auto& e: v)//遇到传值调用就用引用
			{
				push_back(e);
			}
		}

		~vector()
		{
			if (_start)
			{
				delete[] _start;
				_start = _finish = _storage_end = nullptr;
			}
		}
		void clear()
		{
			_finish = _start;
		}

		vector<T>& operator=(const vector<T>& v)
		{
			//if (*this!=v)
			//{
			//	clear();
			//	reserve(v.size());//提前开好空间，提高效率
			//	for (auto& e : v)//遇到传值调用就用引用
			//	{
			//		push_back(e);
			//	}
			//}
			swap(v);
			return *this;
		}

		const_iterator begin() const
		{
			return _start;
		}
		const_iterator end() const
		{
			return _finish;
		}
		iterator begin() 
		{
			return _start;
		}
		iterator end() 
		{
			return _finish;
		}
		size_t size() const
		{
			return _finish-_start;
		}
		size_t capacity() const
		{
			return _storage_end - _start;
		}
		bool empty()
		{
			return _start == _finish;
		}

		T& operator[](size_t i)
		{
			assert(i < size());
			return _start[i];
		}
		void swap(vector<T>& v)
		{
			std::swap(_start, v._start);
			std::swap(_finish, v._finish);
			std::swap(_storage_end, v._storage_end);
		}
		void reserve(size_t n)
		{
			size_t oldsize = size();//size()=finish-start,finish未更新而start更新了，所以此时size无法使用，需要提前存好
			//当然也可以先更新finish,这时size是正确的,不过不推荐
			if (n > capacity())
			{
				T* tmp = new T[n];
				//memcpy(tmp, _start, size()*sizeof(T));浅拷贝，自定义类型不可用
				for (size_t i = 0; i < size(); i++)
				{
					tmp[i] = _start[i];
				}
				delete[] _start;
				_start = tmp;
				_finish = _start + oldsize;
				_storage_end = _start + n;
			}

		}

		void resize(size_t n,const T& val=T())
		{
			if (n < size())
			{
				_finish = _start + n;
			}
			else
			{
				reserve(n);
				while (n >size())
				{
					*_finish = val;
					_finish++;
				}
			}

		}

		void push_back(const T& x)
		{
			if (_finish==_storage_end)
			{
				reserve(capacity()==0 ? 4 : 2 * capacity());
			}
			*_finish = x;
			_finish++;
		}

		void pop_back()
		{
			assert(!empty());
			_finish--;
		}

		iterator insert(iterator pos,const T& val)//insert后的迭代器失效，不可直接使用,可用返回值更新位置，但指向位置含义改变
		{
			assert(pos >= _start);
			assert(pos <= _finish);
			if (_finish == _storage_end)
			{
				size_t len = pos - _start;
				reserve(capacity() == 0 ? 4 : 2 * capacity());
				  //异地扩容警惕指针失效
			//！！！！！！扩容后pos失效，需更新至新空间！！！！！！！
				pos = _start + len;
			}
			iterator end = _finish;
			while (pos<end)
			{
				*end = *(end - 1);
				end--;
			}

			*pos = val;
			_finish++;

			return pos;
		}

		void erase(iterator pos)
		{
			assert(!empty());
			assert(pos >= _start);
			assert(pos <= _finish);
			while (pos<_finish-1)
			{
				*pos = *(pos + 1);
				pos++;
			}
			_finish--;
		}


	private:
		iterator _start=nullptr;
		iterator _finish=nullptr;
		iterator _storage_end=nullptr;
	};

	template<class T>
	void vectorprint(const vector<T>& v)
	{
		typename vector<T>::const_iterator it=v.begin();
		//未实例化模版编译器没法往里面取东西，无法识别const_iterator是类型还是变量，所以需标明typename
		//用auto更方便
		while (it != v.end())
		{
			std::cout << *it;
			it++;
		}
	}
}

template<class Container>
void ContainerPrint(const Container& c)
{
	for (auto e : c)    
	{
		std::cout << e << " ";
	}
	std::cout << std::endl;
}