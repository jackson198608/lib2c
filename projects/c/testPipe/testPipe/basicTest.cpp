//
//  main.cpp
//  testPipe
//
//  Created by 周鹏远 on 16/11/18.
//  Copyright © 2016年 周鹏远. All rights reserved.
//

#include <iostream>
#include <unistd.h>
#include "basicPipWithName.h"
#include <string.h>


void testPipBlock(){
    std::cout<<"begin\n";
    int Pipe[2];
    pipe(Pipe);
    pid_t pid;
    
    pid=fork();
    if(pid >0){
        char buf[10];
        memset(buf,0,10);
        // in the father process
        for(int i=0;i<10;i++){
            std::cout<<"father:"<<i<<std::endl;
            write(Pipe[1], "hi" , 2);
        }
    
        
    }else if(pid==0){
        // in the child process
        char buf[10];
        
        for(int i=0;i<10;i++){
            memset(buf, 0, 10);
            std::cout<<"child:"<<i;
            read(Pipe[0], buf,2);
            std::cout<<buf<<"\n";
            
        }
        
    }
    
    waitpid(pid, NULL, 0);    
}

void testPipNonBlock(){
        //todo
}

int main(int argc, const char * argv[]) {
    
    const char* type=argv[1];
    if(strcmp(type, "0")==0){
        testPipBlock();
    } else if(strcmp(type, "1")==0){
        std::cout<<"1"<<std::endl;
        testNamedPip(1);
    } else if(strcmp(type, "2")==0){
        std::cout<<"2"<<std::endl;

        testNamedPip(2);
    }

    return 0;
}

