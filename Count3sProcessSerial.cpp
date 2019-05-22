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

#include "Timer.h"

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


int main(){
	TimerNew timer;
	timer.start();
	int numbersTotal= Count3sProcessSerial::BinaryFileTotal("./threesData.bin",4);
	Count3sProcessSerial::ReadBinaryFile("./threesData.bin", numbers);
	Count3sProcessSerial::CountThrees(numbersTotal, numbers);

	timer.stop();
	double duration = timer.getElapsedTimeInMilliSec();
	printf("duration %.4f ms", duration);
}
