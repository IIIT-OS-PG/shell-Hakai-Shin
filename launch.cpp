#include "wash.h"
int launchProg(char **args){	 
	 
	 pid_t pid;
	 if((pid=fork())==-1){
		 printf("Child process could not be created\n");
	 }
	 // pid == 0 implies the following code is related to the child process
	if(pid==0){	
		//cout<<"we are inside child process/n";


		//execvp:
		//This particular variant expects a program name and an array (also called a vector, hence the ‘v’) 
		//of string arguments (the first one has to be the program name). 
		//The ‘p’ means that instead of providing the full file path of the program to run, 
		//we’re going to give its name, and let the operating system search for the program 
		//in the path.
		// If we launch non-existing commands we end the process
		if (execvp(args[0],args)==-1){
			kill(getpid(),SIGTERM);
			return 0; //command not found
		}
	 }

	 //cout<<"we are out of child/n";
	 
	 // The following will be executed by the parent
	 
	 // If the process is not requested to be in background, we wait for
	 // the child to finish.
	
	 
		 //In the case of a terminated child, performing a wait allows
       //the system to release the resources associated with  the  child;  if  a
       // wait  is not performed, then the terminated child remains in a "zombie" state
		//If a child has already changed state, then these calls  return  immedi‐
      // ately.   Otherwise,  they block until either a child changes state or a
       //signal handler interrupts the call
		//if we dont wait the parent will do its computations and we encounter 
	 //race condition
		 waitpid(pid,NULL,0);
	
	return 1;
}
