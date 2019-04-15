/*

Name: Jason Durant

Course: Parallel & Cloud Programming

CRN: 39072

Assignment: ALU
Date: 03/04/2019

*/
#include <iostream>
#include "ALU.h"
#include "IllegalArgumentException.h"
using namespace std;

int main(){
    ALU alu;

    alu.LD(1, 123456);

    alu.LD(2, 54321);

    alu.ADD(3, 1, 2);

    alu.LD(4, 8);
    alu.LD(5, 7);

    alu.SUB(6, 4, 5);
    alu.ADD(7, 6, 3);
}