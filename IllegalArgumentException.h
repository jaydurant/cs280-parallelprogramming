/*

Name: Jason Durant

Course: Parallel & Cloud Programming

CRN: 39072

Assignment: RegisterSet
Date: 02/27/2019

*/
#ifndef ILLEGALARGUMENT_H
#define ILLEGALARGUMENT_H

template <class T>
class IllegalArgumentException{
    private:
        T value;

    public:
        IllegalArgumentException(T newValue);
        T getValue();
};

#endif