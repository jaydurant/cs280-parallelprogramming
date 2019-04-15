/*

Name: Jason Durant

Course: Parallel & Cloud Programming

CRN: 39072

Assignment: ALU
Date: 03/04/2019

*/

#ifndef MEMORY_H
#define MEMORY_H
#include "IllegalArgumentException.h"


class Memory{

    enum MemoryType : char {
        INTEGERARR = 'i',
        UNSIGNEDINTEGERARR = 'u',
        SIGNED64BITARR = 'l',
        UNSIGNED64BITARR = 'n',
        FLOAT32BITARR = 'f',
        FLOAT64BITARR = 'd'
    };

    private:
        union MemoryArray{
            int *intMemory;
            unsigned int *unsignedIntMemory;
            long *longMemory;
            unsigned long *unsignedLongMemory;
            float *floatMemory;
            double *doubleMemory;
            char **charMemory;

        } memoryArrays;

        MemoryType selectedMemoryType;
        int memoryAddressLimit;
        void setMemoryType(char type, int count);

    public:
        Memory();

        Memory(char);

        template <class T>
        void write(unsigned int address, T value){
            if (address < memoryAddressLimit - 1 && address > 0 ){
                T * array;
                switch(selectedMemoryType){
                    case INTEGERARR:
                        array = (T*)memoryArrays.intMemory;
                        break;
                    case UNSIGNEDINTEGERARR:
                        array = (T*)memoryArrays.unsignedIntMemory;
                        break;
                    case SIGNED64BITARR:
                        array = (T*)memoryArrays.longMemory;
                        break;
                    case UNSIGNED64BITARR:
                        array = (T*)memoryArrays.unsignedLongMemory;
                        break;
                    case FLOAT32BITARR:
                        array = (T*)memoryArrays.floatMemory;
                        break;
                    case FLOAT64BITARR:
                        array = (T*)memoryArrays.doubleMemory;
                        break;
                }

                array[address] = value;
            }{
                throw IllegalArgumentException<int>(address);

            }
        }

        template <class T>
        T read(unsigned int address){
            T * array;

            if (address < memoryAddressLimit - 1 && address > 0 ){

                switch(selectedMemoryType){
                    case INTEGERARR:
                        array = (T*)memoryArrays.intMemory;
                        break;
                    case UNSIGNEDINTEGERARR:
                        array = (T*)memoryArrays.unsignedIntMemory;
                        break;
                    case SIGNED64BITARR:
                        array = (T*)memoryArrays.longMemory;
                        break;
                    case UNSIGNED64BITARR:
                        array = (T*)memoryArrays.unsignedLongMemory;
                        break;
                    case FLOAT32BITARR:
                        array = (T*)memoryArrays.floatMemory;
                        break;
                    case FLOAT64BITARR:
                        array = (T*)memoryArrays.doubleMemory;
                        break;
                }
                return array[address];
            }else{
              throw IllegalArgumentException<unsigned int>(address);  
            }

        }

};
#endif