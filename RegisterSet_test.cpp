/*

Name: Jason Durant

Course: Parallel & Cloud Programming

CRN: 39072

Assignment: RegisterSet
Date: 02/27/2019

*/
#include <iostream>
#include "RegisterSet.h"
#include "IllegalArgumentException.h"
using namespace std;

int main(){

    RegisterSet registerSet;

    for (int i = 1, y = 9; i < 9; i++, y--){
        registerSet.set<int>(i, y);
    }

    registerSet.displayData();

    registerSet.reset();

    registerSet.displayData();


    exit(0);
}