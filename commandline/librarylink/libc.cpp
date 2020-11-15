#include "libc.h"
#include "libd.h"
#include <iostream>


void addVarC()
{
    gVar += 10;
    std::cout<<"libc gvar:"<<gVar<<std::endl;
}