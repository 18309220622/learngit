#pragma once

#include<iostream>
#include<assert.h>
#include<stack>
using namespace std;


//三数取中法
int GetMidOfThree(int* a,int begin,int end)
{
	//注意符号优先级问题
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

//左右指针法
int PartSort1(int* a,int begin,int end)
{
	int left=begin;
    int right=end;
	//用三数取中法来对其进行优化，避免每次取得最大或最小数
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

//挖坑法
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
		a[right]=a[left];   //左边找比tmp大的，右边找比它小的

		while(left <right && a[right]>=tmp)
		{
			--right;
		}
		a[left]=a[right];
	}
	//此时left=right
	a[left]=tmp;
	return left;
}


//前后指针法
int PartSort3(int* a,int begin,int end)
{
	int prev=begin-1;
	int cur=begin;
	int mid=GetMidOfThree(a,begin,end); 
	std::swap(a[mid],a[end]);
	int key=a[end];
	while(cur<end)
	{
		//只有a[cur]<key时，prev才往后走
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


//非递归快速排序
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