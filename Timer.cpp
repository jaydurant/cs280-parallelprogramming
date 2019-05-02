/*

Name: Jason Durant

Course: Parallel & Cloud Programming

CRN: 39072

Assignment: Timer

Date: 04/28/2019

*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "Timer.h"
#include <chrono>
using namespace std::chrono;

Timer::Timer() {
	startCount = 0;
	endCount = 0;
}

void Timer::start(){
	milliseconds ms = duration_cast< milliseconds >(
		    system_clock::now().time_since_epoch()
		);

	startCount = ms.count();
}

void Timer::stop(){
	milliseconds ms = duration_cast< milliseconds >(
		    system_clock::now().time_since_epoch()
		);

	endCount = ms.count();
}

int Timer::results(){
	return endCount - startCount;
}
Timer::~Timer() {
	// TODO Auto-generated destructor stub
}

