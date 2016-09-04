#include <stdio.h>

int main(){
	int i=5,j=6,k=7;
	int *ip1=&i, *ip2=&j;
	int **ipp = &ip1; 
	int **ipp2 = &ip2; 

	printf("%d\n",**ipp);
	printf("%d\n",**ipp2);

	ipp=ipp2;

	printf("%d\n",**ipp);
	printf("%d\n",**ipp2);

	*ipp=&k;

	printf("%d\n",**ipp);
	printf("%d\n",**ipp2);
	printf("%d\n",*ip2);



	return 0;
} 
