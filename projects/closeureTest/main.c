#include <stdio.h>  
  
void *outer(int var)  
{  
    void inner()  
    {  
        printf("inner  %d\n", var);  
    }  
    printf("outer\n");  
    return &inner;  
}  
  
int main()  
{  
    void (*pInner)() = outer(89);  
    (*pInner)();  
    return 0;  
}  
