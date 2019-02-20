/*

Name: Jason Durant

Course: Parallel & Cloud Programming

CRN: 39072

Assignment: CountThreesThreadParallel
Date: 02/11/2019

*/


#ifndef Count3sThreadParallel_H
#define Count3sThreadParallel_H
#include <string>


class Count3sThreadParallel{
    public:
		Count3sThreadParallel(){}

		static int BinaryFileTotal(std::string strFile, int bytes);
		static void ReadBinaryFile(std::string strFile, int*& numbers);
		static void CountThrees(int sizeOfFile, int*& numbers);
		static int CountThreesPartial(int*& numbers, int start, int end);
		static int* ReadPartialBinaryFile(std::string strFile, int start, int end);
		static void *CountThreesPartialThread(void *arg);
};
#endif
