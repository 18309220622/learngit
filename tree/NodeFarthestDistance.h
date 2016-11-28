#pragma once

#include<iostream>
#include<assert.h>
using namespace std;

template<class T>
struct BinaryTreeNode
{
	BinaryTreeNode(const T& data)
		:_data(data)
		,_left(NULL)
		,_right(NULL)
	{}

	T _data;
	BinaryTreeNode<T>* _left;
	BinaryTreeNode<T>* _right;
};

template<class T>
class BinaryTree
{
	typedef BinaryTreeNode<T> Node;

public:
	BinaryTree(const T* arr,size_t size,const T& invalid)
	{
		size_t index=0;
		_root=_CreateBinaryTree(arr,size,invalid,index);
	}
	void PreOrder()
	{
		_PreOrder(_root);
		cout<<endl;
	}
	int GetFarthestDistance()
	{
		int distance=0;
		_GetFarthestDistance(_root,distance);
		return distance;
	}
protected:
	void _PreOrder(Node* root)
	{
		if(root==NULL)
			return ;

		cout<<root->_data<<" ";
		_PreOrder(root->_left);
		_PreOrder(root->_right);
	}

	Node* _CreateBinaryTree(const T* arr,size_t size,const T& invalid,size_t& index)
	{
		assert(arr);
		Node* root=NULL;
		if(index<size && arr[index]!=invalid)
		{
			root=new Node(arr[index]);
			root->_left=_CreateBinaryTree(arr,size,invalid,++index);
			root->_right=_CreateBinaryTree(arr,size,invalid,++index);
		}
		return root;
	}

	int _GetFarthestDistance(Node* root,int& distance)
	{
		if(root==NULL)
			return 0;

		int left =_GetFarthestDistance(root->_left,distance);
		int right =_GetFarthestDistance(root->_right,distance);
		//当前节点的深度，即左右子树最大基础上+1
		int Depth=left>right ?left+1:right+1;
		if(left + right > distance)
			distance = left+right;
		return Depth;
	}
protected:
	Node* _root;
};

void test()
{
	//int arr[]={1,2,3,'#','#',4,'#','#',5,6};
	int arr[]={1,2,'#',3,'#','#',4,5,'#',6,'#',7,'#','#',8};
	BinaryTree<int> bt(arr,10,'#');
	bt.PreOrder();
	//cout<<bt.GetFarthestDistance()<<endl;  //4
	cout<<bt.GetFarthestDistance()<<endl;    //5
}