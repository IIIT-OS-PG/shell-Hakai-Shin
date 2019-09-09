#include "wash.h"
#include "washconfig.h"
void set_washconfig()
{
    char* filename="washrc";
    char * envTokens[ARG_BUFFER];
    char inputLine[ARG_CHAR];
    FILE* fd;
    fd=fopen(filename,"r+");
    fgets(inputLine, ARG_CHAR, fd); 

    envTokens[0] = strtok(inputLine,":\n\t");
		int tokenCount;
    
		for(tokenCount=1;(envTokens[tokenCount] = strtok(NULL, ":\n\t")) != NULL;) 
			tokenCount++;

    for(int i=0;i<tokenCount;i++)
        {
            if(strcmp(envTokens[i],"PS1")==0)
                setenv("PS1",envTokens[i+1],1);
        }

fclose(fd);

}