#include"Quick.h"

void QSortTest()
{
	//int a[]={9,8,7,6,5,4,3,2,1,0};
	//int a[]={0,1,2,3,4,5,6,7,8,9};
	int a[]={2,0,4,9,3,6,8,7,1,5};
	QuickSort(a,0,9);
	//QuickSortNonR(a,0,9);
	for(size_t i=0;i<sizeof(a)/sizeof(a[0]);++i)
	{
		cout<<a[i]<<" ";
	}
}

int main()
{
	QSortTest();
	system("pause");
	return 0;
}