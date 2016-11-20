#pragma once

#include<iostream>
#include<assert.h>
using namespace std;

void BubbleSort(int* arr,size_t sz)
{
	assert(arr);
	for(int i=0;i<sz-1;++i)   //��������
	{
		int flag=true;       //��Ϊ��־λ
		for(int j=0;j<sz-i-1;++j)  //����ÿ����Ҫ�ȽϵĴ���
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
	for(int index=1;index<sz;++index)  //��Ĭ���±�Ϊ0��Ԫ������
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

		for(int index=gap;index<sz;++index)  //��Ĭ���±�Ϊ0��Ԫ������
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
		min=i;     //����ǰ�±궨��Ϊ��С�±�
		for(int j=i+1;j<sz;++j)  //�Ӻ��������ѡ��С��
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
    size_t child = parent * 2 + 1;  //��ָ������
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
	//���򽨴��
	for(int i=(sz-2)/2;i>=0;--i)   //�ӵ�����һ����Ҷ�ӽڵ㿪ʼ���µ���
	{
		AdjustDown(arr,i,sz);
	}

	for (size_t i=0;i<sz;++i)      
    {  
        std::swap(arr[0],arr[sz-1-i]);   
        AdjustDown(arr,0,sz-1-i);  
    }  
}





