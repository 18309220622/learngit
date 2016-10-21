#pragma once

#include<iostream>
#include<queue>
#include<assert.h>
using namespace std;

template<class T>
struct SearchBinaryTreeNode
{
	SearchBinaryTreeNode<T>* _left;
	SearchBinaryTreeNode<T>* _right;
	T _key;               //�ؼ���

	SearchBinaryTreeNode(const T& key)
		:_left(NULL)
		,_right(NULL)
		,_key(key)
	{}
};

template<class T>
class SearchBinaryTree
{
	typedef SearchBinaryTreeNode<T> Node;
public:
	SearchBinaryTree()
		:_root(NULL)
	{}
	SearchBinaryTree(T* a,size_t size)
		:_root(NULL)
	{
		assert(a);
		for (size_t i=0;i<size;++i)
		{
			Insert(a[i]);
		}
	}
	SearchBinaryTree(const SearchBinaryTree<T>& s)//�ǵݹ�
		:_root(NULL)
	{
		if(s._root==NULL)
			return;
		queue<Node*> q;
		q.push(s._root);
		while (!q.empty())
		{
			Node* cur=q.front();
			Insert(cur->_key);
			q.pop();
			if(cur->_left)
				q.push(cur->_left);

			if(cur->_right)
				q.push(cur->_right);
		}
	}
	/*SearchBinaryTree(const SearchBinaryTree<T>& s)
	{
		_root=_Copy(s._root);
	}*/

	SearchBinaryTree<T>& operator=(SearchBinaryTree<T> s)
	{
		if (this!=&s)
		{
			SearchBinaryTree<T> tmp(s);   //ͨ��������ʱ����
			std::swap(_root,tmp._root);
		}
		return *this;
	}

	~SearchBinaryTree()
	{
		_DelNode(_root);
	}

public:
	bool Insert(const T& key);
	bool Remove(const T& key);
	bool Find(const T& key);
	void InOrder();

	bool InsertR(const T& key);      //�ݹ����
	bool RemoveR(const T& key);
	bool FindR(const T& key);
protected:
	bool _InsertR(Node* &root,const T& key);
	bool _RemoveR(Node* &root,const T& key);
	bool _FindR(Node* &root,const T& key);
	void _InOrder(Node*&root);

	Node* _Copy(Node* root);
	void _DelNode(Node* &root);
protected:
	Node* _root;
};

template<class T>
bool SearchBinaryTree<T>::Insert(const T& key)
{
	//1.������Ϊ��
	//2.Ҫ�����ֵ�Ѿ�����
	//3.������

	if(NULL==_root)
	{
		_root=new Node(key);
		return true;
	}
	Node* cur=_root;
	Node* parent=NULL;
	while(cur)
	{
		parent=cur;
		if (cur->_key < key)
		{
			cur=cur->_right;
		}
		else if(cur->_key > key)
		{
			cur=cur->_left;
		}
		else         //cur->_key==key(���ظ�����)
			return false;
	}

	if (parent->_key < key)
	{
		parent->_right=new Node(key);
		return true;
	}
	else if(parent->_key > key)
	{
		parent->_left=new Node(key);
		return true;
	}
	else
	{
		return false;
	}
}


template<class T>
bool SearchBinaryTree<T>::InsertR(const T& key)      //�ݹ����
{
	return _InsertR(_root,key);

}
template<class T>
bool SearchBinaryTree<T>::_InsertR(Node* &root,const T& key)      
{
	if (root==NULL)
	{
		root=new Node(key);
		return true;
	}
	if (root->_key < key)
	{
		return _InsertR(root->_right,key);
	}
	else if (root->_key >key)
	{
		return _InsertR(root->_left,key);
	}
	else
		return false;   //root->_key==key && root!=NULL
}

template<class T>
bool SearchBinaryTree<T>::Remove(const T& key)  
{  
	Node* cur=_root;  
	Node* parent = NULL;  
	while (cur)  
	{  
		if (cur->_key < key)  
		{  
			parent = cur;  
			cur = cur->_right;  
		}  
		else if (cur->_key>key)  
		{  
			parent = cur;  
			cur = cur->_left;  
		}  
		else  
		{  //�ҵ���ʼɾ��
			if (cur->_left == NULL)     //���cur������Ϊ�գ������Ҷ�Ϊ��  
			{  
				if (parent == NULL)  
					_root = cur->_right;           
				else  
				{  
					if (parent->_left==cur)  
						parent->_left = cur->_right;  
					else  
						parent->_right = cur->_right;  
				}  
				delete cur;  
			}  
			else if (cur->_right == NULL)    //���cur���Һ���Ϊ��  
			{  
				if (parent == NULL)  
					_root = cur->_left; 

				else  
				{  
					if (parent->_left == cur)  
						parent->_left = cur->_left;  
					else  
						parent->_right = cur->_left;  
				}  
				delete cur;  
			} 
			else            
			{  
				//���ҽڵ����Ϊ�յ����,ͨ��������������������ڵ�
				//���������������ҽڵ�����滻�ķ���
				parent=cur;
				Node* MinRight = cur->_right;  
				while (MinRight->_left)  
				{   
					parent=MinRight;
					MinRight=MinRight->_left;  
				}  
				//swap(cur->_key,MinRight->_key);      //��������������ֵ
				cur->_key=MinRight->_key;
				if (parent->_left == MinRight)  
				{  
					parent->_left=MinRight->_right; 
				}  
				else  
					parent->_right=MinRight->_right;

				delete MinRight;                   
			}
			return true;
		}
	}  
	return false;  
}  

template<class T>
bool SearchBinaryTree<T>::RemoveR(const T& key)
{
	return _RemoveR(_root,key);
}

template<class T>
bool SearchBinaryTree<T>::_RemoveR(Node* &root,const T& key)
{
	assert(root);
	if (root==NULL)
	{
		return false;
	}
	if (root->_key < key)
		return _RemoveR(root->_right,key);
	else if(root->_key > key)
		return _RemoveR(root->_left,key);
	else
	{
		Node*del=root;
		if (root->_left==NULL)
			root=root->_right;
		else if(root->_right==NULL)
			root=root->_left;
		else    //���Һ��Ӷ���Ϊ��
		{
			Node* parent=root;
			Node* MinRight=root->_right;
			while (MinRight->_left)
			{
				parent=MinRight;
				MinRight=MinRight->_left;
			}

			root->_key=MinRight->_key;
			del=MinRight;

			if (parent->_left==MinRight)
				parent->_left=MinRight->_right;
			else
				parent->_right=MinRight->_right;
		}
		delete del;
		del=NULL;
		return true;
	}
}

template<class T>
bool SearchBinaryTree<T>::Find(const T& key)
{
	Node* cur=_root;
	while(cur)
	{
		if (cur->_key < key)
		{
			cur=cur->_right;
		}
		else if (cur->_key > key)
		{
			cur=cur->_left;
		}
		else
		{
			return true;
		}
	}
	return false;
}

template<class T>
bool SearchBinaryTree<T>::FindR(const T& key)
{
	return _FindR(_root,key);
}
template<class T>
bool SearchBinaryTree<T>::_FindR(Node* &root,const T& key)
{
	if (root==NULL)
	{
		return false;
	}
	if (root->_key < key)
		return _FindR(root->_right,key);

	else if (root->_key > key)
		return _FindR(root->_left,key);
	else
		return true;
}

template<class T>
SearchBinaryTreeNode<T>* SearchBinaryTree<T>::_Copy(Node* root)
{
	Node* cur=root;
	Node* NewNode=NULL;
	if(cur)
	{
		NewNode=new Node(cur->_key);
		NewNode->_left=_Copy(cur->_left);
		NewNode->_right=_Copy(cur->_right);
	}
	return NewNode;
}

template<class T>
void SearchBinaryTree<T>::_DelNode(Node* &root)
{
	Node* cur=root;
	while (cur)
	{
		_DelNode(cur->_left);
		_DelNode(cur->_right);
		delete cur;
		cur=NULL;
	}
}

template<class T>
void SearchBinaryTree<T>::InOrder()
{
	_InOrder(_root);
	cout<<endl;
}
template<class T>
void SearchBinaryTree<T>::_InOrder(Node*& root)
{
	if (root==NULL)
		return;

	_InOrder(root->_left);
	cout<<root->_key<<" ";
	_InOrder(root->_right);
}