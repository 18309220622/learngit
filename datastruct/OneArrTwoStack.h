#pragma once
#include <iostream>
#include<assert.h>
using namespace std;

template<class T>  
class TwoStack  
{  
public:  
	TwoStack()  
		:_top1(0)  
		,_top2(0)  
		,_capacity(0)  
		,_arr(NULL)  
	{  
		CheckCapacity();  
	}  

	~TwoStack()  
	{  
		if(NULL!=_arr)  
		{  
			delete[] _arr;  
		}  
	}  
	void Push1(const T& d)  
	{  
		CheckCapacity();  
		_arr[_top1++]=d;  
	}  
	void Push2(const T& d)  
	{  
		CheckCapacity();  
		_arr[_top2--]=d;  
	}  
	void Pop1()  
	{  
		assert(_top1>0);  
		_top1--;  
	}  
	void Pop2()  
	{  
		assert(_top2<_capacity-1);  
		_top2++;  
	}  
	size_t Size1()  
	{  
		return _top1;  
	}  
	size_t Size2()  
	{  
		return _capacity-1-_top2;  
	}  
	bool Empty1()  
	{  
		return _top1==0;  
	}  
	bool Empty2()  
	{  
		return _top2==_capacity-1;  
	}  
	T& Top1()  
	{  
		assert(_top1>0);  
		return _arr[_top1-1];  
	}  
	T& Top2()  
	{  
		assert(_top2<_capacity-1);  
		return _arr[_top2+1];  
	}  
protected:  

	void CheckCapacity()  
	{  
		if(NULL==_arr)  
		{  
			_capacity += 2;  
			_arr=new T[_capacity];  
			_top2=_capacity-1;  
			return ;  
		}  
		if(_top1==_top2)  
		{  
			size_t newCapacity=_capacity*2+2;  
			T* tmp=new T[newCapacity];  
			for(size_t i=0;i<_top1;++i)  
			{  
				tmp[i]=_arr[i];  
			}  
			size_t j=newCapacity-1;  
			for(size_t k=_capacity-1;k>_top2;--k)  
			{  
				tmp[j]=_arr[k];  
				--j;  
			}  

			_top2=newCapacity-(_capacity-_top2);  
			_capacity=newCapacity;  
			_arr=tmp;     
		}  
	}  
private:  
	T* _arr;  
	size_t _top1;  
	size_t _top2;  
	size_t _capacity;  

};  
