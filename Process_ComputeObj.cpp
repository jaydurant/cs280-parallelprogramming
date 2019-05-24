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
#include <syslog.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include "ComputeObj.cpp";

using namespace std;

#if !defined(__GNU_LIBRARY__) || defined(_SEM_SEMUN_UNDEFINED)
union semun
{
    int val;                // value for SETVAL
    struct semid_ds* buf;   // buffer for IPC_STAT, IPC_SET
    unsigned short*  array; // array for GETALL, SETALL
    struct seminfo*  __buf; // buffer for IPC_INFO
};
#endif

int AllocateSharedMemory(int n);
void* MapSharedMemory(int id);
int CreateSemaphoreSet(int n, unsigned short* vals);
void DeleteSemaphoreSet(int id);
void LockSemaphore(int id, int i);
void UnlockSemaphore(int id, int i);
void SetAllSemaphores(int id, unsigned short* vals);

struct sharedStruc {
	int total;
};


class Process_ComputeObj: public ComputeObj{
	enum{
		SEM_1
	};

	private:
		int teamCount = 0;
		int * numbers;
		int idSemaphoreSetHandle;
		executionEntryFunc defaultfunc;
		int sharedMemoryHandle;
		sharedStruc *buffer;
		Process_ComputeObj *computeObj;


	public:
		Process_ComputeObj(int *currentNumbers){
			numbers = currentNumbers;
		}

		void createTeam(int n){
			teamCount = n;
			sharedMemoryHandle = AllocateSharedMemory(50);
			buffer = (sharedStruc*) MapSharedMemory(sharedMemoryHandle);
			Process_ComputeObj objects[teamCount];
		}

		int getSizeOfTeam(){
			return teamCount;
		}

		void startAllTeamMembers(){
			for (int i = 0; i < teamCount ;i++){

				if(fork()){
					unlockSempahoreInSet(i);
					(*buffer).total += numbers;
					lockSemaphoreInSet(i);
					exit(0);
				}
			}
		}

		void lockSemaphoreInSet(int index){
			LockSemaphore(idSemaphoreSetHandle, index);
		}

		void unlockSemaphoreSet(){
			for (int i= 0 ; i < teamCount; i++){
				unlockSempahoreInSet(i);
			}
		}

		void unlockSempahoreInSet(int index){
			UnlockSemaphore(idSemaphoreSetHandle, index);
		}

		void setAllSemaphoresInSet(unsigned short *values){
			SetAllSemaphores(idSemaphoreSetHandle, values);
		}

		void createSemaphoreSet(int n){
			unsigned short values[1];
			values[SEM_1] = 0;
			idSemaphoreSetHandle = CreateSemaphoreSet(n, values);
		}

		void deleteSemaphoreSet(){
			DeleteSemaphoreSet(idSemaphoreSetHandle);
		}

		void waitForAllTeamMembers(){
			shmctl(sharedMemoryHandle, IPC_RMID, NULL);
		}

		void setEntryFunction(executionEntryFunc startFunc){
			defaultfunc = startFunc;
		}

		void setEntryFunction(int index, executionEntryFunc startFunc){
			defaultfunc = startFunc;
			int memberIndex = index;
		}
};

/**
 * Allocates a shared memory segment.
 *
 * @param  n  Size (in bytes) of chunk to allocate.
 * @return Id of shared memory chunk.
 */
int AllocateSharedMemory(int n)
{
    assert(n > 0); /* Idiot-proof the call. */
    return shmget(0, n, IPC_CREAT | SHM_R | SHM_W);
}
/**
 * Maps a shared memory segment onto our address space.
 *
 * @param  id  Shared memory block to map.
 * @return Address of mapped block.
 */

void* MapSharedMemory(int id)
{
    void* addr;
    assert(id != 0); /* Idiot-proof the call. */
    addr = shmat(id, NULL, 0);
    /* shmctl(id, IPC_RMID, NULL); ...and mark it destroyed. */
    return addr;
}


void SetAllSemaphores(int id, unsigned short * vals)
{
    union semun arg;
    assert(vals != NULL);
    arg.array = vals;
    semctl(id, 0, SETALL, arg);
}


/**
 * Creates a new semaphore set.
 *
 * @param  n     Number of semaphores in set.
 * @param  vals  Default values to start off with.
 * @return Id of semaphore set.
 */
int CreateSemaphoreSet(int n, unsigned short * vals)
{
    union semun arg;
    int id;
    assert(n > 0);        /* You need at least one! */
    assert(vals != NULL); /* And they need initialising! */
    id = semget(IPC_PRIVATE, n, SHM_R | SHM_W);
    arg.array = vals;
    semctl(id, 0, SETALL, arg);
return id;

}

/**
 * Frees up the given semaphore set.
 *
 * @param  id  Id of the semaphore group.
 */
void DeleteSemaphoreSet(int id)
{
    if (semctl(id, 0, IPC_RMID, NULL) == -1)
    {
        perror("Error releasing semaphore!");
        exit(EXIT_FAILURE);
    }
}
/**
 * Locks a semaphore within a semaphore set.
 *
 * @param  id  Semaphore set it belongs to.
 * @param  i   Actual semaphore to lock.
 *
 * @note If it’s already locked, you’re put to sleep.
 */
void LockSemaphore(int id, int i)
{
    struct sembuf sb;
    sb.sem_num = i;
    sb.sem_op = -1;
    sb.sem_flg = SEM_UNDO;
    semop(id, &sb, 1);
    }
/**
 * Unlocks a semaphore within a semaphore set.
 *
 * @param  id  Semaphore set it belongs to.
 * @param  i   Actual semaphore to unlock.
 */
void UnlockSemaphore(int id, int i)
{
	struct sembuf sb;
	sb.sem_num = i;
	sb.sem_op = 1;
	sb.sem_flg = SEM_UNDO;
	semop(id, &sb, 1);
}
