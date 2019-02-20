/*

Name: Jason Durant

Course: Parallel & Cloud Programming

CRN: 39072

Assignment: Count3sIPC

Date: 02/18/2019

*/

#ifndef Count3sIPC_H
#define Count3sIPC_H
#include <string>


class Count3sIPC{
    public:
		Count3sIPC(){}

		static int BinaryFileTotal(std::string strFile, int bytes);
		static void ReadBinaryFile(std::string strFile, int*& numbers);
		static int CountThreesMid(int*& numbers, int start, int end);
		static void CountThrees(int sizeOfFile, int*& numbers);
		static int CountThreesPartial(int*& numbers, int size);
		static int* ReadPartialBinaryFile(std::string strFile, int start, int end);
};
#endif
