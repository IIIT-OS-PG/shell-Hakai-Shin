#include "wash.h"



/*
  Builtin function implementations.
*/
int lsh_cd(char **args)
{
  if (args[1] == NULL) {
    fprintf(stderr, "expected argument to \"cd\"\n");
  }
  else if(strcmp(args[1],"~")==0)
  {
    char* home;
    home=getenv("HOME");
    chdir(home);
  }
  
   else {
    if (chdir(args[1]) != 0) {
      perror("cd");
      return 0;
    }
  }
  return 1;
}