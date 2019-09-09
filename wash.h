#ifndef WASH_HPP
#define WASH_HPP
//contains all the headers required

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>      // for execvp
#include<string.h>      // for strcmp strtok
#include <sys/types.h>  // for open system call
#include <sys/stat.h>
#include <fcntl.h>
#include<sys/wait.h>
#include <termios.h>
#include<iostream>
#define ARG_BUFFER 100
#define ARG_CHAR 1024

using namespace std;

static pid_t GBSH_PID;
static pid_t GBSH_PGID;
//pid_t pid;
//const char* comargs[ARG_BUFFER]={NULL};
//int init_wash();
void set_washconfig();
void init();
int run_wash();
int comparse();
int commandHandler(char* tokens[],int tokenCount);  
int launchProg(char** command_tokens);
void redio(char * args[], char* inputFile, char* outputFile, int option);
void pipeHandler(char * args[]);
static int GBSH_IS_INTERACTIVE;
static struct termios GBSH_TMODES;

#endif
