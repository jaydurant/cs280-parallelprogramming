/*

Name: Jason Durant

Course: Parallel & Cloud Programming

CRN: 39072

Assignment: Count3sCL
Date: 04/28/2019

*/

#ifndef Count3sCL_H
#define Count3sCL_H
#include <string>


class Count3sCL{
    public:
		Count3sCL(){}

		static int BinaryFileTotal(std::string strFile, int bytes);
		static void ReadBinaryFile(std::string strFile, int*& numbers);
		static int CountThreesMid(int*& numbers, int start, int end);
		static void CountThrees(int sizeOfFile, int*& numbers);
		static int CountThreesPartial(int*& numbers, int size);
		static int* ReadPartialBinaryFile(std::string strFile, int start, int end);
};
#endif
