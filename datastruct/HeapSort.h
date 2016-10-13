#pragma once

#include<iostream>
#include<assert.h>
using namespace std;

template<class T>
struct UpOrder             //Set up MaxHeap
{
	bool operator()(const T& l,const T& r)
	{
		return l<r;
	}
};

template<class T>
struct DownOrder          //Set up MinHeap
{
	bool operator()(const T& l,const T& r)
	{
		return l>r;
	}
};

template<class T,class compare=UpOrder<T>>
class HeapSort
{
public:
	void Sort(T* a,size_t size)
	{
		assert(a);
		for (int i=((int)size-2)/2;i>=0;--i)
		{
			AdjustDown(a,i,size);
		}
		for(size_t i=0;i<size;++i)
		{
			std::swap(a[0],a[size-1-i]);
			AdjustDown(a,0,size-1-i);
		}
	}
protected:
	void AdjustDown(T*a,size_t root,size_t size)
	{
		assert(a);
		compare com;
		size_t parent=root;
		size_t child=parent*2+1;
		while(child<size)
		{
			if (child+1 <size && com(a[child],a[child+1]))
			{
				++child;
			}
			if(com(a[parent],a[child]))
			{
				std::swap(a[parent],a[child]);
				parent=child;
				child=parent*2+1;
			}
			else
			{
				break;
			}
		}
	}
};

