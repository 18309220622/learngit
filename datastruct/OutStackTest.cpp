#include "OutStackIsLeaglity.h"

void test()  
{  
	//int inStack[]={1,2,3,4,5};  
	//int outStack[]={4,5,3,2,1};       //legality  
	//int outStack[]={4,3,5,1,2};        //no  

	char inStack[]={'a','b','c','d','e'};  
	//char outStack[]={'d','e','c','b','a'};  //legality  
	//char outStack[]={'d','c','e','a','b'};    //no  
	char outStack[]={'a','c','d'};              //no  
	size_t szin=sizeof(inStack)/sizeof(inStack[0]);  
	size_t szout=sizeof(outStack)/sizeof(outStack[0]);  
	cout<<CheckStackLeg(inStack,outStack,szin,szout)<<endl;  
}

int main()
{
	test();
	system("pause");
	return 0;
}