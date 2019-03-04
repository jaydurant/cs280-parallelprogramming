/*

Name: Jason Durant

Course: Parallel & Cloud Programming

CRN: 39072

Assignment: RegisterSet
Date: 02/27/2019

*/
#include "IllegalArgumentException.h"
template <class T>
IllegalArgumentException<T>::IllegalArgumentException(T newValue){
    value = newValue;
}
template <class T>
T IllegalArgumentException<T>::getValue(){
    return value;
}