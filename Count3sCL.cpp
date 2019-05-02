/*

Name: Jason Durant

Course: Parallel & Cloud Programming

CRN: 39072

Assignment: Count3sCL

Date: 04/28/2019

*/

#define __CL_ENABLE_EXCEPTIONS
#define CL_TARGET_OPENCL_VERSION 200
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <assert.h>
#include <syslog.h>
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include "CL/cl.hpp"

#include "Count3sCL.h"

using namespace std;


int Count3sCL::BinaryFileTotal(string strFile, int num){
    	ifstream binaryFile;
		int size = 0;
		binaryFile.open(strFile, ios::in | ios::binary);
		binaryFile.seekg(0, ios::end);
		size =  binaryFile.tellg();
		return size / num;
}

void Count3sCL::ReadBinaryFile(string strFile, int*& numbers){
        ifstream binaryFile;
        int size = 0;
        binaryFile.open(strFile, ios::in | ios::binary);
        binaryFile.seekg(0, ios::end);
        size =  binaryFile.tellg();

        numbers = new int[size/4];

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
}


void Count3sCL::CountThrees(int numbersTotal, int*& numbers){
	int count = 0;
	for (int i ; i < numbersTotal; i++){
		if (numbers[i] == 3){
			count++;
		}
	}

	cout << count << endl;
}

int  Count3sCL::CountThreesMid(int*& numbers,int start, int end){
	int count = 0;
	for (int i = start ; i < end; i++){
		if (numbers[i] == 3){
			count++;
		}
	}

	return count;
}

int main(int argc, char* argv[]){
		try{
		int *numbers;
		int comm_sz;
		int total = Count3sCL::BinaryFileTotal("./threesData.bin", 4);
		Count3sCL::ReadBinaryFile("./threesData.bin", numbers);
		int totalNumbers = total;

		int count = 0;
		int result = 0;

	    //get all platforms (drivers)
	    //get all platforms (drivers)
	    std::vector<cl::Platform> all_platforms;
	    cl::Platform::get(&all_platforms);
	    if(all_platforms.size()==0){
	        exit(1);
	    }
	    cl::Platform default_platform=all_platforms[1];

	    //get default device of the default platform
	    std::vector<cl::Device> all_devices;
	    default_platform.getDevices(CL_DEVICE_TYPE_ALL, &all_devices);
	    if(all_devices.size()==0){
	        exit(1);
	    }
	    cl::Device default_device=all_devices[0];

	    cl::Context context({default_device});

	    cl::Program::Sources sources;

	    // kernel calculates for each element C=A+B
	    std::string kernel_code=
	            "   void kernel count3s(global const int* A, global int* C, const int i){       "
	            "       int count = 0;"
	    		"       int id = get_global_id(0);              "
	    		"       for(int z = id * i ;z < (i * id + i ) ; z++){"
	            "			if(A[z] == 3){count++;}	"
	            "       }                            "
	            "       C[get_global_id(0)] = count;          "
	            "   }                                                                                 ";
	    sources.push_back({kernel_code.c_str(),kernel_code.length()});

	    cl::Program program(context,sources);
	    if(program.build({default_device})!=CL_SUCCESS){
	        exit(1);
	    }

	    // create buffers on the device
	    cl::Buffer buffer_A(context,CL_MEM_READ_WRITE,sizeof(int) * totalNumbers);
	    cl::Buffer buffer_B(context,CL_MEM_READ_WRITE,sizeof(int)*10);
	    cl::Buffer buffer_C(context,CL_MEM_READ_WRITE,sizeof(int)*2);

	    int B[] = {0, 1, 2, 0, 1, 2, 0, 1, 2, 0};

	    //create queue to which we will push commands for the device.
	    cl::CommandQueue queue(context,default_device);

	    //write arrays A and B to the device
	    queue.enqueueWriteBuffer(buffer_A,CL_TRUE,0,sizeof(int)*totalNumbers, numbers);

	    int i = totalNumbers;
	    //alternative way to run the kernel
	    cl::Kernel kernel_add=cl::Kernel(program,"count3s");
	    kernel_add.setArg(0,buffer_A);
	    kernel_add.setArg(1,buffer_C);
	    kernel_add.setArg(2, i / 2);

	    queue.enqueueNDRangeKernel(kernel_add,cl::NullRange,cl::NDRange(2),cl::NullRange);
	    queue.finish();

	    int C[2];
	    //read result C from the device to array C
	    queue.enqueueReadBuffer(buffer_C,CL_TRUE,0,sizeof(int)*2,C);

	    std::cout<<" result: \n";
	    for(int y=0;y < 2;y++){
	    	result += C[y];
	    }

	    std::cout<< result << endl;

	    return 0;

	} catch (cl::Error& e){
	    std::cout <<  e.err() << endl;
	}

}
