#include "wash.h"
void redio(char * args[], char* infile, char* outfile, int choice){
	 
	pid_t pid;
	
	
	if((pid=fork())==-1){
		printf("Child process could not be created\n");
		exit(1);
	}
	int fd;
	if(pid==0){
		if (choice == 1){
			// Same as before for the output file
			fd = open(outfile, O_RDONLY, 0600);
			dup2(fd, STDIN_FILENO);
			close(fd);		 
		}
		else if (choice == 0){
			fd = open(outfile, O_CREAT | O_TRUNC | O_WRONLY, 0600); 
			dup2(fd, STDOUT_FILENO); 
			close(fd);
		}
		
		if (execvp(args[0],args)==-1){
			printf("err");
			kill(getpid(),SIGTERM);
		}		 
	}
	waitpid(pid,NULL,0);
}