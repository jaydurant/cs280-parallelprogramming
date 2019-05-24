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

#include "ParallelTeam.h"
#include <string>
#include <iostream>
#include <fstream>
#include "ComputeObj.cpp"
#include "Thread_ComputeObj.cpp"
#include "MPI_ComputeObj.cpp"
#include "OpenCL_ComputeObj.cpp"
#include "PROCESS_ComputeObj.cpp"
#include "CUDA_ComputeObj.cpp"

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

	ComputeObj **dynamic_array = new ComputeObj*[PARTITION_COUNT];
	dynamic_array[0] = new Thread_ComputeObj(partitionArrays[0]);
	dynamic_array[1] = new MPI_ComputeObj(partitionArrays[1]);
	dynamic_array[2] = new Process_ComputeObj(partitionArrays[2]);
	dynamic_array[3] = new OpenCL_ComputeObj(partitionArrays[3]);
	dynamic_array[4] = new CUDA_ComputeObj(partitionArrays[4]);

}


int main(int argc, char* argv[]){
	ParallelTeam team;


	team.readBinaryFile();
	team.partitionData();

	team.startComputation();


}
