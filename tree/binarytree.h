#pragma once

#include<iostream>
#include<queue>
#include<stack>
#include<assert.h>
using namespace std;

template<class T>
struct BinaryTreeNode
{
	BinaryTreeNode(const T& d)
		:_data(d)
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
	BinaryTree()
		:_root(NULL)
	{}
	BinaryTree(const T* a,size_t size,const T& invalid);
	BinaryTree(const BinaryTree<T>& b);
	BinaryTree& operator=(const BinaryTree<T>& b);
	~BinaryTree();

	void PrevOrder();     //前序遍历
	void InOrder();       //中序遍历
	void PostOrder();    //后序遍历
	void LevelOrder();   //队列实现层序遍历
	
	void PrevOrder_NonR();     //非递归前序遍历
	void InOrder_NonR();       //非递归中序遍历
	void PostOrder_NonR();     //非递归后序遍历
	
	size_t Size();         //元素个数
	size_t Depth();        //深度
	size_t LeafSize();     //叶子节点个数
	size_t GetKLevel(size_t k);    //求第k层的节点个数

	Node* FindNode(const T& d=T())      //找某个数字的节点位置
	{
		return _FindNode(_root,d);
	}
	
    
public:
	Node* _CreateBinaryTree(const T* a,size_t size,const T& invalid,size_t& index);
    Node* _CopyBinaryTree(Node* root);
    void _Destroy(Node* root);

	void _PrevOrder(Node* root);
    void _InOrder(Node* root);
	void _PostOrder(Node* root);

	size_t _Size(Node* root);
	size_t _Depth(Node* root);
	size_t _LeafSize(Node* root);
	size_t _GetKLevel(size_t k,Node* root);

	Node* _FindNode(Node* root,const T& d)
	{
		if (NULL==root)
		{
			return NULL;
		}
		if (root->_data==d)
		{
			return root;
		}
		Node* ret=_FindNode(root->_left,d);     
		if(NULL==ret)
		{
			ret=_FindNode(root->_right,d);   //左子树没找到再去右子树找
		}
		return ret;
	}
protected:
	Node* _root;
};

template<class T>
BinaryTree<T>::BinaryTree(const T* a,size_t size,const T& invalid)
{
	size_t index=0;
	_root=_CreateBinaryTree(a,size,invalid,index);
}
template<class T>
BinaryTreeNode<T>* BinaryTree<T>::_CreateBinaryTree(const T* a,size_t size,const T& invalid,size_t& index)
{
	assert(a);    
	Node* root=NULL;
	if(index<size && a[index]!=invalid)
	{
		root=new Node(a[index]);      
		root->_left=_CreateBinaryTree(a,size,invalid,++index);//创建左子树
		root->_right=_CreateBinaryTree(a,size,invalid,++index);//创建右子树
	}
	return root;
}


template<class T>
BinaryTree<T>::BinaryTree(const BinaryTree<T>& b)
{
	_root=_CopyBinaryTree(b._root);
}
template<class T>
BinaryTreeNode<T>* BinaryTree<T>::_CopyBinaryTree(Node* root)
{
	Node* newroot=NULL;
	if(root)
	{
		newroot=new Node(root->_data);        
		newroot->_left=(_CopyBinaryTree(root->_left));
		newroot->_right=(_CopyBinaryTree(root->_right));
	}
	return newroot;
}

//传统写法
//template<class T>
//BinaryTree<T>& BinaryTree<T>::operator=(const BinaryTree<T>& b)
//{
//	if(this!=&b)
//	{
//		Node* tmp=_CopyBinaryTree(b._root);
//		_Destroy(_root);
//		_root=tmp;
//	}
//	return *this;
//}


//现代写法
template<class T>
BinaryTree<T>& BinaryTree<T>::operator=(const BinaryTree<T>& b)
{
	if(this!=&b)
	{
		BinaryTree<T> tmp(b);
		std::swap(_root,tmp._root);
	}
	return *this;
}


template<class T>
BinaryTree<T>::~BinaryTree()
{
	_Destroy(_root);
	_root=NULL;
}
template<class T>
void BinaryTree<T>::_Destroy(Node* root)
{
	Node* cur=root;
	while(cur)
	{
		_Destroy(cur->_left);
		_Destroy(cur->_right);
		delete cur;
		cur=NULL;
	}
}


template<class T>
void BinaryTree<T>::PrevOrder()     //前序遍历
{
	_PrevOrder(_root);
}
template<class T>
void BinaryTree<T>::_PrevOrder(Node* root)
{
	//根节点--左子树--右子树
	if(NULL==root)
	{
		return;
	}
	cout<<root->_data<<" ";
	_PrevOrder(root->_left);
	_PrevOrder((root->_right));
}

template<class T>
void BinaryTree<T>::InOrder()      //中序遍历
{
	_InOrder(_root);
}
template<class T>
void BinaryTree<T>::_InOrder(Node* root)        
{
	//左子树--根节点--右子树
	if(NULL==root)
	{
		return ;
	}
	else
	{
		_InOrder(root->_left);
		cout<<root->_data<<" ";
		_InOrder(root->_right);
	}
}
template<class T>
void BinaryTree<T>::PostOrder()     //后序遍历
{
	_PostOrder(_root);
}
template<class T>
void BinaryTree<T>::_PostOrder(Node* root)
{
	//左子树--右子树--根节点
	if(NULL==root)
	{
		return;
	}
	else
	{
		_PostOrder(root->_left);
		_PostOrder(root->_right);
		cout<<root->_data<<" ";
	}
}

template<class T>
void BinaryTree<T>::LevelOrder()    //层序遍历
{
	//利用队列的“先进先出”的特点
	if(NULL==_root)
	{
		return ;
	}
	queue<Node*> q;         //队列，存放Node*类型的节点
	Node* cur=_root;
	q.push(cur);   //如果根节点不为空，则将其根节点(第一层)push进去
	while(!q.empty())
	{
		cur=q.front();
		cout<<cur->_data<<" ";
		q.pop();
		if(cur->_left)
		{
			q.push(cur->_left);
		}
		if(cur->_right)
		{
			q.push(cur->_right);
		}
	}
	cout<<endl;
}


template<class T>
void BinaryTree<T>::PrevOrder_NonR()     //非递归前序遍历
{
	//根节点--左子树--右子树

	stack< Node* > s;    //存放Node*节点
	Node* cur=_root;
	while(cur||!s.empty())
	{  
		while(cur)
		{
			cout<<cur->_data<<" ";
			s.push(cur);
			cur=cur->_left;
		}
		//走完while循环后表示左子树已访问完
		Node* top=s.top();
		s.pop();
		cur=top->_right;
	}
}

template<class T>
void BinaryTree<T>::InOrder_NonR()   //非递归中序遍历
{
	stack< Node* > s;
	Node* cur=_root;
	while(cur||!s.empty())
	{
		//中序遍历(出栈)是3，2，4，1，6，5
		while(cur)
		{
			s.push(cur);
			cur=cur->_left;      
		}

		cur=s.top();
		cout<<cur->_data<<" ";
		s.pop();               
		cur=cur->_right;
//入栈顺序先是1 2 3，然后3没有左孩子出了while循环后先输出3并返回到上一级2处,
//此时cur指针指向右子树,再次进入while循环，由于2的右节点不为空，所以压入4，
//然后打印2，再打印2的右节点4，4的左右节点均为空时返回到1处并输出，此时栈为空
//但当前节点（指向的是1的右节点）不为空，所以压入5,5的左节点不为空再压入6，然
//后pop出6,5
	}
}
template<class T>
void BinaryTree<T>::PostOrder_NonR()   //非递归后序遍历
{
	//后序遍历是先左再右再根节点  (出栈)3，4，2，6，5，1
	Node* cur=_root;
	Node* prev=NULL;
	stack<Node*> s;
	s.push(cur);
	while (!s.empty())
	{
		cur=s.top();

		if((cur->_left==NULL && cur->_right==NULL)
			||(prev!=NULL)&& (prev==cur->_left || prev==cur->_right))
		{
			cout<<cur->_data<<" ";
			s.pop();
			prev=cur;
		}
		else
		{
			if (cur->_right)
			{
				s.push(cur->_right);
			}
			if(cur->_left)
			{
				s.push(cur->_left);
			}
		}
	}
}
template<class T>
size_t BinaryTree<T>::Size()   //元素个数
{
	return _Size(_root);
}

template<class T>
size_t BinaryTree<T>::_Size(Node* root)         
{
	static size_t count=0;
	if(NULL==root)
	{
		return 0;
	}
	_Size(root->_left);
	++count;          //count的位置不同类似三种遍历方式
	_Size(root->_right);
	return count;
	//if (NULL==root)
	//{
		//return 0;
	//}
	//return _Size(root->_left)+_Size(root->_right)+1;

}
template<class T>
size_t BinaryTree<T>::Depth()        //深度
{
	return _Depth(_root);
}
template<class T>
size_t BinaryTree<T>::_Depth(Node* root)        
{
	if (NULL==root)
	{
		return 0;
	}
	size_t LeftDepth=_Depth(root->_left);
	size_t RightDepth=_Depth(root->_right);

	return LeftDepth>RightDepth ? LeftDepth+1:RightDepth+1;
	//if(LeftDepth>RightDepth)
	//{
	//	return LeftDepth+1;  //把根节点算上
	//}
	//else
	//{
	//	return RightDepth+1;
	//}

}

template<class T>
size_t BinaryTree<T>::LeafSize()     //叶子节点个数
{
	return _LeafSize(_root);
}
template<class T>
size_t BinaryTree<T>::_LeafSize(Node* root)     //叶子节点个数
{
	//叶子节点就是该节点没有左右孩子的节点
	if(NULL==root)
	{
		return 0;
	}
	else if(root->_left==NULL && root->_right==NULL)
	{
		return 1;     //返回值形式，递归一次返1，
	}
	else
	{
		return _LeafSize(root->_left)+_LeafSize(root->_right);
	}
}

template<class T>
size_t BinaryTree<T>::GetKLevel(size_t k)  //第k层节点个数    
{
	return _GetKLevel(k,_root);
}
template<class T>
size_t BinaryTree<T>::_GetKLevel(size_t k,Node* root)    
{
	assert(k>0);
	if(NULL==root)
	{
		return 0;
	}
	if(k==1)          
	{
		return 1;
	}
	size_t leftsz=_GetKLevel(k-1,root->_left);
	size_t rightsz=_GetKLevel(k-1,root->_right);
	return leftsz+rightsz;
}