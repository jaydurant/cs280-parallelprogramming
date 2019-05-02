/*

Name: Jason Durant

Course: Parallel & Cloud Programming

CRN: 39072

Assignment: Count3sMPI
Date: 04/14/2019

*/

#ifndef Count3sMPI_H
#define Count3sMPI_H
#include <string>


class Count3sMPI{
    public:
		Count3sMPI(){}

		static int BinaryFileTotal(std::string strFile, int bytes);
		static void ReadBinaryFile(std::string strFile, int*& numbers);
		static int CountThreesMid(int*& numbers, int start, int end);
		static void CountThrees(int sizeOfFile, int*& numbers);
		static int CountThreesPartial(int*& numbers, int size);
		static int* ReadPartialBinaryFile(std::string strFile, int start, int end);
};
#endif
