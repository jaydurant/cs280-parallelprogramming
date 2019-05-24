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

//Abstract ComputeObj

typedef void (*executionEntryFunc)(void *);


class ComputeObj{

	public:
		virtual void createTeam(int n) = 0;

		virtual void createSemaphoreSet(int n ) = 0;

		virtual void deleteSemaphoreSet() = 0;

		virtual void setAllSemaphoresInSet(unsigned short *values) = 0;

		virtual void lockSemaphoreInSet(int index) = 0;

		virtual void unlockSempahoreInSet(int index) = 0;

		virtual void unlockSemaphoreSet() = 0;

		virtual void startAllTeamMembers() = 0;

		virtual void waitForAllTeamMembers() = 0;

		virtual int getSizeOfTeam() = 0;

		virtual void setEntryFunction(executionEntryFunc startFunc) = 0;

		virtual void setEntryFunction(int index, executionEntryFunc startFunc) = 0;

		virtual ~ComputeObj(){

		}
}
