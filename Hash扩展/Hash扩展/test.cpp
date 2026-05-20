#define _CRT_SECURE_NO_WARNINGS
#include<bitset>
#include"Bitset.h"

using namespace std;
#include"Bloomfilter.h"
int main()
{
	//标准库中的位图在栈上开空间，开不了太大
	//std::bitset<UINT_MAX> bs;
	//解决方法：用new在堆上开空间
	//std::bitset<UINT_MAX>* ptr = new std::bitset<UINT_MAX>();

	//用vector模拟实现直接在堆上开空间
	//mercury::bitset<-1> bs1;
	//mercury::bitset<0xffffffff> bs2;
	//mercury::bitset<UINT_MAX> bs3;
	
	//test_bitset1();
	//test_doublebitset();
	TestBloomFilter2();

	return 0;
}