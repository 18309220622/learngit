#include"HeapSort.h"

void Test1()
{
	HeapSort<int> h;   
	int a[] = {10,11,13,12,16,18,15,17,14,19};
	int sz=sizeof(a)/sizeof(a[0]);
	h.Sort(a,sz);
	for (int i=0;i<sz;++i)
	{
		cout<<a[i]<<" ";
	}
	cout<<endl;
}

void Test2()
{
	HeapSort<int,DownOrder<int>> h1;
	int a[] = {10,11,13,12,16,18,15,17,14,19};
	int sz=sizeof(a)/sizeof(a[0]);
	h1.Sort(a,sz);
	for (int i=0;i<sz;++i)
	{
		cout<<a[i]<<" ";
	}
	cout<<endl;
}
int main()
{
	Test1();
	Test2();
	system("pause");
	return 0;
}