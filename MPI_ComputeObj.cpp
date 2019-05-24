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
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <mpi.h>
#include "ComputeObj.cpp"


class MPI_ComputeObj: public ComputeObj{


	private:
		int teamCount = 0;
		int * numbers;
		int totalCount;
		executionEntryFunc defaultfunc;



	public:
		MPI_ComputeObj(int *currentNumbers, int total){
			numbers = currentNumbers;
			totalCount = total;
		}

		void createTeam(int n){

		}

		int getSizeOfTeam(){
			return teamCount;
		}

		void startAllTeamMembers(){
			int rank;
			int comm_sz;
			char** args;
			int arg = 0;
			int count = 0;
			int result = 0;
			MPI_Init(&arg, &args);
			MPI_Comm_size(MPI_COMM_WORLD, &comm_sz);
			MPI_Comm_rank(MPI_COMM_WORLD, &rank);
			int partition = totalCount / comm_sz;

			for(int i = 0; i < teamCount; i++){
				if (rank != 0){
					int currentCount = defaultfunc(numbers);
					MPI_Send(&currentCount, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);

				}
			}

			for (int i = 0; i < teamCount; i++){
				MPI_Recv(&count, 1, MPI_INT, i, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
				result += count;
			}
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
