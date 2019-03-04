/*

Name: Jason Durant

Course: Parallel & Cloud Programming

CRN: 39072

Assignment: RegisterSet
Date: 02/27/2019

*/

#include "RegisterSet.h"
#include <iostream>
using namespace std;


RegisterSet::RegisterSet(){
    setRegisterType('i', 9);
}

RegisterSet::RegisterSet(char type, int count){
    setRegisterType(type, count);
}

RegisterSet::RegisterSet(char type, int size, int count){
    if (type == 'b'){
         char array[size][count];
        currentRegisters.charRegister = (char**)array;
    }
}

void RegisterSet::setRegisterType(char type, int count=9){
    RegisterType enumType = static_cast<RegisterType>(type); 
    registerCount = count;

    switch(enumType){
        case INTEGERARR:
            selectedRegister = INTEGERARR;
            currentRegisters.intRegister = new int[count];
            displayArrValues(currentRegisters.intRegister);
            break;
        case UNSIGNEDINTEGERARR:
            selectedRegister = UNSIGNEDINTEGERARR;
            currentRegisters.unsignedIntRegister = new unsigned int[count];
            displayArrValues(currentRegisters.unsignedIntRegister);
            break;
        case SIGNED64BITARR:
            selectedRegister = SIGNED64BITARR;
            currentRegisters.longRegister = new long[count];
            displayArrValues(currentRegisters.longRegister);
            break;
        case UNSIGNED64BITARR:
            selectedRegister = UNSIGNED64BITARR;
            currentRegisters.unsignedLongRegister =  new unsigned long[count];
            displayArrValues(currentRegisters.unsignedLongRegister);
        case FLOAT32BITARR:
            selectedRegister = FLOAT32BITARR;
            currentRegisters.floatRegister = new float[count];
            displayArrValues(currentRegisters.floatRegister);
        case FLOAT64BITARR:
            selectedRegister = FLOAT64BITARR;
            currentRegisters.doubleRegister = new double[count];
            displayArrValues(currentRegisters.doubleRegister);
    }
}

 void RegisterSet::reset(){
    switch(selectedRegister){
        case INTEGERARR:
            setArrToZero(currentRegisters.intRegister);
            break;
        case UNSIGNEDINTEGERARR:
            setArrToZero(currentRegisters.unsignedIntRegister);
            break;
        case SIGNED64BITARR:
            setArrToZero(currentRegisters.longRegister);
            break;
        case UNSIGNED64BITARR:
            setArrToZero(currentRegisters.unsignedLongRegister);
            break;
        case FLOAT32BITARR:
            setArrToZero(currentRegisters.floatRegister);
            break;
        case FLOAT64BITARR:
            setArrToZero(currentRegisters.doubleRegister);
            break;
    }
 }

void RegisterSet::displayData(){
    switch(selectedRegister){
        case INTEGERARR:
            displayArrValues(currentRegisters.intRegister);
            break;
        case UNSIGNEDINTEGERARR:
            displayArrValues(currentRegisters.unsignedIntRegister);
            break;
        case SIGNED64BITARR:
            displayArrValues(currentRegisters.longRegister);
            break;
        case UNSIGNED64BITARR:
            displayArrValues(currentRegisters.unsignedLongRegister);
            break;
        case FLOAT32BITARR:
            displayArrValues(currentRegisters.floatRegister);
            break;
        case FLOAT64BITARR:
            displayArrValues(currentRegisters.doubleRegister);
            break;
    }
}