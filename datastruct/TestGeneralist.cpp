#include"generalist.h"
void test()
{
	char str[]="(a,b,(c,d),(e,(f),h))";
	Generalist g1(str);
	g1.Print();
	cout<<endl;
	Generalist g2(g1);
	g2.Print();
	cout<<endl;
	Generalist g3;
	g3=g1;
	g3.Print();
	cout<<endl;
	cout<<"大小:"<<g1.Size()<<endl;      //6
	cout<<"深度:"<<g1.Depth()<<endl;    //4
}
int main()
{
	test();
	system("pause");
	return 0;
}