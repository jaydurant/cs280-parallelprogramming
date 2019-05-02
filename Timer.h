/*
 * Timer.h
 *
 *  Created on: Oct 6, 2013
 *      Author: taxi
 */

#include <sys/time.h>
#include <time.h>

#ifndef TIMER_H_
#define TIMER_H_


class Timer {
    int startCount;
    int endCount;


public:
	Timer();

	void   start();
    void   stop();
    int results();

};

#endif /* Timer_H_ */
