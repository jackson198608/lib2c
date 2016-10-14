#include <stdio.h>

void test(char* message){
	printf("test %s\n",message);
}

int main(){
	void (*myP)(char*);
	test("zhou");
	myP=&test;
	(*myP)("this is from pointer call");
	return 0;
}
