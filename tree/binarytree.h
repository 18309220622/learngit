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

	void PrevOrder();     //ǰ�����
	void InOrder();       //�������
	void PostOrder();    //�������
	void LevelOrder();   //����ʵ�ֲ������
	
	void PrevOrder_NonR();     //�ǵݹ�ǰ�����
	void InOrder_NonR();       //�ǵݹ��������
	void PostOrder_NonR();     //�ǵݹ�������
	
	size_t Size();         //Ԫ�ظ���
	size_t Depth();        //���
	size_t LeafSize();     //Ҷ�ӽڵ����
	size_t GetKLevel(size_t k);    //���k��Ľڵ����

	Node* FindNode(const T& d=T())      //��ĳ�����ֵĽڵ�λ��
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
			ret=_FindNode(root->_right,d);   //������û�ҵ���ȥ��������
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
		root->_left=_CreateBinaryTree(a,size,invalid,++index);//����������
		root->_right=_CreateBinaryTree(a,size,invalid,++index);//����������
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

//��ͳд��
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


//�ִ�д��
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
void BinaryTree<T>::PrevOrder()     //ǰ�����
{
	_PrevOrder(_root);
}
template<class T>
void BinaryTree<T>::_PrevOrder(Node* root)
{
	//���ڵ�--������--������
	if(NULL==root)
	{
		return;
	}
	cout<<root->_data<<" ";
	_PrevOrder(root->_left);
	_PrevOrder((root->_right));
}

template<class T>
void BinaryTree<T>::InOrder()      //�������
{
	_InOrder(_root);
}
template<class T>
void BinaryTree<T>::_InOrder(Node* root)        
{
	//������--���ڵ�--������
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
void BinaryTree<T>::PostOrder()     //�������
{
	_PostOrder(_root);
}
template<class T>
void BinaryTree<T>::_PostOrder(Node* root)
{
	//������--������--���ڵ�
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
void BinaryTree<T>::LevelOrder()    //�������
{
	//���ö��еġ��Ƚ��ȳ������ص�
	if(NULL==_root)
	{
		return ;
	}
	queue<Node*> q;         //���У����Node*���͵Ľڵ�
	Node* cur=_root;
	q.push(cur);   //������ڵ㲻Ϊ�գ�������ڵ�(��һ��)push��ȥ
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
void BinaryTree<T>::PrevOrder_NonR()     //�ǵݹ�ǰ�����
{
	//���ڵ�--������--������

	stack< Node* > s;    //���Node*�ڵ�
	Node* cur=_root;
	while(cur||!s.empty())
	{  
		while(cur)
		{
			cout<<cur->_data<<" ";
			s.push(cur);
			cur=cur->_left;
		}
		//����whileѭ�����ʾ�������ѷ�����
		Node* top=s.top();
		s.pop();
		cur=top->_right;
	}
}

template<class T>
void BinaryTree<T>::InOrder_NonR()   //�ǵݹ��������
{
	stack< Node* > s;
	Node* cur=_root;
	while(cur||!s.empty())
	{
		//�������(��ջ)��3��2��4��1��6��5
		while(cur)
		{
			s.push(cur);
			cur=cur->_left;      
		}

		cur=s.top();
		cout<<cur->_data<<" ";
		s.pop();               
		cur=cur->_right;
//��ջ˳������1 2 3��Ȼ��3û�����ӳ���whileѭ���������3�����ص���һ��2��,
//��ʱcurָ��ָ��������,�ٴν���whileѭ��������2���ҽڵ㲻Ϊ�գ�����ѹ��4��
//Ȼ���ӡ2���ٴ�ӡ2���ҽڵ�4��4�����ҽڵ��Ϊ��ʱ���ص�1�����������ʱջΪ��
//����ǰ�ڵ㣨ָ�����1���ҽڵ㣩��Ϊ�գ�����ѹ��5,5����ڵ㲻Ϊ����ѹ��6��Ȼ
//��pop��6,5
	}
}
template<class T>
void BinaryTree<T>::PostOrder_NonR()   //�ǵݹ�������
{
	//������������������ٸ��ڵ�  (��ջ)3��4��2��6��5��1
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
size_t BinaryTree<T>::Size()   //Ԫ�ظ���
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
	++count;          //count��λ�ò�ͬ�������ֱ�����ʽ
	_Size(root->_right);
	return count;
	//if (NULL==root)
	//{
		//return 0;
	//}
	//return _Size(root->_left)+_Size(root->_right)+1;

}
template<class T>
size_t BinaryTree<T>::Depth()        //���
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
	//	return LeftDepth+1;  //�Ѹ��ڵ�����
	//}
	//else
	//{
	//	return RightDepth+1;
	//}

}

template<class T>
size_t BinaryTree<T>::LeafSize()     //Ҷ�ӽڵ����
{
	return _LeafSize(_root);
}
template<class T>
size_t BinaryTree<T>::_LeafSize(Node* root)     //Ҷ�ӽڵ����
{
	//Ҷ�ӽڵ���Ǹýڵ�û�����Һ��ӵĽڵ�
	if(NULL==root)
	{
		return 0;
	}
	else if(root->_left==NULL && root->_right==NULL)
	{
		return 1;     //����ֵ��ʽ���ݹ�һ�η�1��
	}
	else
	{
		return _LeafSize(root->_left)+_LeafSize(root->_right);
	}
}

template<class T>
size_t BinaryTree<T>::GetKLevel(size_t k)  //��k��ڵ����    
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