#pragma once

#include<iostream>
#include<vector>
using namespace std;

enum Status
{
	EXIST,
	DELETE,
	EMPTY
};

template<class K,class V>
struct HashTableNode
{
	K _key;
	V _value;
	Status _status;

	HashTableNode(const K& key=K(),const V& value=V())
		:_key(key)
		,_value(value)
		,_status(EMPTY)
	{}
};

template<class K,class V>
class HashTable
{
	typedef HashTableNode<K,V> Node;
public:
	HashTable()
		:_size(0)
	{
		_tables.resize(_GetNextPrime(0));
	}

	~HashTable()
	{
		for(size_t i=0;i<_tables.size();++i)
		{
			if(_tables[i]._status!=EMPTY)
			{
				_tables[i]._key=0;
				_tables[i]._value=0;
				_tables[i]._status=EMPTY;
			}
		}
	}

	bool Insert(const K& key,const V& value)
	{
		_CheckSize();
		size_t index=_Func(key);
		while(_tables[index]._status==EXIST)
		{
			if(_tables[index]._key==key)
				return false;

			++index;
			if(index==_tables.size())
				index=0;
		}
		
		_tables[index]._key=key;
		_tables[index]._value=value;
		_tables[index]._status=EXIST;
		++index;
		return true;
	}

	void Print()
	{
		if(!_tables.empty())
		{
			for(size_t i=0;i<_tables.size();++i)
			{
				cout<<_tables[i]._key<<" ";
			}
			cout<<endl;
		}
	}

	Node* Find(const K& key)
	{
		size_t index=_Func(key);
		size_t src=index;
		while(_tables[index]._status!=EMPTY)   //有些可能是删除的，要跳过继续查询
		{
			if(_tables[index]._key == key && _tables[index]._status!=DELETE)
				return &_tables[index];
			else
			{
				++index;
				if(index==src)
			      break;        //找了一圈还没找到就跳出去
			}
		}
		return NULL;
	}

	bool Remove(const K& key)
	{
		Node* ret=Find(key);
		if(NULL==ret)
			return false;
		//懒删除法
		ret->_status=DELETE;
	}
protected:
	size_t _Func(const K& key)
	{
		return key%_tables.size();
	}

	size_t _GetNextPrime(size_t num)
	{
		const int _PrimeSize= 28;
        static const unsigned long _PrimeList[_PrimeSize] =
        {
			53ul, 97ul, 193ul, 389ul, 769ul,
			1543ul, 3079ul, 6151ul, 12289ul, 24593ul,
			49157ul, 98317ul, 196613ul, 393241ul,
			786433ul,
			1572869ul, 3145739ul, 6291469ul, 12582917ul,
			25165843ul,
			50331653ul, 100663319ul, 201326611ul, 402653189ul,
			805306457ul,
			1610612741ul, 3221225473ul, 4294967291ul
       };		for(size_t i=0;i<_PrimeSize;++i)		{			if(num < _PrimeList[i])			{				return _PrimeList[i];			}			return _PrimeList[i-1];		}
		return _PrimeList[_PrimeSize-1];   //如果size大于或等于素数表中数据，就返回表中最大数  
	}
	
	//当哈希表size=0或超过负载因子的要求时就该扩容
	void _CheckSize()
	{
		if(_tables.size()==0 || _size*10 / _tables.size()>=8)
		{
			size_t NewSize=_GetNextPrime(_tables.size());
			HashTable<K,V> h;
			h._tables.resize(NewSize);
			for(size_t i=0;i<_tables.size();++i)
			{
				if(_tables[i]._status==EXIST)
					h.Insert(_tables[i]._key,_tables[i]._value);
			}
			this->_Swap(h);  //通过临时对象出作用域自动析构的特性
		}
	}

	void _Swap(HashTable<K,V>& h)
	{
		_tables.swap(h._tables);
        swap(_size,h._size);
	}
protected:
	vector<Node> _tables;
	size_t _size;
};