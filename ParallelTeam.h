/*

Name: Jason Durant

Course: Parallel & Cloud Programming

CRN: 39072

Assignment: Final Project
Date: 05/22/2019

*/

#ifndef ParallelTeam_H
#define ParalelTeam_H
#include "ComputeObj.cpp"
#include <string>

using namespace std;
class ParallelTeam{
	const int PARTITION_COUNT = 5;

	private:
		ComputeObj *computeObjects;
		int *numbers;
		int total;
		int paritionCount = 5;
		int **partitionArrays = new  int*[PARTITION_COUNT];
		string strFile;

	public:
		ParallelTeam(string strFile);

		int readBinaryFile();

		int binaryFileTotal();

		void paritionData();

		void startComputation();

};

#endif

