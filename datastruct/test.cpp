#include<iostream>
#include<queue>
#include<assert.h>
using namespace std;

template<class T>
class DoubleQueue_Stack
{
public:
	void Push(const T& d);
	void Pop();
	bool Empty();
	size_t Size();
	T& Top();
private:
	queue<T> q1;
	queue<T> q2;
};

template<class T>
void DoubleQueue_Stack<T>::Push(const T& d)
{
	if(!q1.empty())
	{
		q1.push(d);
	}
	else
	{
		q2.push(d);
	}
}

template<class T>
void DoubleQueue_Stack<T>::Pop()
{

	assert(!q1.empty()||!q2.empty());
	if(!q1.empty())
	{
		while (q1.size()>1)
		{
			q2.push(q1.front());
			q1.pop();
		}
		q1.pop();
	}
	else if(!q2.empty())
	{
		while (q2.size()>1)
		{
			q1.push(q2.front());
			q2.pop();
		}
		q2.pop();
	}
}

template<class T>
bool DoubleQueue_Stack<T>::Empty()
{
	return q1.empty()&&q2.empty();
}

template<class T>
size_t DoubleQueue_Stack<T>::Size()
{
	if (!q1.empty())
	{
		return q1.size();
	}
	return q2.size();
}

template<class T>
T& DoubleQueue_Stack<T>::Top()
{
	assert(!q1.empty()|| !q2.empty());
	if(!q1.empty())
	{
		return q1.back();
	}
	if(!q2.empty())
	{
		return q2.back();
	}
}
void test()
{
	DoubleQueue_Stack<int> s;
	for(size_t i=0;i<4;++i)
	{
		s.Push(i);
	}
	cout<<s.Size()<<endl;
	while(!s.Empty())
	{
		cout<<s.Top()<<" ";
		s.Pop();
	}
	cout<<endl;
}
int main()
{
	test();
	system("pause");
	return 0;
}