#include"binarytree.h"

void test()
{
	int a[10]={1,2,3,'#','#',4,'#','#',5,6};
	BinaryTree<int> b1(a,10,'#');

	cout<<"ǰ��";
	b1.PrevOrder();
	cout<<endl;
	cout<<"����";
	b1.InOrder();
	cout<<endl;
	cout<<"����";
    b1.PostOrder();
	cout<<endl;
	cout<<"����";
	b1.LevelOrder();
	cout<<endl;

	cout<<"�ǵݹ�ǰ��";
	b1.PrevOrder_NonR();
	cout<<endl;

	cout<<"�ǵݹ�����";
	b1.InOrder_NonR();
	cout<<endl;

	cout<<"�ǵݹ����";
	b1.PostOrder_NonR();
	cout<<endl;


	cout<<"b1.Size:"<<b1.Size()<<endl;
	cout<<"b1.Depth:"<<b1.Depth()<<endl;
	cout<<"b1.LeafSize:"<<b1.LeafSize()<<endl;
	cout<<"b1.GetKLevel:"<<b1.GetKLevel(2)<<endl;

	

	BinaryTree<int> b2(b1);
	cout<<"���������죬ǰ�������";
	b2.PrevOrder();
	cout<<endl;

	BinaryTree<int> b3;
	b3=b1;
	cout<<"����ֵ������ǰ�������";
	b3.PrevOrder();
	cout<<endl;
	cout<<"����ֵ���������������";
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
	cout<<"FindeNode8:"<<ret<<endl;   //�Ҳ��������ַ00000000
}
int main()
{
	test();
	test1();
	system("pause");
	return 0;
}