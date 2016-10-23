#include "OneArrTwoStack.h"

void test()  
{  
	TwoStack<int> s;  
	for(size_t i=0;i<4;++i)  
	{  
		s.Push1(i);  
	}  
	for(size_t i=4;i<8;++i)  
	{  
		s.Push2(i);  
	}  
	cout<<"s1:"<<s.Size1()<<endl;  
	cout<<"s2:"<<s.Size2()<<endl;  
	cout<<"Õ»1£º";  
	while(!s.Empty1())  
	{  
		cout<<s.Top1()<<" ";  
		s.Pop1();  
	}  
	cout<<endl;  
	cout<<"Õ»2£º";  
	while(!s.Empty2())  
	{  
		cout<<s.Top2()<<" ";  
		s.Pop2();  
	}
	cout<<endl;
} 

void test1()  
{  
	TwoStack<int> s;  
	for(size_t i=0;i<6;++i)  
	{  
		s.Push1(i);  
	}  
	cout<<"s1:"<<s.Size1()<<endl;  
	cout<<"s2:"<<s.Size2()<<endl;  
	cout<<"Õ»1£º";  
	while(!s.Empty1())  
	{  
		cout<<s.Top1()<<" ";  
		s.Pop1();  
	}
	cout<<endl;
}  

void test2()  
{  
	TwoStack<int> s;  
	for(size_t i=0;i<6;++i)  
	{  
		s.Push2(i);  
	}  
	cout<<"s1:"<<s.Size1()<<endl;  
	cout<<"s2:"<<s.Size2()<<endl;  
	cout<<"Õ»2£º";  
	while(!s.Empty2())  
	{  
		cout<<s.Top2()<<" ";  
		s.Pop2();  
	}  
}

int main()
{
	test();
	test1();
	test2();
	system("pause");
	return 0;
}