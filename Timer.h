/*

Name: Jason Durant

Course: Parallel & Cloud Programming

CRN: 39072

Assignment: Timer

Date: 04/30/2019

*/

#include <sys/time.h>
#include<time.h>


#ifndef TIMERNEW_H_
#define TIMERNEW_H_


class Timer {
	struct timespec startCount;
	struct timespec endCount;
	double startTimeInMicroSec;
	double endTimeInMicroSec;
	int stopped;

public:
	Timer();

	void start();
	void stop();
	double getElapsedTime();
	double getElapsedTimeInSec();
	double getElapsedTimeInMilliSec();
	double getElapsedTimeInMicroSec();
};

#endif
