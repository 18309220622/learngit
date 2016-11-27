#include<iostream>
#include<assert.h>
using namespace std;


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
void _MergeSort(int* a,int* tmp,int left,int right)
{
	if(left >= right)
		return;

	int mid=left+((right-left)>>1);
	int begin1=left,end1=mid;
	int begin2=mid+1,end2=right;

	if(left < mid)      //left=midʱ������Ԫ�ز����зָ�
	{
		if(right-left >13)
			_MergeSort(a,tmp,left,mid);
		else
			InsertSort(a+left,right-left+1);
	}
		
	if(mid+1 < right)     
	{ 
		if(right-mid-1 >13)
			_MergeSort(a,tmp,right,mid);
		else
			InsertSort(a+mid+1,right-mid);   //[mid+1,right]����Ԫ�ظ���Ϊright-mid
	}

	int index=left;
	//���й鲢
	while(begin1 <= end1 && begin2 <= end2)
	{
		if(a[begin1] < a[begin2])
			tmp[index++]=a[begin1++];

		else
			tmp[index++]=a[begin2++];
	}

	while(begin1 <= end1)   //һ��Ϊ�գ�һ�β�Ϊ�յ������������
	{
		tmp[index++]=a[begin1++];
	}

	while(begin2 <= end2)  
	{
		tmp[index++]=a[begin2++];
	}

	for(int i=left;i<=right;++i)
	{
		a[i]=tmp[i];
	}
}
void MergeSort(int* a,int begin,int end)
{
	assert(a);
	int* tmp=new int[end-begin+1];
	assert(tmp);
	_MergeSort(a,tmp,begin,end);
	delete[] tmp;
}

