#pragma once
#include<vector>

template<class T>
class Less
{
public:
	bool operator()(const T& x, const T& y)
	{
		return x < y;
	}
};

//模版特化
template<>
class Less<int*>
{
public:
	bool operator()( int* const& x,int* const& y)
	{
		return *x < *y;
	}
};

template<class T>
class Greater
{
public:
	bool operator()(const T& x, const T& y)
	{
		return x > y;
	}
};

using namespace std;

//本质是堆
namespace Mercury
{
	template<class T,class Container = vector<T>,class Compare=Less<T>>
	class priority_queue
	{
	public:
		void AdjustUp(int child)
		{
			Compare com;
			while (child > 0)
			{
				int parent = (child - 1) / 2;
				//if (_con[parent] < _con[child]),less:大堆;greater:小堆
				if (com(_con[parent], _con[child]))
				{
					swap(_con[parent], _con[child]);
					child = parent;
				}
				else 
				{
					break;
				}
			}
		}
		void AdjustDown(int parent)
		{
			int child = parent * 2 + 1;
			Compare com;
			while (child < _con.size())
			{
				                           //_con[child] > _con[child + 1]
				if (child+1< _con.size() && com(_con[child], _con[child + 1]))
				{
					child++;
				}
				   //_con[parent] > _con[child], less:大堆；greater:小堆
				if (com(_con[parent], _con[child]))
				{
					swap(_con[child], _con[parent]);
					parent = child;
					child = parent * 2 + 1;
				}
				else
				{
					break;
				}
			}
		}
		void push(const T& x)
		{
			_con.push_back(x);
			AdjustUp(_con.size() - 1);
		}
		void pop()
		{
			swap(_con[0], _con[_con.size() - 1]);
			_con.pop_back();
			AdjustDown(0);
		}
		const T& top() 
		{
			return _con[0];
		}
		size_t size() const
		{
			return _con.size();
		}

		bool empty() const
		{
			return _con.empty();
		}

	private:
		Container _con;
	};

}