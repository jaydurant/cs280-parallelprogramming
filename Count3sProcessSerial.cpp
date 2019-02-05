/*

Name: Jason Durant

Course: Parallel & Cloud Programming

CRN: 39072

Assignment: CountThreesProcessSerial

Date: 01/28/2019

*/
#include<iostream>
#include<string>
#include<fstream>
#include<vector>
#include "Count3sProcessSerial.h"
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>


using namespace std;

int* numbers;


int Count3sProcessSerial::BinaryFileTotal(string strFile, int bytes){
    	ifstream binaryFile;
		int size = 0;
		binaryFile.open(strFile, ios::in | ios::binary);
		binaryFile.seekg(0, ios::end);
		size =  binaryFile.tellg();
		return size / bytes;
    }

void Count3sProcessSerial::ReadBinaryFile(string strFile, int*& numbers){
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

void Count3sProcessSerial::CountThrees(int numbersTotal, int*& numbers){
	int count = 0;
	for (int i ; i < numbersTotal; i++){
		if (numbers[i] == 3){
			count++;
		}
	}

	cout << count << endl;
}

int Count3sProcessSerial::CountThreesPartial(int start, int end, int*& numbers){
	int count = 0;

	for (int i ;i < end; i++){
		if (numbers[i] == 3){
			cout << count << endl;
			count++;
		}

	}
	return count;
}


int main(){
	int numbersTotal= Count3sProcessSerial::BinaryFileTotal("./threesData.bin", 4);
	Count3sProcessSerial::ReadBinaryFile("./threesData.bin", numbers);

	int start = 0;
	int step = 2;


	//int totalOne = Count3sProcessSerial::CountThreesPartial(start, numbersTotal / 2, numbers);

	pid_t pid = fork();
	if (pid == 0){
		int total = 0;
		int half = numbersTotal / 2;
		total = Count3sProcessSerial::CountThreesPartial(start, numbersTotal / 2, numbers);
		cout << numbersTotal << endl;
		cout << half << endl;
		cout << total << endl;
		cout << "child exiting" << endl;
		exit(total);
	}

	printf("I'm %d: myvar is \n", getpid());
	//cout << total << endl;
	int status = 0;
	pid_t childpid = wait(&status);
	int childReturnValue = WEXITSTATUS(status);
	cout << "child return value" << endl;
	printf("Return value was %d /n", childReturnValue);
}
