#pragma once
#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

inline unsigned long __stl_next_prime(unsigned long n)
{
	// Note: assumes long is at least 32 bits.
	static const int __stl_num_primes = 28;
	static const unsigned long __stl_prime_list[__stl_num_primes] = {
		53, 97, 193, 389, 769,
		1543, 3079, 6151, 12289, 24593,
		49157, 98317, 196613, 393241, 786433,
		1572869, 3145739, 6291469, 12582917, 25165843,
		50331653, 100663319, 201326611, 402653189, 805306457,
		1610612741, 3221225473, 4294967291
	};
	const unsigned long* first = __stl_prime_list;
	const unsigned long* last = __stl_prime_list + __stl_num_primes;
	const unsigned long* pos = lower_bound(first, last, n);
	return pos == last ? *(last - 1) : *pos;
}

template<class K>
struct HashFunc
{
	size_t operator()(const K& key)
	{
		return (size_t)key;
	}
};
//模版特化：字符串哈希
template<>
struct HashFunc<string>
{
	size_t operator()(const string& s)
	{
		size_t hash = 0;
		for (auto ch : s)
		{
			hash += ch;
			hash *= 131;
		}
		return hash;
	}
};

namespace open_address
{
	enum State
	{
		EXIST,
		EMPTY,
		DELETE
	};

	template<class K, class V>
	struct HashData
	{
		pair<K, V> _kv;
		State _state = EMPTY;
	};

	template<class K, class V, class Hash = HashFunc<K>>
	class HashTable
	{
	public:
		HashTable()
			:_tables(__stl_next_prime(0))
			, _n(0)
		{}

		bool Insert(const pair<K, V>& kv)
		{
			if (Find(kv.first))
				return false;
			//负载因子 >= 0.7扩容
			if (_n * 10 / _tables.size() >= 7)
			{
				//现代写法：复用insert()方法插入新表，然后交换即可
				HashTable<K, V> newht;
				newht._tables.resize(__stl_next_prime(_tables.size() + 1));
				for (auto& data : _tables)
				{
					if (data._state == EXIST)
					{
						newht.Insert(data._kv);
					}
				}
				_tables.swap(newht._tables);
			}
			Hash hash;

			size_t hash0 = hash(kv.first) % (_tables.size());
			size_t hashi = hash0;
			size_t i = 1;
			while (_tables[hashi]._state != EMPTY)
			{
				//双重探测
				/*hashi = (hash0 + (i*i*flag)) % _tables.size();
				if (hashi < _tables.size())
					hashi += _tables.size();

				if (flag == 1)
				{
					flag = -1;
				}
				else
				{
					++i;
					flag = 1;
				}*/

				//线性探测
				hashi = (hash0 + i) % _tables.size();
				i++;
			}
			_tables[hashi]._kv = kv;
			_tables[hashi]._state = EXIST;
			++_n;
			return true;
		}
		HashData<K, V>* Find(const K& key)
		{
			Hash hash;
			size_t hash0 = hash(key) % _tables.size();
			size_t hashi = hash0;
			size_t i = 1;
			while (_tables[hashi]._state != EMPTY)
			{
				if (_tables[hashi]._state == EXIST
					&& _tables[hashi]._kv.first == key)
					return &_tables[hashi];
				else
				{
					//线性探测
					hashi = (hash0 + i) % _tables.size();
					i++;
				}
			}
			return nullptr;
		}

		bool Erase(const K& key)
		{
			HashData<K, V>* ret = Find(key);
			if (ret)
			{
				ret->_state = DELETE;
				--_n;
				return true;
			}
			else return false;
		}

	private:
		vector<HashData<K, V>> _tables;
		size_t _n;//记录数据个数
	};
}
namespace hash_bucket
{
	template<class K,class V>
	struct HashNode
	{
		pair<K, V> _kv;
		HashNode* _next;
		HashNode(const pair <K, V>& kv)
			:_kv(kv)
			,_next(nullptr)
		{}
	};

	template<class K, class V, class Hash = HashFunc<K>>
	class HashTable
	{
		typedef HashNode<K, V> Node;
	public:
		HashTable()
			:_tables(__stl_next_prime(0))
			, _n(0)
		{}

		bool Insert(const pair<K, V>& kv)
		{
			if (Find(kv.first))
				return false;

			Hash hash;
			//负载因子 >= 1扩容
			if (_n * 10 / _tables.size() >= 10)
			{
			//直接移动节点插入,避免增删节点降低效率
				vector<Node*> newht(__stl_next_prime(_tables.size()+1));
				for (int i = 0; i < _tables.size(); i++)
				{
					Node* cur = _tables[i];
					while (cur)
					{
						size_t hashi = hash(cur->_kv.first) % newht.size();
						Node* next = cur->_next;
						cur->_next = newht[hashi];
						newht[hashi]=cur;
						cur = next;
					}
					_tables[i] = nullptr;
				}
				_tables.swap(newht);
			}
			size_t hashi = hash(kv.first) % _tables.size();
			Node* newnode = new Node(kv);
			newnode->_next = _tables[hashi];
			_tables[hashi] = newnode;
			++_n;

			return true;
		}

		Node* Find(const K& key)
		{
			Hash hash;
			size_t hashi = hash(key) % _tables.size();
			Node* cur = _tables[hashi];
			while (cur)
			{
				if (cur->_kv.first == key)
				{
					return cur;
				}
				else
				{
					cur = cur->_next;
				}
			}
			return nullptr;
		}

		bool Erase(const K& key)
		{
			Hash hash;
			size_t hashi = hash(key) % _tables.size();
			Node* cur = _tables[hashi];
			Node* prev = nullptr;
			while (cur)
			{
				if (cur->_kv.first == key)
				{
					if (prev == nullptr) //头结点
					{
						_tables[hashi] = cur->_next;
					}
					else                 //中间节点
					{
						prev->_next = cur->_next;
					}
					delete cur;
					--_n;
					return true;
				}
				else
				{
					prev = cur;
					cur = cur->_next;
				}
			}
			return false;
		}

	private:
		vector<Node*> _tables;
		size_t _n;
	};
}