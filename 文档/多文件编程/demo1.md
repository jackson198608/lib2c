# 无头文件，演示编译寻找函数过程
## 创建主文件，里面用了两个目前还没有定义的函数 

```c
include <stdio.h>

void main(){
        printf("what is the faviroute things you wants to do?\n");
        while(1){
                say("hello");
                what_rest_for(10);
        }
}

```
## 编译得到目标代码

```
gcc -c sayhello.c -o say.o
```

## 得到输出如下

```
sayhello.c: In function ‘main’:
sayhello.c:6:3: warning: implicit declaration of function ‘say’ [-Wimplicit-function-declaration]
   say("hello"); 
   ^
sayhello.c:7:3: warning: implicit declaration of function ‘what_rest_for’ [-Wimplicit-function-declaration]
   what_rest_for(10);   

```

- 编译阶段仅仅是警告

## 链接得到可执行文件

```
gcc say.o -o say
```

## 得到错误输出，提出找不到函数的定义

```
say.o：在函数‘main’中：
sayhello.c:(.text+0x19)：对‘say’未定义的引用
sayhello.c:(.text+0x28)：对‘what_rest_for’未定义的引用
collect2: error: ld returned 1 exit status
```

## 编写what_rest_for函数文件

```c
void what_rest_for(int seconds){
        sleep(seconds);
}

```

## 编译得到目标代码
- gcc -c sleep.c -o sleep.o
- 输出如下：

```
sleep.c: In function ‘what_rest_for’:
sleep.c:2:2: warning: implicit declaration of function ‘sleep’ [-Wimplicit-function-declaration]
  sleep(seconds);
  ^
```

## 编写say函数文件

```c
void say(char* message){
        printf("%s\n",message);
}

```


## 编译得到目标代码
- gcc -c talk.c -o talk.o
- 输出如下：

```
talk.c: In function ‘say’:
talk.c:2:2: warning: implicit declaration of function ‘printf’ [-Wimplicit-function-declaration]
  printf("%s\n",message);
  ^
talk.c:2:2: warning: incompatible implicit declaration of built-in function ‘printf’
talk.c:2:2: note: include ‘<stdio.h>’ or provide a declaration of ‘printf’

```

## 重新生成链接生成可执行文件，新增加入上面两个目标代码
```
 gcc sleep.o  say.o talk.o -o say
```

- 没有报错，成功生成可执行文件。
- talk.c里面找不到的printf,以及sleep.c里面找不到的sleep函数，都在目标代码say.o中找到了
- 因为say.c引入了stdio.h，里面有函数的声明。已经可以找到定义


## 写成makefile
```
say: sleep.o say.o talk.o
        cc -o say sleep.o say.o talk.o

say.o: sayhello.c
        cc -c sayhello.c -o say.o

sleep.o: sleep.c
        cc -c sleep.c -o sleep.o

talk.o: talk.c
        cc -c talk.c -o talk.o 

clean:
        rm say say.o sleep.o talk.o 

```
