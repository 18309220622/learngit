#include"DoubleStack_Queue.h"

void test()  
{  
	DoubleStack_Queue<int> q1;  
	for(size_t i=0;i<4;++i)  
	{  
		q1.Push(i);  
	}                           //0 1 2 3   
	cout<<"Queue Size1:"<<q1.Size()<<endl;  
	cout<<"Queue Front1:"<<q1.Front()<<endl;  
	cout<<"Queue Back1:"<<q1.Back()<<endl;  

	for(size_t i=4;i<6;++i)  
	{  
		q1.Push(i);  
	}   
	cout<<"增加元素4 5后："<<endl;  
	cout<<"Queue Size2:"<<q1.Size()<<endl;  
	cout<<"Queue Front2:"<<q1.Front()<<endl;  
	cout<<"Queue Back2:"<<q1.Back()<<endl;  
	while(!q1.Empty())  
	{  
		cout<<q1.Front()<<" ";  
		q1.Pop();                 
	}  
}  

int main()
{
	test();
	system("pause");
	return 0;
}