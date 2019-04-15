/*

Name: Jason Durant

Course: Parallel & Cloud Programming

CRN: 39072

Assignment: ALU
Date: 03/04/2019

*/

#ifndef ALU_H
#define ALU_H
#include "RegisterSet.h"

class ALU{
    private:
        RegisterSet *registerSet;
    public:
        ALU();

        ALU(const RegisterSet &);

        ALU(char type, int count);

        template<class T>
        void LD(int registerIndex, T value){
            registerSet->set(registerIndex, value);
        }

        void ADD(int, int, int);

        void SUB(int, int, int);

        void MUL(int, int, int);

        void DIV(int, int, int);

        void STO();

};

#endif