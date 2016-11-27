#include"MergeSort.h"

void MergeTest()
{
	//int a[]={9,8,7,6,5,4,3,2,1,0};
	int a[]={6,8,7,1,5,4,2,3,1,2,11,65,43,22,21,45,14,6};
	MergeSort(a,0,17);
	int sz=sizeof(a)/sizeof(a[0]);
	for(int i=0;i<sz;++i)
	{
		cout<<a[i]<<" ";
	}
}
int main()
{
	MergeTest();
	system("pause");
	return 0;
}