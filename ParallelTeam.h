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

Assignment: Count3sIPC

Date: 05/22/2019
*/

#ifndef ParallelTeam_H
#define ParalelTeam_H
#include "ComputeObj.cpp"
#include <string>

using namespace std;

class ParallelTeam{


	private:
		ComputeObj *computeObjects;
		const int PARTITION_COUNT = 5;
		int *numbers;
		int total = 0;
		int paritionCount = 5;
		int **partitionArrays = new  int*[PARTITION_COUNT];
		string strFile;

	public:
		ParallelTeam(string strFile);

		ParallelTeam();

		int readBinaryFile();

		void partitionData();

		void startComputation();

};

#endif

