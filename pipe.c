#include "wash.h"

void pipeHandler(char * cargs[]){
	// File descriptors
	int des1[2],des2[2],pipe_count = 0,lend = 0;
	
	char *aux_command[256];
	// First we calculate the number of commands (they are separated
	// by '|')
	for(int loop=0;cargs[loop] != NULL;loop++)
	{
		if (strcmp(cargs[loop],"|") == 0)
		{
			pipe_count++;
		}
	}
	pipe_count++;

	
	// Main loop of this method. For each command between '|', the
	// pipes will be configured and standard input and/or output will
	// be replaced. Then it will be executed
	int k = 0,j=0,i=0;
	for(;lend != 1 && cargs[j] != NULL;){
		
		// We use an auxiliary array of pointers to store the command
		// that will be executed on each iteration
		for(;strcmp(cargs[j],"|") != 0;)
		{

			aux_command[k] = (char*)malloc(sizeof(strlen(cargs[j])+1));
			strcpy(aux_command[k],cargs[j]);
			j++;	
			if (cargs[j] == NULL)
			{
				// 'end' variable used to keep the program from entering
				// again in the loop when no more arguments are found
				k++;
				lend = 1;
				break;
			}
			k++;
		}
		// Last position of the command will be NULL to indicate that
		// it is its end when we pass it to the exec function
		j++;
		aux_command[k] = NULL;
				
		
		// Depending on whether we are in an iteration or another, we
		// will set different descriptors for the pipes inputs and
		// output. This way, a pipe will be shared between each two
		// iterations, enabling us to connect the inputs and outputs of
		// the two different commands.
		if (i % 2 == 0)
		{
			pipe(des2); // for odd i
		}
		else if(i%2!=0)
		{
			pipe(des1); // for even i
		}
		pid_t pid;
		pid=fork();
		
		if(pid<0)
		{			
			if (i != pipe_count - 1)
			{
				if (i % 2 == 0){
					close(des2[1]); // for odd i
				}
				else
				{
					close(des1[1]); // for even i
				} 
			}			
			printf("Child process could not be created\n");
			exit(-1);
		}
		if(pid==0)
		{
			// If we are in the first command
			if (i == 0)
			{
				dup2(des2[1], STDOUT_FILENO);
			}
			// If we are in the last command, depending on whether it
			// is placed in an odd or even position, we will replace
			// the standard input for one pipe or another. The standard
			// output will be untouched because we want to see the 
			// output in the terminal
			else if (i == pipe_count - 1)
			{
				if (pipe_count % 2 != 0)
				{ // for odd number of commands
					dup2(des1[0],STDIN_FILENO);
				}
				else
				{ // for even number of commands
					dup2(des2[0],STDIN_FILENO);
				}
			// If we are in a command that is in the middle, we will
			// have to use two pipes, one for input and another for
			// output. The position is also important in order to choose
			// which file descriptor corresponds to each input/output
			}
			else
			{ // for odd i
				if(i % 2 == 0)
				{ // for even i
					dup2(des1[0],STDIN_FILENO); 
					dup2(des2[1],STDOUT_FILENO);					
				} 
				else
				{
					dup2(des2[0],STDIN_FILENO); 
					dup2(des1[1],STDOUT_FILENO);
				}
			}
			
			
			if (execvp(aux_command[0],aux_command)<0)
			{
				kill(getpid(),SIGTERM);
			}		
		}
				
		// CLOSING DESCRIPTORS ON PARENT
		if (i == 0)
		{
			close(des2[1]);
		}
		else if (i == pipe_count - 1)
		{
			if (pipe_count % 2 == 0)
			{					
				close(des2[0]);
			}
			else
			{					
				close(des1[0]);
			}
		}
		else
		{
			if (i % 2 == 0)
			{					
				close(des1[0]);
				close(des2[1]);
			}
			else
			{					
				close(des2[0]);
				close(des1[1]);
			}
		}
				
		waitpid(pid,NULL,0);
				
		i++;
		k=0;	
	}
	
}