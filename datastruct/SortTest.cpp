#include"Sort.h"

void BubbleTest()
{
	int arr[]={9,1,5,8,3,7,4,6,2};
	int sz=sizeof(arr)/sizeof(arr[0]);
	//BubbleSort(arr,sz);
	//InsertSort(arr,sz);
	//ShellSort(arr,sz);
	//SelectSort(arr,sz);
	HeapSort(arr,sz);
	for(int i=0;i<sz;++i)
	{
		cout<<arr[i]<<" ";
	}
	cout<<endl;
}
int main()
{
	BubbleTest();
	system("pause");
	return 0;
}