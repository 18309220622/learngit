#include"RBTree.h"

void test()
{
	RBTree<int,int> RB;
	int arr[]={16, 3, 7, 11, 9, 26, 18, 14, 15};
	size_t sz=sizeof(arr)/sizeof(arr[0]);
	for (size_t i=0;i<sz;++i)
	{
		RB.Insert(arr[i],i);
	}
	RB.InOrder();
	cout<<"Find(15):"<<RB.Find(15)<<endl;
	cout<<"IsRBTree?"<<RB.IsRBTree();
}
int main()
{
	test();
	system("pause");
	return 0;
}