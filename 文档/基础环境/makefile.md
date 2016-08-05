# 简介
- 定义
```
 一个工程中的源文件不计数，其按类型、功能、模块分别放在若干个目录中.
makefile定义了一系列的规则来指定:
	哪些文件需要先编译
	哪些文件需要后编译，
	哪些文件需要重新编译，
甚至于进行更复杂的功能操作，因为makefile就像一个Shell脚本一样，其中也可以执行操作系统的命令。

```

- makefile带来的好处就是——“自动化编译”，一旦写好，只需要一个make命令，整个工程完全自动编译，极大的提高了软件开发的效率

- make是一个命令工具，是一个解释makefile中指令的命令工具，一般来说，大多数的IDE都有这个命令，比如：Delphi的make，Visual C++的nmake，Linux下GNU的make。

- 不同产商的make各不相同，也有不同的语法，但其本质都是在“文件依赖性”上做文章，这里，仅对GNU的make进行讲述


# makefile常见作用

```
1. 如果工程没有编译过，那么我们的所有C文件都要编译并被链接。
2. 如果已经编译过的工程的某几个C文件被修改，那么我们只编译被修改的C文件，并链接目标程序。
3. 如果这个工程的头文件被改变了，那么我们需要编译引用了这几个头文件的C文件，并链接目标程序。
```

- 只要我们的Makefile写得够好，所有的这一切，我们只用一个make命令就可以完成
- make命令会自动智能地根据当前的文件修改的情况来确定哪些文件需要重编译，从而自己编译所需要的文件和链接目标程序。


# makefile 语法
## 书写语法

```
target ... : prerequisites ...
command
...
...
```
- target也就是一个目标文件，可以是Object File，也可以是执行文件。还可以是一个标签（Label），对于标签这种特性，以后会讲到
- prerequisites就是，要生成那个target所需要的文件或是目标。
- command也就是make需要执行的命令。（任意的Shell命令,要以tab开头）
- 这是一个文件的依赖关系
- target这一个或多个的目标文件依赖于prerequisites中的文件，其生成规则定义在command中。
- prerequisites中如果有一个以上的文件比target文件要新的话，command所定义的命令就会被执行。
- 这就是Makefile的规则。也就是Makefile中最核心的内容。

## makefile 变量
- 定义方式
```
objects = main.o kbd.o command.o display.o /
insert.o search.o files.o utils.o
```

- 使用方式
```
edit : $(objects)
cc -o edit $(objects)
```

## makefile 自动推导依赖关系
- 只要make看到一个[.o]文件，它就会自动的把[.c]文件加在依赖关系中


## makefile 如何理解最终目标
- 在Makefile中，规则的顺序是很重要的
- Makefile中只应该有一个最终目标，其它的目标都是被这个目标所连带出来的
- 第一条规则中的目标将被确立为最终的目标。如果第一条规则中的目标有很多个，那么，第一个目标会成为最终的目标。make所完成的也就是这个目标。



# make
## make 命令
### make clean
- 删除执行文件和所有的中间目标文件

## make 工作原理
- make会在当前目录下找名字叫“Makefile”或“makefile”的文件。
- 如果找到，它会找文件中的第一个目标文件（target）,他会找到“edit”这个文件，并把这个文件作为最终的目标文件。
- 如果最终目标文件不存在，或是所依赖的后面的 .o 文件的文件修改时间要比edit这个文件新，那么，他就会执行后面所定义的命令来生成edit这个文件。
- 如果最终文件所依赖的.o文件也不存在，那么make会在当前文件中找目标为.o文件的依赖性，如果找到则再根据那一个规则生成.o文件。（这有点像一个堆栈的过程）
- 这就是整个make的依赖性，make会一层又一层地去找文件的依赖关系，直到最终编译出第一个目标文件。
- 在找寻的过程中，如果出现错误，比如最后被依赖的文件找不到，那么make就会直接退出，并报错，而对于所定义的命令的错误，或是编译不成功，make根本不理。make只管文件的依赖性


## make 工作方式
1. 读入所有的Makefile
2. 读入被include的其它Makefile
3. 初始化文件中的变量
4. 推导隐晦规则，并分析所有规则
5. 为所有的目标文件创建依赖关系链
6. 根据依赖关系，决定哪些目标要重新生成
7. 执行生成命令

# demo示例
## demo 1
- 如果一个工程有3个头文件，和8个C文件，我们为了完成前面所述的那三个规则，我们的Makefile应该是下面的这个样子的。

```
edit : main.o kbd.o command.o display.o /
insert.o search.o files.o utils.o
cc -o edit main.o kbd.o command.o display.o /
insert.o search.o files.o utils.o

main.o : main.c defs.h
cc -c main.c
kbd.o : kbd.c defs.h command.h
cc -c kbd.c
command.o : command.c defs.h command.h
cc -c command.c
display.o : display.c defs.h buffer.h
cc -c display.c
insert.o : insert.c defs.h buffer.h
cc -c insert.c
search.o : search.c defs.h buffer.h
cc -c search.c
files.o : files.c defs.h buffer.h command.h
cc -c files.c
utils.o : utils.c defs.h
cc -c utils.c
clean :
rm edit main.o kbd.o command.o display.o /
insert.o search.o files.o utils.o
```

- 反斜杠（/）是换行符的意思。这样比较便于Makefile的易读
- 在这个makefile中，目标文件（target）包含：执行文件edit和中间目标文件（*.o）
- 依赖文件（prerequisites）就是冒号后面的那些 .c 文件和 .h文件
- 每一个 .o 文件都有一组依赖文件，而这些 .o 文件又是执行文件 edit 的依赖文件
- 依赖关系的实质上就是说明了目标文件是由哪些文件生成的，换言之，目标文件是哪些文件更新的。
- 在定义好依赖关系后，后续的那一行定义了如何生成目标文件的操作系统命令，一定要以一个Tab键作为开头。记住，make并不管命令是怎么工作的，他只管执行所定义的命令


# vpath

# 多目标

# 
