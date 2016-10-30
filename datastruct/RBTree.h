#pragma once

#include<iostream>
using namespace std;

enum Color
{
	RED,
	BLACK
};

template<class K,class V>
struct RBTreeNode
{
	RBTreeNode<K,V>* _left;
	RBTreeNode<K,V>* _right;
	RBTreeNode<K,V>* _parent;

	K _key;
	V _value;

	Color _col; 

	RBTreeNode(const K& key=K(),const V& value=V())
		:_left(NULL)
		,_right(NULL)
		,_parent(NULL)
		,_key(key)
		,_value(value)
		,_col(RED)
	{}
};

template<class K,class V>
class RBTree
{
	typedef RBTreeNode<K,V> Node;
public:
	RBTree()
		:_root(NULL)
	{}

	~RBTree()
	{
		_Destory(_root);
	}
	void InOrder()
	{
		_InOrder(_root);
		cout<<endl;
	}
public:
	bool Insert(const K& key,const V& value);
	bool Find(const K& key);
	bool IsRBTree();
protected:
	void _RotateL(Node*& parent);
	void _RotateR(Node*& parent);
	bool _IsRBTree(Node* root,const int count,int k);
protected:
	void _InOrder(Node* root)
	{
		if(root==NULL)
			return;

		_InOrder(root->_left);
		cout<<root->_key<<" ";
		_InOrder(root->_right);
	}
	void _Destory(Node*& root)
	{
		if (root==NULL)
			return;
		if(root)
		{
			_Destory(root->_left);
			_Destory(root->_right);
			delete root;
			root=NULL;
		}
	}
protected:
	Node* _root;
};

template<class K,class V>
void RBTree<K,V>::_RotateL(Node*& parent)
{
	Node* subR=parent->_right;
	Node* subRL=subR->_left;
	parent->_right=subRL;
	if(subRL)
		subRL->_parent=parent;
	subR->_left=parent;
	Node* ppNode=parent->_parent;
	parent->_parent=subR;
	if (ppNode==NULL)
	{
		_root=subR;
		subR->_parent=NULL;
	}
	else
	{
		if(ppNode->_left==parent)
			ppNode->_left=subR;
		else
			ppNode->_right=subR;

		subR->_parent=ppNode;
	}
}

template<class K,class V>
void RBTree<K,V>::_RotateR(Node*& parent)
{
	Node* subL=parent->_left;
	Node* subLR=subL->_right;
	parent->_left=subLR;
	if(subLR)
		subLR->_parent=parent;
	subL->_right=parent;
	Node* ppNode=parent->_parent;   //ppNode保存起初parent的parent
    parent->_parent=subL;          //重新链接
	if (ppNode==NULL)
	{
		_root=subL;
		subL->_parent=NULL;
	}
	else
	{
		if(ppNode->_left==parent)
			ppNode->_left=subL;
		else
			ppNode->_right=subL;

		subL->_parent=ppNode;
	}

}
template<class K,class V>
bool RBTree<K,V>::Insert(const K& key,const V& value)
{
	if (_root==NULL)
	{
		_root=new Node(key,value);
		_root->_col=BLACK;
		return true;
	}
	Node* cur=_root;
	Node* parent=NULL;
	while (cur)
	{
		if (cur->_key < key)
		{
			parent=cur;
			cur=cur->_right;
		}
		else if (cur->_key > key)
		{
			parent=cur;
			cur=cur->_left;
		}
		else              //cur->_key==key
		{
			return false;
		}
	}
	//找到要插入的空位置cur,进行插入
	cur=new Node(key,value);
	if(parent->_key < key)
	{
		parent->_right=cur;
		cur->_parent=parent;
	}
	else
	{
		parent->_left=cur;
		cur->_parent=parent;
	}
	
	while (cur!=_root && parent->_col==RED)  //保证parent,grandfather均存在
	{
		//遇见两个连续红节点开始调整(cur新插的节点默认为红)
		Node* grandfather=parent->_parent;
		if (parent==grandfather->_left)
		{
			Node* uncle=grandfather->_right;
			if (uncle && uncle->_col==RED)
			{
				//将grangfather变为红，parent和uncle变为黑,继续向上调
				grandfather->_col=RED;
				parent->_col=BLACK;
				uncle->_col=BLACK;

				cur=grandfather;            //继续向上调整
				parent=cur->_parent;
			}
			//uncle为黑或不存在
			else
			{
				if (parent->_right==cur)
				{
					_RotateL(parent);
					std::swap(parent,cur); 
				}
				//cur==parent->_left的情况
				_RotateR(grandfather);
				grandfather->_col=RED;
				parent->_col=BLACK;
				
				cur=parent;
				parent=cur->_parent;
			}
		}
		else   //parent==grandfather->_right
		{
			Node* uncle=grandfather->_left;
			if (uncle && uncle->_col==RED)
			{
				grandfather->_col = RED;  
				parent->_col = BLACK;  
				uncle->_col = BLACK;

				cur=grandfather;
				parent=cur->_parent;
			}
			else //uncle为黑或不存在
			{
				if (parent->_left==cur)
				{
					_RotateR(parent);
					std::swap(parent,cur);
				}
				_RotateL(grandfather);
				grandfather->_col=RED;
				parent->_col=BLACK;

				cur=parent;
				parent=cur->_parent;
			}
		}	
	}
	_root->_col=BLACK;
	return true;
}
template<class K,class V>
bool RBTree<K,V>::Find(const K& key)
{
	if(_root==NULL)
		return false;
	Node* cur=_root;
	while(cur)
	{
		if (cur->_key > key)
			cur=cur->_left;
		else if(cur->_key < key)
			cur=cur->_right;
		else
			return true;
	}
	return false;
}

template<class K,class V>
bool RBTree<K,V>:: IsRBTree()
{
	if (_root->_col==RED)
		return false;
	
	int BalckCount=0;    //用来统计任意一条路径的黑节点数量作为基准值
	int k=0;            //需要与BalckCount比较的其他路径的黑节点数量
	Node* cur=_root;
	while (cur)
	{
		if(cur->_col=BLACK)
		{
			++BalckCount;
		}
		cur=cur->_left;
	}
	return _IsRBTree(_root,BalckCount,k);
}

template<class K,class V>
bool RBTree<K,V>:: _IsRBTree(Node* root,const int BalckCount,int k)
{
	if (root==NULL)   //递归结束条件
		return true;
	//连续两个红节点则不是红黑树
	if (root->_col==RED && root->_parent->_col==RED)
		return false;
	if(root->_col==BLACK)
	{
		++k;
	}
	if(root->_left==NULL && root->_right==NULL)
	{
		if (k==BalckCount)
			return true;
		else
			cout<<"黑节点数量不同:"<<root->_key<<endl;
			return false;
	}
	return _IsRBTree(root->_left,BalckCount,k)
		&& _IsRBTree(root->_right,BalckCount,k);
}