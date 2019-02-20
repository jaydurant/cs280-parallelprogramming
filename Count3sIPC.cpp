/*

Name: Jason Durant

Course: Parallel & Cloud Programming

CRN: 39072

Assignment: Count3sIPC

Date: 02/18/2019

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

#include "Count3sIPC.h"

using namespace std;

int AllocateSharedMemory(int n);
void* MapSharedMemory(int id);
int CreateSemaphoreSet(int n, unsigned short* vals);
void DeleteSemaphoreSet(int id);
void LockSemaphore(int id, int i);
void UnlockSemaphore(int id, int i);

#if !defined(__GNU_LIBRARY__) || defined(_SEM_SEMUN_UNDEFINED)
union semun
{
    int val;                // value for SETVAL
    struct semid_ds* buf;   // buffer for IPC_STAT, IPC_SET
    unsigned short*  array; // array for GETALL, SETALL
    struct seminfo*  __buf; // buffer for IPC_INFO
};
#endif

int Count3sIPC::BinaryFileTotal(string strFile, int num){
    	ifstream binaryFile;
		int size = 0;
		binaryFile.open(strFile, ios::in | ios::binary);
		binaryFile.seekg(0, ios::end);
		size =  binaryFile.tellg();
		return size;
}

void Count3sIPC::ReadBinaryFile(string strFile, int*& numbers){
        ifstream binaryFile;
        int size = 0;
        binaryFile.open(strFile, ios::in | ios::binary);
        binaryFile.seekg(0, ios::end);
        size =  binaryFile.tellg();

        numbers = new int[size/4];

        binaryFile.seekg(0, ios::beg);

        signed int data;
        int count = 0;
        while(binaryFile.tellg() < size){
            binaryFile.read((char*)&data, sizeof(data));
            if (sizeof(data) == 4){
            	numbers[count++] = data;
            }
        }
        binaryFile.close();
}


void Count3sIPC::CountThrees(int numbersTotal, int*& numbers){
	int count = 0;
	for (int i ; i < numbersTotal; i++){
		if (numbers[i] == 3){
			count++;
		}
	}

	cout << count << endl;
}

int  Count3sIPC::CountThreesMid(int*& numbers,int start, int end){
	int count = 0;
	for (int i = start ; i < end; i++){
		if (numbers[i] == 3){
			count++;
		}
	}

	return count;
}

int *numbers;
struct sharedStruc {
	int total;
};

enum{
	SEM_1
};

int main(int argc, char* argv[]){
	int sharedMemoryHandle;
	int idSemaphoreSetHandle;
	sharedStruc *buffer; //shared memory buffer

	unsigned short values[1];
	int semaphore;

	int total = Count3sIPC::BinaryFileTotal("./threesData.bin", 0);
	Count3sIPC::ReadBinaryFile("./threesData.bin", numbers);
	int totalNumbers = total / 4;


	sharedMemoryHandle = AllocateSharedMemory(50);
	buffer = (sharedStruc*) MapSharedMemory(sharedMemoryHandle);
	values[SEM_1] = 0;

	idSemaphoreSetHandle = CreateSemaphoreSet(1, values);

	(*buffer).total = 0;

	if (fork()){
		int total = Count3sIPC::CountThreesMid(numbers, 0, totalNumbers/3);

		UnlockSemaphore(idSemaphoreSetHandle, SEM_1);
		sharedStruc *heybuffer = (sharedStruc*) MapSharedMemory(sharedMemoryHandle);
		(*buffer).total += total;
		LockSemaphore(idSemaphoreSetHandle, SEM_1);

		exit(0);

	}
	else if(fork()){
		int total = Count3sIPC::CountThreesMid(numbers, totalNumbers/3, totalNumbers/3 * 2);

		UnlockSemaphore(idSemaphoreSetHandle, SEM_1);
		(*buffer).total += total;
		LockSemaphore(idSemaphoreSetHandle, SEM_1);

		exit(0);
	}
	else{
		int total = Count3sIPC::CountThreesMid(numbers, totalNumbers/3 * 2, totalNumbers);

		UnlockSemaphore(idSemaphoreSetHandle, SEM_1);
		 (*buffer).total += total;
		LockSemaphore(idSemaphoreSetHandle, SEM_1);
	}

	shmctl(sharedMemoryHandle, IPC_RMID, NULL);
	DeleteSemaphoreSet(idSemaphoreSetHandle);

	cout << (*buffer).total << endl;
	exit(0);
}

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

