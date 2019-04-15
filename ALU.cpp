/*

Name: Jason Durant

Course: Parallel & Cloud Programming

CRN: 39072

Assignment: ALU
Date: 03/04/2019

*/
#include "ALU.h"
#include <iostream>
using namespace std;
#include "RegisterSet.h"

ALU::ALU(){
    registerSet = new RegisterSet();
}

ALU::ALU(const RegisterSet &registerSetObject){
    registerSet = (RegisterSet*) &registerSetObject;
}

ALU::ALU(char type, int count){
   registerSet = new RegisterSet(type, count);
}

/*
void ALU::ADD(int destRegisterIndex, int registerIndex1, int registerIndex2){

    registerSet->set(destRegisterIndex, (registerSet->get<int>(registerIndex1) + registerSet->get<int>(registerIndex2)) );
}

void ALU::SUB(int destRegisterIndex, int registerIndex1, int registerIndex2){

    registerSet->set(destRegisterIndex, (registerSet->get(registerIndex1) - registerSet->get(registerIndex2)));
}   


void ALU::MUL(int destRegisterIndex, int registerIndex1, int registerIndex2){
    registerSet->set(destRegisterIndex, (registerSet->get(registerIndex1) * registerSet->get(registerIndex2)));
}

void ALU::DIV(int destRegisterIndex, int registerIndex1, int registerIndex2){
    registerSet->set(destRegisterIndex, (registerSet->get(registerIndex1) / registerSet->get(registerIndex2)));
}
*/

