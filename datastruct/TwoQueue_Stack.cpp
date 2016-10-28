#include"TwoQueue_Stack.h"

void test()
{
	DoubleQueue_Stack<int> s;
	for(size_t i=0;i<6;++i)
	{
		s.Push(i);
	}
	while(!s.Empty())
	{
		cout<<s.Top()<<" ";
		s.Pop();
	}
}
int main()
{
	test();
	system("pause");
	return 0;
}