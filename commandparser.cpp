#include "wash.h"

int comparse()
{
    int status;
char * commandTokens[ARG_BUFFER]; // array for the different tokens in the command
char inputLine[ARG_CHAR]; // buffer for the user input

        // We wait for user input
		fgets(inputLine, ARG_CHAR, stdin);  //data is stored in line,
        //size of data is ARG_CHAR,data taken from stdin
	
		// If nothing is written, the we go back to main program and \
        //continue the shell loop
		if((commandTokens[0] = strtok(inputLine," \n\t")) == NULL)
        {
            //cout<<"success\n";
            return 0;
        }

        // We read the string,return a pointer to null terminated string
        // and store it in char* tokens[]
        //
        //and pass it to our
		// commandHandler as the argument
		int tokenCount;
        //strtok stores the point where we last left in a static location and 
        //it access next yime fromt that point. so we pass null
		for(tokenCount=1;(commandTokens[tokenCount] = strtok(NULL, " \n\t")) != NULL;) 
			tokenCount++;

            status=commandHandler(commandTokens,tokenCount);

		return  status;//return status of commandHandler 2:exit

}
