# 相关链接
- http://www.php-cpp.com/documentation/install

# 1.install
```
	git clone https://github.com/CopernicaMarketingSoftware/PHP-CPP-LEGACY   (for php5.*)
	make
	make install
```

# 2. hello world
## 2.1 下载框架文件
```
	curl -O http://www.php-cpp.com/EmptyExtension.tar.gz	
```

## 2.2 框架自定义内容
### 2.2.1 Makefile NAME
- 指定生成扩展文件名

### 2.2.2 Makefile INI_DIR
- 指定make install拷贝扩展自己的ini文件到哪个路径中

## 2.3 源代码文件
```c++
#include <phpcpp.h>
#include <iostream>

void myFunction()
{
    Php::out << "example output" << std::endl;
}

/**
 *  tell the compiler that the get_module is a pure C function
 */
extern "C" {
    
    /** 
     *  Function that is called by PHP right after the PHP process
     *  has started, and that returns an address of an internal PHP
     *  strucure with all the details and features of your extension
     *
     *  @return void*   a pointer to an address that is understood by PHP
     */
    PHPCPP_EXPORT void *get_module() 
    {   
        // static(!) Php::Extension object that should stay in memory
        // for the entire duration of the process (that's why it's static)
        static Php::Extension extension("yourextension1", "1.0");
        extension.add<myFunction>("myFunction"); 

        // @todo    add your own functions, classes, namespaces to the extension
    
        // return the extension
        return extension;
    }   
}
```


