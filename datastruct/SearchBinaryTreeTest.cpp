#include "SearchBinaryTree.h"

void test1()
{
	int arr[10] = {5,2,4,6,9,0,3,7,8,1};
	size_t sz=sizeof(arr)/sizeof(arr[0]);
	SearchBinaryTree<int> t(arr,sz);
	t.InOrder();

	SearchBinaryTree<int> t1;
	t1=t;
	t1.InOrder();

	SearchBinaryTree<int> t2(t);
	t2.InOrder();

	cout<<"Find(7):"<<t.Find(7)<<endl;
	cout<<"Find(13):"<<t.Find(13)<<endl;

	t.Insert(10);
	t.Insert(11);
	t.InOrder();

	t.Remove(0);
	t.Remove(1);
	t.Remove(2);
	t.Remove(3);
	t.Remove(4);
	t.Remove(5);
	t.Remove(6);
	t.Remove(7);
	t.Remove(8);
	t.Remove(9);
	t.InOrder();
}

void test2()
{
	int arr[10] = {5,2,4,6,9,0,3,7,8,1};
	size_t sz=sizeof(arr)/sizeof(arr[0]);
	SearchBinaryTree<int> t(arr,sz);

	SearchBinaryTree<int> t1(t);
	t1.InOrder();

	SearchBinaryTree<int> t2;
	t2=t;
	t2.InOrder();
	
	t.InsertR(10);
	t.InsertR(12);
	t.InOrder();

	cout<<"FindR(5):"<<t.FindR(5)<<endl;
	cout<<"FindR(11):"<<t.FindR(11)<<endl;

	t.RemoveR(0);
	t.RemoveR(1);
	t.RemoveR(2);
	t.RemoveR(3);
	t.RemoveR(4);
	t.RemoveR(5);
	t.RemoveR(6);
	t.RemoveR(7);
	t.RemoveR(8);
	t.RemoveR(9);
	t.InOrder();

}
int main()
{
	//test1();
	test2();
	system("pause");
	return 0;
}
