#pragma once

#include<iostream>
#include<assert.h>
#include<stack>
using namespace std;


//����ȡ�з�
int GetMidOfThree(int* a,int begin,int end)
{
	//ע��������ȼ�����
	int mid=begin+((end-begin)>>1);
	if(a[begin]<a[mid])
	{
		if(a[mid] < a[end])  //3 4 5
			return mid;

		else if(a[mid] > a[end])  //3 5 4
			return end;
		else
			return begin;
	}
	else //a[begin]>a[mid]
	{
		if(a[mid]<a[end])    //4 3 5
			return begin;
		else if(a[mid]>a[end])        //4 3 2
			return mid;
		else 
			return end;
	}
}

//����ָ�뷨
int PartSort1(int* a,int begin,int end)
{
	int left=begin;
    int right=end;
	//������ȡ�з�����������Ż�������ÿ��ȡ��������С��
	int mid=GetMidOfThree(a,begin,end); 
	std::swap(a[mid],a[end]);
	int key=a[end];
	while(left < right)
	{
		while(left<right && a[left]<=key)
		{
			++left;
		}

		while(left<right && a[right]>=key)
		{
			--right;
		}
		if(left < right)
		{
			std::swap(a[left],a[right]);
		}
	}
	//left==right
	std::swap(a[left],a[end]);
	return left;
}

//�ڿӷ�
int PartSort2(int* a,int begin,int end)
{
	int left=begin;
	int right=end;
	int mid=GetMidOfThree(a,begin,end); 
	std::swap(a[mid],a[end]);
	int tmp=a[end];
	while(left < right)
	{
		while(left < right && a[left]<=tmp)
		{
			++left;
		}
		a[right]=a[left];   //����ұ�tmp��ģ��ұ��ұ���С��

		while(left <right && a[right]>=tmp)
		{
			--right;
		}
		a[left]=a[right];
	}
	//��ʱleft=right
	a[left]=tmp;
	return left;
}


//ǰ��ָ�뷨
int PartSort3(int* a,int begin,int end)
{
	int prev=begin-1;
	int cur=begin;
	int mid=GetMidOfThree(a,begin,end); 
	std::swap(a[mid],a[end]);
	int key=a[end];
	while(cur<end)
	{
		//ֻ��a[cur]<keyʱ��prev��������
		if(a[cur]<key)
		{
			++prev;
			if(prev!=cur)
				std::swap(a[cur],a[prev]);
		}
		++cur;
	}
	++prev;     
	std::swap(a[prev],a[end]);
	return prev;
}



void QuickSort(int* a,int begin,int end)
{
	assert(a);
	//int div=PartSort1(a,begin,end);
	//int div=PartSort2(a,begin,end);
	int div=PartSort3(a,begin,end);
	if(div-1 > begin)
		QuickSort(a,begin,div-1);

	if(div+1 < end)
		QuickSort(a,div+1,end);
}


//�ǵݹ��������
void QuickSortNonR(int* a,int begin,int end)
{
	stack<int> s;
	s.push(end);
	s.push(begin);
	while(!s.empty())
	{
		int left=s.top();
		s.pop();
		int right=s.top();
		s.pop();

		int div=PartSort2(a,left,right);
		if(left < div-1)
		{
			s.push(div-1);
			s.push(left);
		}
		if(div+1 < right)
		{
			s.push(right);
			s.push(div+1);
		}
	}
}