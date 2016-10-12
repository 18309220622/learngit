#include"Heap.h"

void Test1()
{
	int a[] = {10,11,13,12,16,18,15,17,14,19};
	Heap<int> hp(a,sizeof(a)/sizeof(a[0]));
	hp.Print();
	
	cout<<"Empty> "<<hp.Empty()<<endl;
	cout<<"Size> "<<hp.Size()<<endl;
	cout<<"Top> "<<hp.Top()<<endl;

	hp.Push(20);
	hp.Print();
	hp.Pop();
	hp.Print();
}

int main()
{
	Test1();
	system("pause");
	return 0;
}