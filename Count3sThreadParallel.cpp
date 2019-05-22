/*

Name: Jason Durant

Course: Parallel & Cloud Programming

CRN: 39072

Assignment: CountThreesThreadParallel

Date: 02/11/2019

*/

#include "Count3sThreadParallel.h"

#include <pthread.h>
#include<iostream>
#include<string>
#include<fstream>
#include<vector>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>

#include "Timer.h"


using namespace std;

int* numbers;

typedef struct{
	int numbersTotal;
	long sum;
} THREESUMDATA;

#define NUMTHREADS 8
	THREESUMDATA threedatastr;
	pthread_t callThd[NUMTHREADS];
	pthread_mutex_t mutexthreesum;

int Count3sThreadParallel::BinaryFileTotal(string strFile, int bytes){
    	ifstream binaryFile;
		int size = 0;
		binaryFile.open(strFile, ios::in | ios::binary);
		binaryFile.seekg(0, ios::end);
		size =  binaryFile.tellg();
		return size / bytes;
}

void Count3sThreadParallel::ReadBinaryFile(string strFile, int*& numbers){
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

int* Count3sThreadParallel::ReadPartialBinaryFile(string strFile, int start, int end){
        ifstream binaryFile;
        binaryFile.open(strFile, ios::in | ios::binary);

        int* numbers = new int[(end - start)/4];

        binaryFile.seekg(start, ios::beg);

        signed int data;
        int count = 0;
        while(binaryFile.tellg() < end){
            binaryFile.read((char*)&data, sizeof(data));
            if (sizeof(data) == 4){
            	numbers[count++] = data;
            }
        }
        binaryFile.close();

        return numbers;
}

void Count3sThreadParallel::CountThrees(int numbersTotal, int*& numbers){
	int count = 0;
	for (int i ; i < numbersTotal; i++){
		if (numbers[i] == 3){
			count++;
		}
	}

	cout << count << endl;
}

int Count3sThreadParallel::CountThreesPartial(int*& numbers, int start, int end){
	cout << start << endl;
	int count = 0;
	for (int i = start ; i < end; i++){
		if (numbers[i] == 3){
			count++;
		}

	}

	return count;
}

void *Count3sThreadParallel::CountThreesPartialThread(void *arg){
	int start, end;
	long offset = (long)arg;
	int sum = 0;
	start = (threedatastr.numbersTotal / NUMTHREADS) * offset;
	end = start + (threedatastr.numbersTotal / NUMTHREADS);

	if (end > threedatastr.numbersTotal){
		end = threedatastr.numbersTotal;
	}

	sum = Count3sThreadParallel::CountThreesPartial(numbers, start, end);

	pthread_mutex_lock(&mutexthreesum);
	threedatastr.sum += sum;
	pthread_mutex_unlock(&mutexthreesum);
	pthread_exit((void*) 0);

}


int main(){
	threedatastr.numbersTotal = 0;
	threedatastr.sum = 0;
	TimerNew timer;
	timer.start();

	int totalSize= Count3sThreadParallel::BinaryFileTotal("./threesData.bin", 4);
	Count3sThreadParallel::ReadBinaryFile("./threesData.bin", numbers);
	threedatastr.numbersTotal = totalSize;

	void *status;
	pthread_attr_t attr;


	pthread_mutex_init(&mutexthreesum, NULL);
	pthread_attr_init(&attr);
	pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);

	for(long i = 0; i < NUMTHREADS ; i++){
		cout << i << endl;
		pthread_create(&callThd[i], &attr, Count3sThreadParallel::CountThreesPartialThread, (void *) i);
	}

	pthread_attr_destroy(&attr);

	for(int i = 0; i < NUMTHREADS ; i++){
		pthread_join(callThd[i], &status);
	}

	cout << threedatastr.sum << endl;
	pthread_mutex_destroy(&mutexthreesum);
	timer.stop();
	double duration = timer.getElapsedTimeInMilliSec();

	printf("%.4f ms", duration);
	pthread_exit(NULL);


}
