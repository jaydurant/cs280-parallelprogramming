/*

Name: Jason Durant

Course: Parallel & Cloud Programming

CRN: 39072

Assignment: CountThreesProcessParallel

Date: 02/04/2019

*/


#ifndef Count3sProcessParallel_H
#define Count3sProcessParallel_H
#include <string>


class Count3sProcessParallel{
    public:
		Count3sProcessParallel(){}

		static int BinaryFileTotal(std::string strFile, int bytes);
		static void ReadBinaryFile(std::string strFile, int*& numbers);
		static void CountThrees(int sizeOfFile, int*& numbers);
		static int CountThreesPartial(int*& numbers, int size);
		static int* ReadPartialBinaryFile(std::string strFile, int start, int end);
};
#endif
