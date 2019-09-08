#ifndef headers
#define headers

#include<stdio.h>
#include<string.h> 
#include<fcntl.h> 
#include<sys/stat.h>
#include<sys/wait.h>
#include<sys/types.h>
#include<stdlib.h>
#include<unistd.h> 
#include<libgen.h>
#include<dirent.h>
#include<time.h>
#include<pwd.h>
#include<grp.h>

void bgend();
void pwd();
void cdir(char *);
void echo(char *);
char *format(char *, time_t);
void pinfo(char *);
void hist(char histor[20][100], int, int);
void others(char syscmnd[100][100]);


#endif