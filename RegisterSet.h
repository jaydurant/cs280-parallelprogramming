/*

Name: Jason Durant

Course: Parallel & Cloud Programming

CRN: 39072

Assignment: RegisterSet
Date: 02/27/2019

*/
#ifndef REGISTERSET_H
#define REGISTERSET_H
#include <iostream>
#include <string>
#include "IllegalArgumentException.h"
#include <typeinfo>

using namespace std;
template <class T>
class RegisterSet{
    enum RegisterType : char {
        INTEGERARR = 'i',
        UNSIGNEDINTEGERARR = 'u',
        SIGNED64BITARR = 'l',
        UNSIGNED64BITARR = 'n',
        FLOAT32BITARR = 'f',
        FLOAT64BITARR = 'd'
    };

    private:
        char currentRegisterType;
        char *registerFlags;
        short registerCount;
        RegisterType selectedRegister;
        
        union registers{
            int *intRegister;
            unsigned int *unsignedIntRegister;
            long *longRegister;
            unsigned long *unsignedLongRegister;
            float *floatRegister;
            double *doubleRegister;
            char **charRegister;

        } currentRegisters;

        void setRegisterType(char type, int count);

        template <class T>
        void setArrToZero(T * arr){
            for (int i = 1 ; i < registerCount; i++){
                arr[i] = 0;
            }
        }

        template <class T>
        void displayArrValues(T * arr){
            for (int i = 0 ; i < registerCount; i++){
                string displayString ="R";
                T value = arr[i];
                displayString += i < 10 ? ("0" + to_string(i)) : to_string(i);
                displayString += ": 0x" + to_string(arr[i]);
                displayString += " " + string(1, *typeid(value).name());
                cout << displayString << endl;
            }
        }

    public:
        // Constructors
        RegisterSet();
        RegisterSet(char type, int count);
        RegisterSet(char type, int size, int count);

        // class methods
        template <class T>
        void set(int registerIndex, T value){
            if (registerIndex > 0){
                T * array;
                switch(selectedRegister){
                    case INTEGERARR:
                        array = (T*)currentRegisters.intRegister;
                        break;
                    case UNSIGNEDINTEGERARR:
                        array = (T*)currentRegisters.unsignedIntRegister;
                        break;
                    case SIGNED64BITARR:
                        array = (T*)currentRegisters.longRegister;
                        break;
                    case UNSIGNED64BITARR:
                        array = (T*)currentRegisters.unsignedLongRegister;
                        break;
                    case FLOAT32BITARR:
                        array = (T*)currentRegisters.floatRegister;
                        break;
                    case FLOAT64BITARR:
                        array = (T*)currentRegisters.doubleRegister;
                        break;
                }

                array[registerIndex] = value;

                displayArrValues(array);
            }
            else{
                throw IllegalArgumentException<int>(registerIndex);
            }
        }

        template <class T>
        T get(int registerIndex){
            T * array;

            switch(selectedRegister){
                case INTEGERARR:
                    array = currentRegisters.intRegister;
                    break;
                case UNSIGNEDINTEGERARR:
                    array = currentRegisters.unsignedIntRegister;
                    break;
                case SIGNED64BITARR:
                    array = currentRegisters.longRegister;
                    break;
                case UNSIGNED64BITARR:
                    array = currentRegisters.unsignedLongRegister;
                    break;
                case FLOAT32BITARR:
                    array = currentRegisters.floatRegister;
                    break;
                case FLOAT64BITARR:
                    array = currentRegisters.doubleRegister;
                    break;
            }
            return array[registerIndex];
        }

        void reset();

        void displayData();
};

#endif