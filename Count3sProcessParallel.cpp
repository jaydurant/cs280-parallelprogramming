/*

Name: Jason Durant

Course: Parallel & Cloud Programming

CRN: 39072

Assignment: CountThreesProcessParallel

Date: 02/04/2019

*/

#include<iostream>
#include<string>
#include<fstream>
#include<vector>
#include "Count3sProcessParallel.h"
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>

#include "Timer.h"


using namespace std;

int* numbers;


int Count3sProcessParallel::BinaryFileTotal(string strFile, int bytes){
    	ifstream binaryFile;
		int size = 0;
		binaryFile.open(strFile, ios::in | ios::binary);
		binaryFile.seekg(0, ios::end);
		size =  binaryFile.tellg();
		return size;
}

void Count3sProcessParallel::ReadBinaryFile(string strFile, int*& numbers){
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

int* Count3sProcessParallel::ReadPartialBinaryFile(string strFile, int start, int end){
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

void Count3sProcessParallel::CountThrees(int numbersTotal, int*& numbers){
	int count = 0;
	for (int i ; i < numbersTotal; i++){
		if (numbers[i] == 3){
			count++;
		}
	}

	cout << count << endl;
}

int Count3sProcessParallel::CountThreesPartial(int*& numbers, int size){
	int count = 0;
	for (int i = 0 ;i < size; i++){
		if (numbers[i] == 3){
			count++;
		}

	}
	return count;
}


int main(){
	TimerNew timer;
	timer.start();

	int totalSize= Count3sProcessParallel::BinaryFileTotal("./threesData.bin", 4);
	int start = 0;
	int midpoint = totalSize / 2;

	int* firstHalf = Count3sProcessParallel::ReadPartialBinaryFile("./threesData.bin", start, midpoint);
	int result = Count3sProcessParallel::CountThreesPartial(firstHalf, midpoint / 4);

	start = midpoint;
	midpoint = totalSize;

	pid_t pid = fork();

	if (pid == 0){

		int* secondHalf = Count3sProcessParallel::ReadPartialBinaryFile("./threesData.bin", start, midpoint);
		result += Count3sProcessParallel::CountThreesPartial(secondHalf, (midpoint -start) / 4);
		cout << result << endl;
		exit(0);
	}


	wait(NULL);

	timer.stop();

	float duration = timer.getElapsedTimeInMilliSec();
	printf("%.4f ms", duration);
}
