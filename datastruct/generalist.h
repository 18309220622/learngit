#pragma once

#include<iostream>
#include<assert.h>
using namespace std;

enum Type
{
	HEAD_TYPE,      
	VALUE_TYPE,     
	SUB_TYPE       
};

struct GeneralistNode
{
	GeneralistNode(const char& value='0',const Type& type=HEAD_TYPE)
		:_type(type)
		,_next(NULL)
		/*,_value(value)*/
		,_pSub(NULL)
	{}

	Type _type;
	GeneralistNode* _next; 
	union               
	{
		char _value;   
		GeneralistNode* _pSub;    
	};
};

class Generalist
{
public:
	Generalist()
		:_head(NULL)
	{}
	Generalist(char* str)
	{
		_head=_CreateList(str);
	}
	Generalist(const Generalist& g)
	{
		_head=_CopyList(g._head);
	}
	/*Generalist& operator=(Generalist g)
	{
		std::swap(_head,g._head);
		return *this;
	}*/
	/*Generalist& operator=(const Generalist& g)
	{
		if(this!=&g)
		{
			GeneralistNode* tmp=_CopyList(g._head);
			_DelGeneralist(_head);
			_head=tmp;
		}
		return *this;
	}*/
	Generalist& operator=(const Generalist& g)
	{
		if(this!=&g)
		{
			GeneralistNode* tmp;
			std::swap(_head,tmp._head);
		}
		return *this;
	}
	~Generalist()
	{
		_DelGeneralist(_head);
		_head = NULL;
	}

	size_t Size()
	{
		return _Size(_head);
	}

	size_t Depth()
	{
		return _Depth(_head);
	}
	void Print()
	{
		return _Print(_head);
	}
protected:
	void _Print(GeneralistNode* head)
	{
		if(NULL==head)
		{
			return ;
		}
		GeneralistNode* cur=head;
		while(cur)
		{
			if(cur->_type==VALUE_TYPE)
			{
				cout<<cur->_value;
				if(cur->_next!=NULL)
				{
					cout<<',';
				}
				cur=cur->_next;
			}
			else if(cur->_type==SUB_TYPE)
			{
				_Print(cur->_pSub);
				if(cur->_next!=NULL)
				{
					cout<<',';
				}
				cur=cur->_next;
			}
			else
			{
				cout<<'(';
				cur=cur->_next;
			}
		}
		cout<<')';
	}
	size_t _Depth(GeneralistNode* head) 
	{
		int maxdepth=1;
		int curdepth=1;
		GeneralistNode* cur=head;
		while(cur)
		{
			if(cur->_type==SUB_TYPE)
			{
				curdepth+=_Depth(cur->_pSub);
				if(curdepth>maxdepth)  
				{
					maxdepth=curdepth;
				}
				curdepth=1;
			}
			cur=cur->_next;
		}
		return maxdepth;
	}

	size_t _Size(GeneralistNode* head)
	{
		size_t count=0;
		GeneralistNode* cur=head;
		while(cur)
		{
			if(cur->_type==VALUE_TYPE)
			{
				++count;
			}
			else if(cur->_type==SUB_TYPE)
			{
				count+=_Size(cur->_pSub);
			}
			cur=cur->_next;
		}
		return count;
	}


	void _DelGeneralist(GeneralistNode* head)
	{
		if(NULL==head)
		{
			return ;
		}
		GeneralistNode* cur=head;
		GeneralistNode* del=head;
		while(cur)
		{
			del=cur;
			/*if(cur->_type==VALUE_TYPE)
			{
				delete del;
			}*/
			if(cur->_type==SUB_TYPE)
			{
				_DelGeneralist(cur->_pSub);
			}
			cur=cur->_next;
			delete del;
		}

	}
	GeneralistNode* _CopyList(GeneralistNode* head)
	{
		GeneralistNode* pHead=new GeneralistNode(HEAD_TYPE);
		GeneralistNode* cur=head;
		GeneralistNode* pcur=pHead;
		while(cur)
		{
			if(cur->_type==VALUE_TYPE)
			{
				pcur->_next=new GeneralistNode(cur->_value,VALUE_TYPE);
				pcur=pcur->_next;
				pcur->_value=cur->_value;
				cur=cur->_next;
			}
			else if(cur->_type==SUB_TYPE)
			{
				pcur->_next=new GeneralistNode(SUB_TYPE);
				pcur=pcur->_next;
				pcur->_type=cur->_type;            
				pcur->_pSub=_CopyList(cur->_pSub);    
				cur=cur->_next;
			}
			else
			{
				cur=cur->_next;
			}
		}
		return pHead;
	}

	GeneralistNode* _CreateList(char* &str)
	{
		assert(*str=='(');
		++str;
		GeneralistNode* head= new GeneralistNode(HEAD_TYPE);
		GeneralistNode* cur=head;
		while(*str)
		{
			if(IsLegalValue(*str)) 
			{
				cur->_next=new GeneralistNode(*str,VALUE_TYPE);
				cur=cur->_next;
				cur->_value=*str;
				++str;
				cur->_type=VALUE_TYPE;
			}
			else if(*str=='(') 
			{
				cur->_next=new GeneralistNode(SUB_TYPE);
				cur=cur->_next;
				cur->_pSub=_CreateList(str);  
				++str;
				cur->_type=SUB_TYPE;
			}
			else if(*str==')') 
			{
				++str;
				return head;  
			}
			else  
			{
				++str;
			}
		}
		return head;
	}

	bool IsLegalValue(char str)
	{
		if((str >= '0'&& str <= '9') ||(str>='a'&& str<='z')||(str>='A'&&str<='Z'))
		{
			return true;
		}
		else
		{
			return false;
		}
	}
private:
	GeneralistNode* _head;
};