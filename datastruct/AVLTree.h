#pragma once

#include<iostream>
#include<assert.h>
#include<cmath>
using namespace std;

template<class K,class V>
struct AVLTreeNode 
{
	AVLTreeNode<K,V>* _left;
	AVLTreeNode<K,V>* _right;
	AVLTreeNode<K,V>*_parent;
	K _key;
	V _value;
	int _bf;     //ƽ�����ӣ��������߶ȼ�ȥ�������߶�

	AVLTreeNode(const K& key=K(),const V& value=V())
		:_left(NULL)
		,_right(NULL)
		,_parent(NULL)
		,_key(key)
		,_value(value)
		,_bf(0)
	{}
};

template<class K,class V>
class AVLTree
{
	typedef AVLTreeNode<K,V> Node;
public:
	AVLTree()
		:_root(NULL)
	{}

	~AVLTree()
	{
		_Destroy(_root);
	}

	void InOrder()
	{
		_InOrder(_root);
		cout<<endl;
	}
	bool Insert(const K& key,const V& value);
	bool Isbalance()
	{
		return _Isbalance(_root);
	}

	bool IsbalanceOP()
	{
		size_t Height=0;
		return _IsbalanceOP(_root,Height);
	}
protected:
	void _RotateL(Node*& parent);    //����
	void _RotateR(Node*& parent);    //�ҵ���
	void _RotateRL(Node*& parent);   //������
	void _RotateLR(Node*& parent);   //������ת

	void _Destroy(Node*& root);
	void _InOrder(Node* root);
	bool _Isbalance(Node* root);
	size_t _Height(Node* root)
	{
		if(root==NULL)
			return 0;
		size_t leftHeight=_Height(root->_left)+1;
		size_t rightHeight=_Height(root->_right)+1;
		return leftHeight > rightHeight ? leftHeight:rightHeight;
	}
	bool _IsbalanceOP(Node* root,size_t& Height);
protected:
	Node* _root;
};

template<class K,class V>
void AVLTree<K,V>::_Destroy(Node*& root)
{
	if (root==NULL)
	{
		return ;
	}
	while (root)
	{
		_Destroy(root->_left);
		_Destroy(root->_right);
		delete root;
		root=NULL;
	}
}

template<class K,class V>
void AVLTree<K,V>::_InOrder(Node* root)
{
	if (root==NULL)
		return;
	_InOrder(root->_left);
	cout<<root->_key<<" ";
	_InOrder(root->_right);
}

template<class K,class V>
bool AVLTree<K,V>::_Isbalance(Node* root)
{
	if (root==NULL)
		return true;
	size_t LeftHeight=_Height(root->_left);
	size_t RightHeight=_Height(root->_right);
	int bf=RightHeight-LeftHeight;
	if (root->_bf!=bf)
	{
		cout<<"Unbalance:"<<root->_key<<endl;
		return false;
	}
	return abs(bf)<2 && _Isbalance(root->_left) 
		&& _Isbalance(root->_right);
}
template<class K,class V>
bool AVLTree<K,V>::_IsbalanceOP(Node* root,size_t& Height)
{
	if (root==NULL)
	{
		Height=0;
		return true;
	}
	size_t LeftHeight=0;
	size_t RightHeight=0;
	if (_IsbalanceOP(root->_left,LeftHeight)==false)
		return false;
	if(_IsbalanceOP(root->_right,RightHeight)==false)
		return false;
	//��ʾ�Ե�ǰ�ڵ�Ϊ���ڵ������������ƽ���
	int bf=RightHeight-LeftHeight;
	if (abs(bf)<2)
	{
		Height=1+(RightHeight > LeftHeight ? RightHeight : LeftHeight);
		return true;
	}
}
template<class K,class V>
bool AVLTree<K,V>::Insert(const K& key,const V& value)
{
	//��keyֵΪ��׼��keyֵ��ͬ���벻�ɹ�
	if (_root==NULL)
	{
		_root=new Node(key,value);
		return true;
	}
	Node* cur=_root;
	Node* parent=NULL;
	while(cur)
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
		else 
			return false;
	}
	//�ҵ�����λ��cur,��parent������
	cur=new Node(key,value);
	if (parent->_key < key)
	{
		parent->_right=cur;
		cur->_parent=parent;
	}
	else if (parent->_key > key)
	{
		parent->_left=cur;
		cur->_parent=parent;
	}

	//����Ƿ�ƽ��,��ƽ����е���
	parent=cur->_parent;
	while (parent)
	{
		//���ж�cur��ӵ�λ�ã��Ӷ�ȷ����������parent->_bf
		if (parent->_left==cur)
		{
			parent->_bf--;
		}
		if (parent->_right==cur)
		{
			parent->_bf++;
		}

		if (parent->_bf==0)
		{
			break;
		}
		else if (parent->_bf==1 || parent->_bf==-1) //���ĸ߶ȱ��ˣ��������ϵ���
		{                                      
			cur=parent;
			parent=cur->_parent;
		}
		else   //parent->_bf==2 || parent->_bf==-2
		{
			if (parent->_bf==2)
			{
				if (cur->_bf==1)  //��Ҫ����
					_RotateL(parent);
				else
					_RotateRL(parent); //����˫��
			}
			else if (parent->_bf==-2)
			{
				if (parent->_bf==-2)
				{
					if (cur->_bf==-1)  //��Ҫ�ҵ���
						_RotateR(parent);
					else
						_RotateLR(parent); //����˫��
				}
			}
		}
	}
}

template<class K,class V>
void AVLTree<K,V>::_RotateL(Node*& parent)
{
	Node* subR=parent->_right;
	Node* subRL=subR->_left;
	Node* ppNode=parent->_parent;
	subR->_left=parent;
	parent->_right=subRL;
	if(subRL)
		subRL->_parent=parent;
	parent->_parent=subR;
	if (ppNode==NULL)
	{
		_root=subR;
		subR->_parent=NULL;
	}
	else
	{
		if (ppNode->_right==parent)
			ppNode->_right=subR;
		else
			ppNode->_left=subR;

		subR->_parent=ppNode;
	}
	subR->_bf=parent->_bf=0;     //����ƽ������
}

template<class K,class V>
void AVLTree<K,V>::_RotateR(Node*& parent)
{
	Node* subL=parent->_left;
	Node* subLR=subL->_right;
	Node* ppNode=parent->_parent;
	parent->_left=subLR;
	if (subLR)
	{
		subLR->_parent=parent;
	}
	subL->_right=parent;
	parent->_parent=subL;
	if (ppNode==NULL)
	{
		_root=subL;
		subL->_parent=NULL;
	}
	else
	{
		if (ppNode->_left==parent)
			ppNode->_left=subL;
		else
			ppNode->_right=subL;

        subL->_parent=ppNode;
	}
	subL->_bf=parent->_bf=0;
}


template<class K,class V>
void AVLTree<K,V>::_RotateLR(Node*& parent)
{
	Node* subL=parent->_left;
	Node* subLR=subL->_right;
	int bf=subLR->_bf;
	_RotateL(parent->_left);
	_RotateR(parent);
	if (bf==0)  //�����ڵ�
	{
		parent->_bf=subL->_bf=subLR->_bf=0;
	}
	else if(bf==-1)  //b������
	{  
		parent->_bf=1;
		subL->_bf=0;
		subLR->_bf=0;
	}
	else           //c������
	{
		parent->_bf=0;
		subL->_bf=-1;
		subLR->_bf=1;
	}
}

template<class K,class V>
void AVLTree<K,V>::_RotateRL(Node*& parent)
{
	Node* subR=parent->_right;
	Node* subRL=subR->_left;
	int bf=subRL->_bf;
	_RotateR(parent->_right);
	_RotateL(parent);
	if (bf==0)  //�����ڵ�
	{
		parent->_bf=subR->_bf=subRL->_bf=0;
	}
	else if(bf==-1)  //b������
	{  
		parent->_bf=0;
	    subR->_bf=1;
		subRL->_bf=0;
	}
	else           //c������
	{
		parent->_bf=-1;
		subR->_bf=0;
		subRL->_bf=1;
	}
}

