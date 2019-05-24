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
#include "ComputeObj.cpp"

class OpenCL_ComputeObj : public ComputeObj{
	private:
		int teamCount = 0;
		int * numbers;
		int totalNumbers;
		int result = 0;
		executionEntryFunc defaultfunc;

	public:
		OpenCL_ComputeObj(int *currentNumbers, int total){
			numbers = currentNumbers;
			totalNumbers = total;
		}

		void createTeam(int n){

		}

		int getSizeOfTeam(){
			return teamCount;
		}

		void startAllTeamMembers(){
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
			cl::Buffer buffer_A(context,CL_MEM_READ_WRITE,sizeof(int) * numbers);
			cl::Buffer buffer_C(context,CL_MEM_READ_WRITE,sizeof(int)*2);


			//create queue to which we will push commands for the device.
			cl::CommandQueue queue(context,default_device);

			//write arrays A and B to the device
			queue.enqueueWriteBuffer(buffer_A,CL_TRUE,0,sizeof(int)*numbers, numbers);

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
		}

		void lockSemaphoreInSet(int index){
		}

		void unlockSempahoreInSet(int index){
		}

		void unlockSemaphoreSet(){
		}

		void setAllSemaphoresInSet(unsigned short *values){

		}

		void createSemaphoreSet(int n){

		}

		void deleteSemaphoreSet(){


		}

		void waitForAllTeamMembers(){
		}

		void setEntryFunction(executionEntryFunc startFunc){
			defaultfunc = startFunc;
		}

		void setEntryFunction(int index, executionEntryFunc startFunc){
			defaultfunc = startFunc;
			int memberIndex = index;
		}
}
