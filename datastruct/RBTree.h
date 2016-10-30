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
	Node* ppNode=parent->_parent;   //ppNode�������parent��parent
    parent->_parent=subL;          //��������
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
	//�ҵ�Ҫ����Ŀ�λ��cur,���в���
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
	
	while (cur!=_root && parent->_col==RED)  //��֤parent,grandfather������
	{
		//��������������ڵ㿪ʼ����(cur�²�Ľڵ�Ĭ��Ϊ��)
		Node* grandfather=parent->_parent;
		if (parent==grandfather->_left)
		{
			Node* uncle=grandfather->_right;
			if (uncle && uncle->_col==RED)
			{
				//��grangfather��Ϊ�죬parent��uncle��Ϊ��,�������ϵ�
				grandfather->_col=RED;
				parent->_col=BLACK;
				uncle->_col=BLACK;

				cur=grandfather;            //�������ϵ���
				parent=cur->_parent;
			}
			//uncleΪ�ڻ򲻴���
			else
			{
				if (parent->_right==cur)
				{
					_RotateL(parent);
					std::swap(parent,cur); 
				}
				//cur==parent->_left�����
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
			else //uncleΪ�ڻ򲻴���
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
	
	int BalckCount=0;    //����ͳ������һ��·���ĺڽڵ�������Ϊ��׼ֵ
	int k=0;            //��Ҫ��BalckCount�Ƚϵ�����·���ĺڽڵ�����
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
	if (root==NULL)   //�ݹ��������
		return true;
	//����������ڵ����Ǻ����
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
			cout<<"�ڽڵ�������ͬ:"<<root->_key<<endl;
			return false;
	}
	return _IsRBTree(root->_left,BalckCount,k)
		&& _IsRBTree(root->_right,BalckCount,k);
}