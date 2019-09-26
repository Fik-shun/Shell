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
void ls(char flag[100][100]);
void pinfo(char *);
void hist(char histor[20][100], int, int);
int others(char *syscmnd[],char *jobs[],int *,int);
void set_env(char cmnd[100][100]);
void unset_env(char cmnd[100][100]);
void the_jobs(char *jobs[],int *,int);
void kjob(char cmnd[100][100],int *,int);
void overkill(int *,int);
void quit();
void fg(char cmnd[100][100],int *);
void bg(char cmnd[100][100],int *);



#endif