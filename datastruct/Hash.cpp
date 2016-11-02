#include"Hash.h"

void test()
{
	HashTable<int,int> ht;
	int arr[]={89,18,49,58,9};
	size_t sz=sizeof(arr)/sizeof(arr[0]);
	for(size_t i=0;i<sz;++i)
	{
		ht.Insert(arr[i],i);
	}
	ht.Print();

	cout<<"Find(89):"<<ht.Find(89)->_key<<endl;
	cout<<"Find(18):"<<ht.Find(18)->_key<<endl;
	cout<<"Find(49):"<<ht.Find(49)->_key<<endl;
	cout<<"Find(58):"<<ht.Find(58)->_key<<endl;
	cout<<"Find(9):"<<ht.Find(9)->_key<<endl;

	cout<<"Insert(5,1):"<<ht.Insert(5,1)<<endl;
	cout<<"Insert(90,1):"<<ht.Insert(90,1)<<endl;
	ht.Print();
}

int main()
{
	test();
	system("pause");
	return 0;
}