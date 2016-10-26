#include"AVLTree.h"

void test()
{
	AVLTree<int,int> at;
	//int arr[]={16, 3, 7, 11, 9, 26, 18, 14, 15};
	int arr[]={4, 2, 6, 1, 3, 5, 15, 7, 16, 14};
	for (size_t i=0;i<9;++i)
	{
		at.Insert(arr[i],i);
	}
	at.InOrder();
	//cout<<"balance or unbalance?"<<at.Isbalance()<<endl;
	cout<<"balance or unbalance?"<<at.IsbalanceOP()<<endl;

}
int main()
{
	test();
	system("pause");
	return 0;
}