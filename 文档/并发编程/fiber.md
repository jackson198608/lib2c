# 1.refer link
- https://en.wikipedia.org/wiki/Fiber_(computer_science)

# 2.定义
- 

# 3.和线程的异同
- 都需要共享地址
- 线程的调度方式:pre-emptive，需要第三方调度，决定是否停止当前，运行下一个
- fiber的调度方式: co-operative,需要自己决定，是否停止自己，运行下一个

# 4.fiber和coroutines
- 概念上是一致的
- coroutines是语言级别的construct,包含很多执行过程，调度组件等等内部实现
- fiber是系统级别的construct,更多被看成是coroutines的系统级实现

