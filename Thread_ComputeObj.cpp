/*

Name: Jason Durant

Course: Parallel & Cloud Programming

CRN: 39072

Assignment: Final Project
Date: 05/22/2019

/*

Name: Jason Durant

Course: Parallel & Cloud Programming

CRN: 39072

Assignment: Project Final

Date: 05/22/2019
*/

#include "ComputeObj.cpp";
#include <pthread.h>
#include<iostream>
#include<string>
#include<fstream>
#include<vector>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include "semaphore.h"


class Thread_ComputeObj : public ComputeObj{

	private:
		int teamCount = 0;
		int * numbers;
		void *status;
		pthread_t *callThd;
		pthread_attr_t attr;
		pthread_mutex_t mutexthreesum;
		sem_t *sempahoreSet;
		executionEntryFunc defaultfunc;


	public:
		Thread_ComputeObj(int *currentNumbers){
			numbers = currentNumbers;
		}


		void createTeam(int n){
			teamCount = n;

			pthread_mutex_init(&mutexthreesum, NULL);
			pthread_attr_init(&attr);

			pthread_t *threads = new pthread_t[teamCount];
			callThd = threads;
		}

		int getSizeOfTeam(){
			return teamCount;
		}

		void startAllTeamMembers(){
			for (int i = 0; i < teamCount; i++){
				pthread_create(&callThd[i], &attr, defaultfunc, (void * ) i );
			}

			pthread_attr_destroy(&attr);

			pthread_exit(NULL);
		}

		void lockSemaphoreInSet(int index){
			sem_wait(&semaphoreSet[index]);
		}

		void unlockSempahoreInSet(int index){
			sem_post(&sempahoreSet[index]);
		}

		void unlockSemaphoreSet(){
			for (int i = 0; i < teamCount; i++){
				sem_post(&sempahoreSet[i]);
			}
		}

		void setAllSemaphoresInSet(unsigned short *values){
			for (int i = 0; i < teamCount;i++){
				sem_init(&sempahoreSet[i], 0, values);
			}
		}

		void createSemaphoreSet(int n){
			sem_t *semaphores =  new sem_t[teamCount];

			sempahoreSet = semaphores;

		}

		void deleteSemaphoreSet(){
			for (int i = 0;i < teamCount ; i++){
				sem_destroy(&semaphoreSet[i]);
			}
			pthread_attr_destroy(&attr);

		}

		void waitForAllTeamMembers(){
			pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);
		}

		void setEntryFunction(executionEntryFunc startFunc){
			defaultfunc = startFunc;
		}

		void setEntryFunction(int index, executionEntryFunc startFunc){
			defaultfunc = startFunc;
			int memberIndex = index;
		}

};
