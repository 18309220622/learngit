#include"binarytree.h"

void test()
{
	int a[10]={1,2,3,'#','#',4,'#','#',5,6};
	BinaryTree<int> b1(a,10,'#');

	cout<<"前序：";
	b1.PrevOrder();
	cout<<endl;
	cout<<"中序：";
	b1.InOrder();
	cout<<endl;
	cout<<"后序：";
    b1.PostOrder();
	cout<<endl;
	cout<<"层序：";
	b1.LevelOrder();
	cout<<endl;

	cout<<"非递归前序：";
	b1.PrevOrder_NonR();
	cout<<endl;

	cout<<"非递归中序：";
	b1.InOrder_NonR();
	cout<<endl;

	cout<<"非递归后序：";
	b1.PostOrder_NonR();
	cout<<endl;


	cout<<"b1.Size:"<<b1.Size()<<endl;
	cout<<"b1.Depth:"<<b1.Depth()<<endl;
	cout<<"b1.LeafSize:"<<b1.LeafSize()<<endl;
	cout<<"b1.GetKLevel:"<<b1.GetKLevel(2)<<endl;

	

	BinaryTree<int> b2(b1);
	cout<<"调拷贝构造，前序遍历：";
	b2.PrevOrder();
	cout<<endl;

	BinaryTree<int> b3;
	b3=b1;
	cout<<"调赋值操作，前序遍历：";
	b3.PrevOrder();
	cout<<endl;
	cout<<"调赋值操作，中序遍历：";
	b3.InOrder();
	cout<<endl;       

}

void test1()
{
	int a[10]={1,2,3,'#','#',4,'#','#',5,6};
	BinaryTree<int> b1(a,10,'#');

	BinaryTreeNode<int> *ret=b1.FindNode(6);
	assert(ret);
	cout<<"FindNode6:"<<ret->_data<<endl;    
	ret=b1.FindNode(8);
	cout<<"FindeNode8:"<<ret<<endl;   //找不到输出地址00000000
}
int main()
{
	test();
	test1();
	system("pause");
	return 0;
}