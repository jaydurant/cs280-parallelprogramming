/*

Name: Jason Durant

Course: Parallel & Cloud Programming

CRN: 39072

Assignment: Timer

Date: 04/30/2019

*/

#include "Timer.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
using namespace std;


Timer::Timer(){
	startCount.tv_sec = startCount.tv_nsec = 0;
	endCount.tv_sec = endCount.tv_nsec = 0;
	stopped = 0;
	startTimeInMicroSec = 0;
	endTimeInMicroSec = 0;
}

void Timer::start(){
	stopped = 0;
	clock_gettime(CLOCK_MONOTONIC, &startCount);
}

void Timer::stop(){
	stopped = 1;
	clock_gettime(CLOCK_MONOTONIC, &endCount);
}

double Timer::getElapsedTime(){
	double dur = (endCount.tv_sec + 1.0e-9*endCount.tv_nsec) - (startCount.tv_sec + 1.0e-9*startCount.tv_nsec);
	return dur;
}

double Timer::getElapsedTimeInSec(){
	return this->getElapsedTime();
}

double Timer::getElapsedTimeInMilliSec(){
	double car = (1000 * endCount.tv_sec + 1.0e-6*endCount.tv_nsec);
	printf("%ld \n",endCount.tv_nsec);
	double boat = (1000 * startCount.tv_sec + 1.0e-6*endCount.tv_nsec);
	printf("%.4f \n", car);
	printf("%.4f \n", boat);

	double dur = (1000 * endCount.tv_sec + 1.0e-6*endCount.tv_nsec) - (1000 * startCount.tv_sec + 1.0e-6*startCount.tv_nsec);
	return dur;
}

double Timer::getElapsedTimeInMicroSec(){
	double car = (1000000 * endCount.tv_sec + endCount.tv_nsec);
	double boat = (1000000 * startCount.tv_sec + startCount.tv_nsec);
	printf("%.4f \n", car);
	printf("%.4f \n", boat);
	double dur = (1000000 * endCount.tv_sec + endCount.tv_nsec) - (1000000 * startCount.tv_sec + startCount.tv_nsec);
	return dur;
}
