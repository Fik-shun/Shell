#include "headers.h"
void others(char syscmnd[100][100])
{
	char *argv[101];
	int i,bg=0;
	for(i=0;i<100;++i)
	{
		if(!strcmp("",syscmnd[i]))
		{
			argv[i] = NULL;
			break;
		}
		argv[i] = syscmnd[i];
	}

	if(!strcmp("&",argv[i-1]))
	{
		bg =1;
		argv[i-1] = NULL;
	}

	int pid = fork();
	if(pid==0)
	{
		int j = execvp(argv[0], argv);
		if(j==-1)
			printf("ERROR!\n");
		exit(0);
	}
	else
	{
		if(bg==0)
			waitpid(pid,NULL,0);
		else
		{
			printf("process with pid %d started\n",pid);
			signal(SIGCHLD,bgend);
		}
		return;
	}
}
