//
//  main.cpp
//  testPipe
//
//  Created by 周鹏远 on 16/11/18.
//  Copyright © 2016年 周鹏远. All rights reserved.
//

#include <iostream>
#include <unistd.h>

int main(int argc, const char * argv[]) {
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
            read(Pipe[0], buf,sizeof(buf));
            std::cout<<"father: "<<buf<<std::endl;
        }
    
        
    }else if(pid==0){
        // in the child process
        char buf[10];
        
        for(int i=0;i<10;i++){
            memset(buf, 0, 10);
            std::cout<<"child:"<<i<<std::endl;
            read(Pipe[0], buf,sizeof(buf));
            std::cout<<"child: "<<buf<<std::endl;
            
        }
        
    }
    
    waitpid(pid, NULL, 0);
    

    return 0;
}
