PROG = textr
CC = g++
CPPFLAGS = -lpthread  -lOpenCL 
OBJS = main.o
$(PROG) : $(OBJS)
$(CC) $(LDFLAGS) -o $(PROG) $(OBJS)
main.o :
$(CC) $(CPPFLAGS) -c ParallelTeam.cpp ComputeObj.cpp Thread_ComputeObj.cpp MPI_ComputeObj.cpp OpenCL_ComputeObj.cpp Process_ComputeObj.cpp Cuda_ComputeObj.cpp
clean:
rm -f core $(PROG) $(OBJS)