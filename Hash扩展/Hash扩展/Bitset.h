#pragma once
#include<vector>
#include<iostream>

namespace mercury
{
	//解决某个数在不在的问题
	template<size_t N>
	class bitset
	{
	public:
		bitset()
		{
			_bs.resize(N / 32 + 1);
		}
		//将第x位设为1
		void set(size_t x)
		{
			size_t i = x / 32;
			size_t j = x % 32;
			_bs[i] |= (1 << j);
		}
		//将第x位设为0
		void unset(size_t x)
		{
			size_t i = x / 32;
			size_t j = x % 32;
			_bs[i] &= (~(1 << j));
		}
		//检测第x位：1返回true，0返回false
		bool test(size_t x)
		{
			size_t i = x / 32;
			size_t j = x % 32;
			return _bs[i] & (1 << j);
		}

	private:
		std::vector<int> _bs;
	};

	//解决某个数出现次数的问题
	template<size_t N>
	class doublebitset
	{
	public:
		void set(size_t x)
		{
			bool bit1 = _bs1.test(x);
			bool bit2 = _bs2.test(x);

			if (!bit1 && !bit2) //00->01
			{
				_bs2.set(x);
			}
			if (!bit1 && bit2) //01->10
			{
				_bs1.set(x);
				_bs2.unset(x);
			}
			if (bit1 && !bit2) //10->11
			{
				_bs2.set(x);
			}
		}
		int get_count(size_t x)
		{
			bool bit1 = _bs1.test(x);
			bool bit2 = _bs2.test(x);

			if (!bit1 && !bit2)     //00
			{
				return 0;
			}
			else if (!bit1 && bit2) //01
			{
				return 1;
			}
			else if (bit1 && !bit2) //10
			{
				return 2;
			}
			else                    //11
			{
				return 3;           //3个及以上
			}
		}
	private:
		mercury::bitset<N> _bs1;
		mercury::bitset<N> _bs2;
	};

}
void test_doublebitset()
{
	mercury::doublebitset<100> bs;
	int a[] = { 5,7,9,2,5,99,5,5,7,5,3,9,2,55,1,5,6,6,6,6,7,9 };
	for (auto e : a)
	{
		bs.set(e);
	}

	for (size_t i = 0; i < 100; ++i)
	{
		//cout << i << "->" << tbs.get_count(i) << endl;
		if (bs.get_count(i) == 1 || bs.get_count(i) == 2)
		{
			std::cout << i << std::endl;
		}
	}
}

void test_bitset1()
{
	int a1[] = { 5,7,9,2,5,99,5,5,7,5,3,9,2,55,1,5,6 };
	int a2[] = { 5,3,5,99,6,99,33,66 };

	mercury::bitset<100> bs1;
	mercury::bitset<100> bs2;

	for (auto e : a1)
	{
		bs1.set(e);
	}

	for (auto e : a2)
	{
		bs2.set(e);
	}

	for (size_t i = 0; i < 100; i++)
	{
		if (bs1.test(i) && bs2.test(i))
		{
			std::cout << i << std::endl;
		}
	}
}