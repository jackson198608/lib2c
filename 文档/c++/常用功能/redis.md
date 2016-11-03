# 1.refer link
- https://github.com/redis/hiredis


# 2.依赖库安装方式
- git clone https://github.com/redis/hiredis.git
- cd hiredis
- make
- make install
- install中实现上做了下面的事情:

```
cp -a hiredis.h async.h read.h sds.h adapters /usr/local/include/hiredis
cp -a libhiredis.dylib /usr/local/lib/libhiredis.0.13.dylib
cd /usr/local/lib && ln -sf libhiredis.0.13.dylib libhiredis.dylib
cp -a libhiredis.a /usr/local/lib
mkdir -p /usr/local/lib/pkgconfig
cp -a hiredis.pc /usr/local/lib/pkgconfig
```

- 就是讲库文件以及需要的头文件放置的在系统中以便后续程序引入与查询

# 3.测试程序
- https://github.com/jackson198608/lib2c/tree/master/projects/testRedis

