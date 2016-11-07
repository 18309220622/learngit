#include"HashList.h"

void TestInt()
{
	HashList<int,int> hf;
	hf.Insert(23,1);
	hf.Insert(89,1);
	hf.Insert(83,1);
	hf.Insert(19,1);
	hf.Insert(110,1);

	hf.Print();

	cout<<"Find(23):"<<hf.Find(23)<<endl;
	cout<<"Find(80):"<<hf.Find(80)<<endl;
	cout<<"Remove(110):"<<hf.Remove(110)<<endl;
}

void TestString()
{
	HashList<string,int> hf;
	hf.Insert("sort",1);
	hf.Insert("size",1);
	hf.Insert("vector",1);
	hf.Insert("english",1);

	hf.Print();

	cout<<"Find(sort)"<<hf.Find("sort");
	cout<<"Remove(size)"<<hf.Remove("size");

}
int main()
{
	TestInt();
	//TestString();
	system("pause");
	return 0;
}