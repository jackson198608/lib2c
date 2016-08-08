#include <stdio.h>
#include "talk.h"
#include "sleep.h"

void main(){
	printf("%d\n",test);
	printf("what is the faviroute things you wants to do?\n");
	while(1){
		say("hello"); 
		what_rest_for(10);   
	}
}
