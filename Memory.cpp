/*

Name: Jason Durant

Course: Parallel & Cloud Programming

CRN: 39072

Assignment: ALU
Date: 03/04/2019

*/

#include "Memory.h"
#include <iostream>
using namespace std;

Memory::Memory(){
    setMemoryType('i',512);
}

Memory::Memory(char type){
    setMemoryType(type, 512);
}

void Memory::setMemoryType(char type, int count=512){
    MemoryType enumType = static_cast<MemoryType>(type); 
    memoryAddressLimit = count;

    switch(enumType){
        case INTEGERARR:
            selectedMemoryType = INTEGERARR;
            memoryArrays.intMemory = new int[count];
            break;
        case UNSIGNEDINTEGERARR:
            selectedMemoryType = UNSIGNEDINTEGERARR;
            memoryArrays.unsignedIntMemory = new unsigned int[count];
            break;
        case SIGNED64BITARR:
            selectedMemoryType = SIGNED64BITARR;
            memoryArrays.longMemory = new long[count];
            break;
        case UNSIGNED64BITARR:
            selectedMemoryType = UNSIGNED64BITARR;
            memoryArrays.unsignedLongMemory =  new unsigned long[count];
            break;
        case FLOAT32BITARR:
            selectedMemoryType = FLOAT32BITARR;
            memoryArrays.floatMemory = new float[count];
            break;
        case FLOAT64BITARR:
            selectedMemoryType = FLOAT64BITARR;
            memoryArrays.doubleMemory = new double[count];
            break;
    }
}
