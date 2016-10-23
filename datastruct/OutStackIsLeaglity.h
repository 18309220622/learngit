#pragma once

#include<iostream>
#include<assert.h>
#include<stack>
using namespace  std;

template<class T>  
bool CheckStackLeg(const T* sPush,const T* sPop,size_t szin,size_t szout)  
{  
	assert(sPush && sPop);   //��ֹ����������ָ��  
	assert(szin && szout);   //��ֹ��С����0�����³������  
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
				break;    //������if������ֱ������  
			}  
		}  
	}  
	if (!s.empty())  
	{  
		return false;  
	}  
	return true;  
}  
