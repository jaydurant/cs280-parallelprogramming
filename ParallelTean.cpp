/*

 */

#include "ParallelTeam.h"
#include <string>
#include <iostream>
#include <fstream>


using namespace std;

ParallelTeam::ParallelTeam(){
	this->strFile = "./threesData.bin";
}

ParallelTeam::ParallelTeam(string strFile){
	this->strFile = strFile;
}

int ParallelTeam::readBinaryFile(){
	ifstream binaryFile;
	int size = 0;
	binaryFile.open(strFile, ios::in | ios::binary);
	binaryFile.seekg(0, ios::end);
	size =  binaryFile.tellg();

	numbers = new int[size/4];
	total = numbers;

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

	return size;
}

void ParallelTeam::partitionData(){
	int partitionOffset  = total / PARTITION_COUNT;

	for (int i = 0; i < PARTITION_COUNT; i++){
		if (i != PARTITION_COUNT - 1){
			partitionArrays[i] = new int[partitionOffset];
		}else{
			partitionArrays[i] =  new int[ total - partitionOffset * i];
		}

	}
}

void ParallelTeam::startComputation(){

}
