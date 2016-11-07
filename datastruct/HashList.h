#pragma once 

#include<iostream>
#include<vector>
#include<string>
using namespace std;


template<class K>
struct GetKType
{
	size_t operator()(const K& key)
	{
		return key;
	}
};

template<>
struct GetKType<string>      //模板的特化
{
	//字符串哈希算法(将字符串转为整型)
	static size_t BKDRHash(const char* str)  //BKDRHash算法
	{
		unsigned int seed= 131;// 31 131 1313 13131 131313
		unsigned int hash= 0;
		while(*str)
		{
			hash=hash*seed+(*str++);
		}
		return(hash& 0x7FFFFFFF);	}

	size_t operator()(const string& str)
	{
		return BKDRHash(str.c_str());
	}
};

template<class K,class V>
struct HashListNode
{
	HashListNode<K,V>* _next;
	K _key;
	V _value;

	HashListNode(const K& key,const V& value)
		:_key(key)
		,_value(value)
		,_next(NULL)
	{}
};

template<class K,class V,class HashFunc=GetKType<K> >
class HashList
{
	typedef HashListNode<K,V> Node;
public:
	HashList()
		:_size(0)
	{
		_tables.resize(_GetNextPrime(0));
	}

	~HashList()
	{
		if(_tables.empty())
			return;

		for(size_t i=0;i<_tables.size();++i)
		{
			Node* cur=_tables[i];
			while(cur)
			{
				Node* tmp=cur;
				cur=cur->_next;
				delete tmp;
				tmp=NULL;
			}
		}
		_size=0;
		_tables.clear();
	}

	bool Insert(const K& key,const V& value)
	{
		_CheckSize();
		size_t index=_HashFunc(key,_tables.size());
		//先检查该元素是否已在表中了
		Node* cur=_tables[index];
		while(cur)
		{
			if(cur->_key==key)
				return false;

			cur=cur->_next;
		}

		//采取头插
		Node* NewNode=new Node(key,value);
		NewNode->_next=_tables[index];
		_tables[index]=NewNode;

		++_size;
	}

	bool Find(const K& key)
	{
		size_t index=_HashFunc(key,_tables.size());
		Node* cur=_tables[index];    //先定位到在表中哪个位置
		while(cur)
		{
			if(cur->_key==key)
				return true;

			else
				cur=cur->_next;
		}
		return false;
	}

	bool Remove(const K& key)
	{
		if(_tables.empty())
			return false;

		size_t index=_HashFunc(key,_tables.size());
		Node* cur=_tables[index];
		Node* prev=NULL;
		while(cur)
		{
			//1.删除头结点
			//2.删除中间节点及尾节点
			if(cur->_key==key)
			{
				if(prev==NULL)
				{
					_tables[index]=cur->_next;
				}
				else
				{
					prev->_next=cur->_next;
				}
				delete cur;
				cur=NULL;
				--_size;
				return true;
			}
			prev=cur;
			cur=cur->_next;
		}
		return false;
	}


	void Print()
    {
        if (_size == 0)
            return;

        for (size_t i = 0; i < _tables.size(); ++i)
        {
            Node* cur = _tables[i];
            //cout << "_tables[" << i << "]" << "->";
			printf("_tables[%d]:",i);
            while (cur)
            {
                cout << cur->_key << "->";
                cur = cur->_next;
            }
            cout << "NULL" << endl;
        }
    }

protected:
	void _Swap(HashList<K,V,HashFunc>& hl)
	{
		std::swap(hl._tables,_tables);
		std::swap(hl._size,_size);
	}

	size_t _HashFunc(const K& key,size_t size)
	{
		HashFunc hf;
		return hf(key)%size;
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
	
	void _CheckSize()
	{
		if(_size >= _tables.size())      //负载因子为1就开始扩容
		{
			size_t NewSize=_GetNextPrime(_tables.size());
			//通过原表中的数据算出在新表中的位置
			vector<Node*> newTables;      //出了这个作用域就销毁
			newTables.resize(NewSize);
			for(size_t i=0;i<_tables.size();++i)
			{
				Node* cur=_tables[i];
				while(cur)
				{
					Node* tmp=cur->_next;
					cur=cur->_next;
					size_t index=_HashFunc(tmp->_key,newTables.size());
					newTables[index]=tmp;   	
				}
			}
			_tables.swap(newTables);
		}
	}

protected:
	vector<Node*> _tables;
	size_t _size;
};