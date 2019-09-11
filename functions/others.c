#include "headers.h"
int others(char syscmnd[100][100],char *jobs[],int *bgpids,int r)
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
		bg = 1;
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
		{
			waitpid(pid,NULL,0);
			return 0;
		}
		else
		{

			for(int w=1;w<i-1;++w)
			{
				strcat(argv[0]," ");
				strcat(argv[0],argv[w]);
			}
			jobs[r] = argv[0];
			bgpids[r] = pid;

			printf("process with pid %d started\n",pid);
			signal(SIGCHLD,bgend);
			return 1;
		}
	}
}
