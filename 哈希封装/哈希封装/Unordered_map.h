#pragma once
#include"HashTable.h"

template<class K,class V,class Hash = HashFunc<K>>
class unordered_map
{
	struct MapKeyOfKey
	{
		const K& operator()(const pair<K, V>& kv)
		{
			return kv.first;
		}
	};
public:
	typedef typename hash_bucket::HashTable<K, pair<const K, V>, Hash, MapKeyOfKey>::Iterator iterator;
	typedef typename hash_bucket::HashTable<K, pair<const K, V>, Hash, MapKeyOfKey>::Const_Iterator const_iterator;
	iterator begin()
	{
		return _ht.Begin();
	}
	iterator end()
	{
		return _ht.End();
	}
	const_iterator begin() const
	{
		return _ht.Begin();
	}
	const_iterator end() const
	{
		return _ht.End();
	}
	pair<iterator, bool> insert(const pair<K, V>& kv)
	{
		return _ht.Insert(kv);
	}
	bool erase(const K& key)
	{
		return _ht.Erase(key);
	}
	iterator find(const K& key)
	{
		return _ht.Find(key);
	}
	V& operator[](const K& key)
	{
		pair<iterator, bool> ret= _ht.Insert({key,V()});
		return ret.first->second;
	}
private:
	hash_bucket::HashTable<K, pair<const K, V>, Hash, MapKeyOfKey> _ht;
};

void test_map1()
{
	unordered_map<string, string> dict;
	dict.insert({ "sort", "ÅÅĞò" });
	dict.insert({ "×Ö·û´®", "string" });

	dict.insert({ "sort", "ÅÅĞò" });
	dict.insert({ "left", "×ó±ß" });
	dict.insert({ "right", "ÓÒ±ß" });

	dict["left"] = "×ó±ß£¬Ê£Óà";
	dict["insert"] = "²åÈë";
	dict["string"];

	for (auto& kv : dict)
	{
		cout << kv.first << ":" << kv.second << endl;
	}
	cout << endl;

	unordered_map<string, string>::iterator it = dict.begin();
	while (it != dict.end())
	{
		// ²»ÄÜĞŞ¸Äfirst£¬¿ÉÒÔĞŞ¸Äsecond
		//it->first += 'x';
		it->second += 'x';
		cout << it->first << ":" << it->second << endl;
		++it;
	}
	cout << endl;
}
