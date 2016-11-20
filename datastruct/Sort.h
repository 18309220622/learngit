#pragma once

#include<iostream>
#include<assert.h>
using namespace std;

void BubbleSort(int* arr,size_t sz)
{
	assert(arr);
	for(int i=0;i<sz-1;++i)   //控制趟数
	{
		int flag=true;       //作为标志位
		for(int j=0;j<sz-i-1;++j)  //控制每趟需要比较的次数
		{
			if(arr[j]>arr[j+1])
			{
				std::swap(arr[j],arr[j+1]);
				flag=false;
				/*int tmp=arr[j];
				arr[j]=arr[j+1];
				arr[j+1]=tmp;*/
			}
		}
		if(flag)
			break;
	}
}

void InsertSort(int* arr,size_t sz)
{
	assert(arr);
	for(int index=1;index<sz;++index)  //先默认下标为0的元素有序
	{
		int pos=index-1;
		int tmp=arr[index];
		while(pos>=0 && tmp < arr[pos])
		{
			std::swap(arr[pos],arr[pos+1]);
			--pos;
		}
		arr[pos+1]=tmp;
	}
}

void ShellSort(int* arr,size_t sz)
{
	assert(arr);
	int gap=sz;
	while(gap > 1)  
	{
		gap=gap/3 +1;   

		for(int index=gap;index<sz;++index)  //先默认下标为0的元素有序
	    {
			int pos=index-gap;
			int tmp=arr[index];
			while(pos>=0 && tmp < arr[pos])
			{
				std::swap(arr[pos],arr[pos+gap]);
				pos-=gap;
			}
			arr[pos+gap]=tmp;
	    }
	}
}

void SelectSort(int* arr,size_t sz)
{
	assert(arr);
	int i=0;
	int min=0;
	for(i=0;i<sz;++i)
	{
		min=i;     //将当前下标定义为最小下标
		for(int j=i+1;j<sz;++j)  //从后面的数据选择小的
		{
			if(arr[j]<arr[min])
				min=j;
		}
		if(min!=i)
		{
			std::swap(arr[i],arr[min]);
		}
	}
}


void AdjustDown(int *a, size_t root, size_t size)  
{   
    size_t parent = root;  
    size_t child = parent * 2 + 1;  //先指向左孩子
    while (child < size)  
    {  
        if (child + 1 < size && a[child] < a[child + 1])  
        {  
            ++child;  
        }  
        if (a[parent] < a[child])  
        {  
            std::swap(a[parent], a[child]);  
            parent = child;  
            child = parent*2 + 1;  
        }  
        else  
        {  
            break;  
        }  
    }  
}  
void HeapSort(int *arr,int sz)
{
	assert(arr);
	//升序建大堆
	for(int i=(sz-2)/2;i>=0;--i)   //从倒数第一个非叶子节点开始向下调整
	{
		AdjustDown(arr,i,sz);
	}

	for (size_t i=0;i<sz;++i)      
    {  
        std::swap(arr[0],arr[sz-1-i]);   
        AdjustDown(arr,0,sz-1-i);  
    }  
}





