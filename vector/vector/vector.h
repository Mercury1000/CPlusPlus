#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <assert.h>
#include <algorithm>

namespace Mercury
{

	template<class T>
	class vector
	{
	public:
		typedef T* iterator;
		typedef const T* const_iterator;

		// 构造 n 个值为 x 的元素
		vector(size_t n, const T& x = T())
		{
			reserve(n);
			for (size_t i = 0; i < n; i++)
			{
				push_back(x);
			}
		}

		// 迭代器区间构造 [begin, end)
		template<class InputIterator>
		vector(InputIterator begin, InputIterator end)
		{
			while (begin != end)
			{
				push_back(*begin);
				++begin;
			}
		}

		// 默认构造
		vector() = default;

		// 拷贝构造
		vector(const vector<T>& v)
		{
			reserve(v.size());
			for (auto& e : v)
			{
				push_back(e);
			}
		}

		// 移动构造
		vector(vector<T>&& v) noexcept
			: _start(nullptr), _finish(nullptr), _storage_end(nullptr)
		{
			swap(v);
		}

		// 拷贝赋值：现代写法，传值传参触发拷贝构造生成临时对象，再swap狸猫换太子
		vector<T>& operator=(vector<T> v)
		{
			swap(v);
			return *this;
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

		const_iterator begin() const { return _start; }
		const_iterator end()   const { return _finish; }
		iterator       begin()       { return _start; }
		iterator       end()         { return _finish; }

		size_t size()     const { return _finish - _start; }
		size_t capacity() const { return _storage_end - _start; }
		bool   empty()    const { return _start == _finish; }   // 补 const

		T& operator[](size_t i)
		{
			assert(i < size());
			return _start[i];
		}
		const T& operator[](size_t i) const
		{
			assert(i < size());
			return _start[i];
		}

		void swap(vector<T>& v) noexcept
		{
			std::swap(_start,       v._start);
			std::swap(_finish,      v._finish);
			std::swap(_storage_end,  v._storage_end);
		}

		// 预扩容：只开空间，不改变 size
		void reserve(size_t n)
		{
			// size() = _finish - _start，扩容后 _finish 会被重新计算
			// 所以先用 oldsize 保存原 size
			size_t oldsize = size();
			if (n > capacity())
			{
				T* tmp = new T[n];
				// 不能用 memcpy：自定义类型需要调用赋值运算符
				for (size_t i = 0; i < oldsize; i++)
				{
					tmp[i] = _start[i];
				}
				delete[] _start;
				_start       = tmp;
				_finish      = _start + oldsize;
				_storage_end = _start + n;
			}
		}

		// 变长：n > size() 时用 val 填充，n < size() 时截断
		void resize(size_t n, const T& val = T())
		{
			if (n < size())
			{
				_finish = _start + n;
			}
			else
			{
				if (n > capacity())
					reserve(n);
				while (_finish < _start + n)   // 用 _finish 直接比较，避免重复计算
				{
					*_finish = val;
					++_finish;
				}
			}
		}

		void push_back(const T& x)
		{
			if (_finish == _storage_end)
			{
				reserve(capacity() == 0 ? 4 : 2 * capacity());
			}
			*_finish = x;
			++_finish;
		}

		void pop_back()
		{
			assert(!empty());
			--_finish;
		}

		// 在 pos 位置前插入 val，返回新插入元素的位置
		// 注意：插入后原迭代器可能失效，需要用返回的新迭代器更新
		iterator insert(iterator pos, const T& val)
		{
			assert(pos >= _start);
			assert(pos <= _finish);

			size_t len = pos - _start;   // 先记录偏移量

			if (_finish == _storage_end)
			{
				reserve(capacity() == 0 ? 4 : 2 * capacity());
				// 扩容后原 pos 失效，需要重新计算
				pos = _start + len;
			}

			iterator end = _finish;
			while (end > pos)
			{
				*end = *(end - 1);
				--end;
			}

			*pos = val;
			++_finish;

			return pos;
		}

		// 删除 pos 位置的元素，返回被删元素的下一个迭代器
		// 注意：删除后 pos 及之后的迭代器可能失效
		iterator erase(iterator pos)
		{
			assert(!empty());
			assert(pos >= _start);
			assert(pos < _finish);   // erase 不允许等于 end()

			iterator cur = pos;
			while (cur < _finish - 1)
			{
				*cur = *(cur + 1);
				++cur;
			}
			--_finish;

			return pos;   // 返回被删元素的下一个位置（STL 规范）
		}

	private:
		iterator _start       = nullptr;
		iterator _finish      = nullptr;
		iterator _storage_end = nullptr;
	};

	// vector 专用的打印函数
	template<class T>
	void vectorprint(const vector<T>& v)
	{
		// 模板类内部 typedef 在类外使用时必须加 typename 告诉编译器这是类型
		typename vector<T>::const_iterator it = v.begin();
		while (it != v.end())
		{
			std::cout << *it;
			++it;
		}
	}
}

// 通用的容器打印函数（适用于任何带 begin/end 的容器）
template<class Container>
void ContainerPrint(const Container& c)
{
	for (auto e : c)
	{
		std::cout << e << " ";
	}
	std::cout << std::endl;
}
