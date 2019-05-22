/*

Name: Jason Durant

Course: Parallel & Cloud Programming

CRN: 39072

Assignment: Count3sMPI

Date: 04/14/2019

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
#include <mpi.h>
#include "Count3sMPI.h"
#include "Timer.h"

using namespace std;


int Count3sMPI::BinaryFileTotal(string strFile, int num){
    	ifstream binaryFile;
		int size = 0;
		binaryFile.open(strFile, ios::in | ios::binary);
		binaryFile.seekg(0, ios::end);
		size =  binaryFile.tellg();
		return size / num;
}

void Count3sMPI::ReadBinaryFile(string strFile, int*& numbers){
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


void Count3sMPI::CountThrees(int numbersTotal, int*& numbers){
	int count = 0;
	for (int i ; i < numbersTotal; i++){
		if (numbers[i] == 3){
			count++;
		}
	}

	cout << count << endl;
}

int  Count3sMPI::CountThreesMid(int*& numbers,int start, int end){
	int count = 0;
	for (int i = start ; i < end; i++){
		if (numbers[i] == 3){
			count++;
		}
	}

	return count;
}

int main(int argc, char* argv[]){
	TimerNew timer;
	timer.start();
	int rank;
	int *numbers;
	int comm_sz;
	int total = Count3sMPI::BinaryFileTotal("./threesData.bin", 4);
	Count3sMPI::ReadBinaryFile("./threesData.bin", numbers);
	int totalNumbers = total;

	int count = 0;
	int result = 0;

    //Expects number of processes to be 3
	MPI_Init(&argc, &argv);http://marketplace.eclipse.org/marketplace-client-intro?mpc_install=2235823
	MPI_Comm_size(MPI_COMM_WORLD, &comm_sz);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	int partition = totalNumbers / comm_sz;

	if (rank != 0){
		int current_partition = rank * partition;
		int end_partition = current_partition + partition > totalNumbers ? totalNumbers : current_partition + partition;
		int currentCount = Count3sMPI::CountThreesMid(numbers, current_partition, end_partition);
		MPI_Send(&currentCount, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
	}else{
		for (int i = 1; i < comm_sz; i++){
			MPI_Recv(&count, 1, MPI_INT, i, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
			result += count;MPI_Init
		}

		int rankZeroCount = Count3sMPI::CountThreesMid(numbers, rank, partition);

		cout << rankZeroCount + result << endl;
	}

	MPI_Finalize();
	timer.stop();
	float duration = timer.getElapsedTimeInMilliSec();
	printf("%.2f ms", duration);

	return 0;


}
