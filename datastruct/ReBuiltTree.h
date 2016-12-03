#pragma once
#include<assert.h>
#include<iostream>
using namespace std;

//����ǰ������������ؽ�������
template<class T>
class RebuiltBinaryTree
{
	struct RebuiltBinaryTreeNode
	{
		T _data;
		RebuiltBinaryTreeNode* _left;
		RebuiltBinaryTreeNode* _right;

		RebuiltBinaryTreeNode(const T& data)
			:_data(data)
			,_left(NULL)
			,_right(NULL)
		{}
	};
	typedef RebuiltBinaryTreeNode Node;
public:
	RebuiltBinaryTree (T* PrevOrder,T* InOrder,int len)
	{
		assert(PrevOrder && InOrder);
		_CreateSubTree(_root,PrevOrder,InOrder,len);
	}

	void PreOrder()
	{
		_PreOrder(_root);
		cout<<endl;
	}
	void PostOrder()
	{
		_PostOrder(_root);
		cout<<endl;
	}
protected:
	void _PostOrder(Node* root)
	{
		if(root==NULL)
			return;

		_PostOrder(root->_left);
		_PostOrder(root->_right);
		cout<<root->_data<<" ";
	}
	void _PreOrder(Node* root)
	{
		if(root==NULL)
			return;

		cout<<root->_data<<" ";
		_PreOrder(root->_left);
		_PreOrder(root->_right);
	}
	void _CreateSubTree(Node*& root,T* PrevOrder,T* InOrder,int len)
	{
		if(len<=0)
			return;
		//����ǰ�����е������ȴ������ĸ��ڵ�
		root=new Node(PrevOrder[0]);  
		//�������������Ҹ��ڵ㣬��ȷ����������������
		int index=0;
		for(;index<len;++index)
		{
			if(PrevOrder[0]==InOrder[index])
				break;
		}
		int LeftSub=index;   //�������ڵ���
		int RightSub=len-index-1;  //�������ڵ���

		//�ݹ鹹������������ע���������
		_CreateSubTree(root->_left,PrevOrder+1,InOrder,LeftSub);  
		_CreateSubTree(root->_right,PrevOrder+index+1,InOrder+index+1,RightSub);
	}

protected:
	Node* _root;
};

void Test()
{
	int PrevOrder[]={1,2,3,4,5,6};
	int InOrder[]={3,2,4,1,6,5};
	RebuiltBinaryTree<int> bt(PrevOrder,InOrder,6);
	bt.PreOrder();
	bt.PostOrder();
}

