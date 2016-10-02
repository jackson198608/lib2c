# 1.referlink
## 1.1 百度经验
- http://jingyan.baidu.com/album/f96699bbcb77a0894e3c1b22.html?picindex=8



# 2.具体步骤
## 2.1 编译好php文件，放在/usr/local/php下

## 2.2 进入源代码目录的ext目录
- ./ext_skel -extname=jExt
- ![demo](http://b.hiphotos.baidu.com/exp/w=480/sign=2854f02fc25c1038247ecfca8211931c/8435e5dde71190efb7c262eaca1b9d16fdfa60ce.jpg "logo图片")

## 2.3 查看生成的php扩展目录
- cd ext & ls jExt
- ![demo](http://e.hiphotos.baidu.com/exp/w=480/sign=559b771eb451f819f1250242eab54a76/503d269759ee3d6d397276fe47166d224f4ade4b.jpg "logo图片")

## 2.4 修改configure.m4文件，取消注释
- 取消PHP_ARG_WITH里面的三行
- ![demo](http://b.hiphotos.baidu.com/exp/w=480/sign=31fcceff553d26972ed3095565fbb24f/14ce36d3d539b600abe3fc82ed50352ac65cb7d2.jpg "logo图片")
- ![demo](http://h.hiphotos.baidu.com/exp/w=480/sign=fe7b1ffcd32a60595210e0121834342d/adaf2edda3cc7cd92264c7ec3d01213fb80e91be.jpg "logo图片")

## 2.5 编辑头文件
- 打开头文件，加入HelloWorld方法声明

- ![demo](http://c.hiphotos.baidu.com/exp/w=480/sign=08ba1f36cc95d143da76e52b43f08296/8ad4b31c8701a18bcdcbe17a9a2f07082838fee7.jpg "header")

- ![demo](http://e.hiphotos.baidu.com/exp/w=480/sign=691a70053ef33a879e6d0112f65c1018/b8389b504fc2d562391623d8e31190ef76c66ced.jpg "header")


## 2.6 编辑源代码文件
- 在zend_function_entry中加入HelloWorld的声明，告诉外部php有什么api
- ![demo](http://c.hiphotos.baidu.com/exp/w=480/sign=66dc480f1dd8bc3ec60807c2b28ba6c8/d31b0ef41bd5ad6ed79999df85cb39dbb6fd3ca6.jpg "test")

- 加入HelloWolrd方法实现代码
- ![demo](http://h.hiphotos.baidu.com/exp/w=480/sign=2506841369224f4a5799721b39f69044/342ac65c103853436c0f75149713b07ecb8088c7.jpg "test")

## 2.7 phpize生成框架文件
```
cd ext/jExt
phpize
```

## 2.8 configue
```
cd ext/jExt
./configure --with-php-config=/usr/local/php/bin/php-config
```

## 2.9 编译生成so文件
```
 make
 make install
```

# 3 php.ini中添加扩展,并使用
- extension=jExt.so

```
<?php
        HelloWorld();
?>
```


















