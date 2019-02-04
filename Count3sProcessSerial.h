/*

Name: Jason Durant

Course: Parallel & Cloud Programming

CRN: 39072

Assignment: CountThreesProcessSerial

Date: 01/28/2019

*/

#ifndef Count3sProcessSerial_H
#define Count3sProcessSerial_H
#include <string>


class Count3sProcessSerial{
    public:
		Count3sProcessSerial(){}

		static int BinaryFileTotal(std::string strFile, int bytes);
		static void ReadBinaryFile(std::string strFile, int*& numbers);
		static void CountThrees(int sizeOfFile, int*& numbers);
};
#endif
