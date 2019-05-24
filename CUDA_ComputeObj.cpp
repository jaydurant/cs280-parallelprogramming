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

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <assert.h>
#include <syslog.h>
#include <sys/types.h>
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <mpi.h>
#include "ComputeObj.cpp"


class CUDA_ComputeObj: public ComputeObj{


	private:
		int teamCount = 0;
		int * numbers;
		int totalCount;
		executionEntryFunc defaultfunc;



	public:
		CUDA_ComputeObj(int *currentNumbers, int total){
			numbers = currentNumbers;
			totalCount = total;
		}

		void createTeam(int n){

		}

		int getSizeOfTeam(){
			return teamCount;
		}

		void startAllTeamMembers(){

		}

		void lockSemaphoreInSet(int index){
		}

		void unlockSemaphoreSet(){

		}

		void unlockSempahoreInSet(int index){
		}

		void setAllSemaphoresInSet(unsigned short *values){
		}

		void createSemaphoreSet(int n){

		}

		void deleteSemaphoreSet(){
		}

		void waitForAllTeamMembers(){
		}

		void setEntryFunction(executionEntryFunc startFunc){
			defaultfunc = startFunc;
		}

		void setEntryFunction(int index, executionEntryFunc startFunc){
			defaultfunc = startFunc;
			int memberIndex = index;
		}
};
