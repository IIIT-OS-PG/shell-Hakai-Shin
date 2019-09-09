#include "wash.h"
#include "washbuilt.h"
/**
* Method used to handle the commands entered via the standard input
*/ 
int lsh_num_builtins() {
  return sizeof(builtin_str) / sizeof(char *);
}

int commandHandler(char * command_tokens[],int tokenCount){
	int i = 0;
	int j = 0;
	
	int fileDescriptor;
	int standardOut;
	
	int aux;
    
	int background = 0;

	char *args_aux[256];
	
	// We look for the special characters and separate the command itself
	// in a new array for the arguments
	while ( command_tokens[j] != NULL){
		if ( (strcmp(command_tokens[j],">") == 0) || (strcmp(command_tokens[j],"<") == 0) || (strcmp(command_tokens[j],"&") == 0)){
			break;
		}
		args_aux[j] = command_tokens[j];
		j++;
	}

	//char* command_tokens[ARG_BUFFER];

	for (i = 0; i < lsh_num_builtins(); i++) {
    if (strcmp(command_tokens[0], builtin_str[i]) == 0) 
	{
      (*builtin_func[i])(command_tokens);
	  return 1;
    }
  }


  		// If none of the preceding commands were used, we invoke the
		// specified program. We have to detect if I/O redirection,
		// piped execution or background execution were solicited
		i=0;
		while (command_tokens[i] != NULL && background == 0){
			// If background execution was solicited (last argument '&')
			// we exit the loop
			if (strcmp(command_tokens[i],"&") == 0)
			{
				background = 1;
			}
			// If '|' is detected, piping was solicited, and we call
			// the appropriate method that will handle the different
			// executions
			else if (strcmp(command_tokens[i],"|") == 0)
			{
				pipeHandler(command_tokens);
				return 1;
			}
			// If '<' is detected, we have Input and Output redirection.
			// First we check if the structure given is the correct one,
			// and if that is the case we call the appropriate method
			else if (strcmp(command_tokens[i],">") == 0 )
			{

				redio(args_aux,NULL,command_tokens[i+1],0);
				return 1;
				
			}
			else if (strcmp(command_tokens[i],"<") == 0){
				
				redio(args_aux,NULL,command_tokens[i+1],1);
				return 1;
			}
			else if (strcmp(command_tokens[i],">>") == 0 )
			{

				redio(args_aux,NULL,command_tokens[i+1],2);
				return 1;
				
			}
			
			i++;
		}
		
	
return launchProg(command_tokens);
}
