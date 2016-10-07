#include <phpcpp.h>
#include <iostream>

void myFunction(Php::Parameters &params)
{
    Php::out << "example output" << std::endl;
    Php::out << params[0] << std::endl;
	Php::Value example =params[1];
	std::map<std::string,Php::Value> ExampleMap = example.mapValue();

	//for map vaule
	std::map<std::string,Php::Value>::iterator it;
	for(it = ExampleMap.begin(); it != ExampleMap.end(); it++)  {  
        Php::out << it->first << "--->"; 
		Php::out <<(it->second).type() <<std::endl; 
    }  
   
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
       	extension.add<myFunction>("myFunction",{
            Php::ByVal("a", Php::Type::Numeric),
            Php::ByVal("b", "ExampleClass"),
            Php::ByVal("c", "OtherClass")
        }); 

        // @todo    add your own functions, classes, namespaces to the extension
        
        // return the extension
        return extension;
    }
}
