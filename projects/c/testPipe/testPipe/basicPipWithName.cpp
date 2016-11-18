//
//  basicPipeWithName.cpp
//  testPipe
//
//  Created by 周鹏远 on 16/11/18.
//  Copyright © 2016年 周鹏远. All rights reserved.
//

#include <iostream>
#include <sys/types.h>
#include <sys/stat.h>
#include "basicPipWithName.h"


void processOne(){

}

void processTwo(){

}


void testNamedPip(int type){
    if(type == 1){
        processOne();
    } else if(type==2){
        processTwo();
    }
 }

