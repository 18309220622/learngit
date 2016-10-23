#pragma once

#include<iostream>
#include<assert.h>
#include<stack>
using namespace  std;

template<class T>  
bool CheckStackLeg(const T* sPush,const T* sPop,size_t szin,size_t szout)  
{  
	assert(sPush && sPop);   //防止输入两个空指针  
	assert(szin && szout);   //防止大小传入0，导致程序错误  
	if(szin!=szout)  
	{  
		return false;  
	}  
	stack<int> s;  
	size_t i=0;  
	size_t j=0;  
	for (i=0;i<szin;++i)  
	{  
		s.push(sPush[i]);  
		while(j<szout)  
		{  
			if (!s.empty()&&s.top()==sPop[j])  
			{  
				s.pop();  
				j++;  
			}  
			else  
			{  
				break;    //不满足if条件就直接跳出  
			}  
		}  
	}  
	if (!s.empty())  
	{  
		return false;  
	}  
	return true;  
}  
