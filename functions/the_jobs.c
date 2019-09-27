#include "headers.h"
void the_jobs(char *jobs[],int *bgpids,int r)
{
	for(int i=0;i<r;++i)
	{
		int skip = 0;
		for(int e=0;e<totalkill;++e)
		{
			if(killed[e]==bgpids[i])
			{
				skip = 1;
				break;
			}
		}
		if(skip==1)
			continue;
		char path[100];
		sprintf(path,"/proc/%d/stat", bgpids[i]);

		int fd1 = open(path, O_RDONLY);
		
		char *BUFFER = (char *) calloc(1000, sizeof(char)); 
		read(fd1,BUFFER,1000);

		char cmnds[5][100];
		char *mytoken = strtok(BUFFER," ");
		int wx = 0; 
		while(wx<4)
		{
			strcpy(cmnds[wx],mytoken);
			wx++;
			mytoken = strtok(NULL, " ");
		}

		char status[2];
		char thestatus[8]="Running";
		if(strchr(cmnds[2],')')!=NULL)
			strcpy(status,cmnds[3]);
		else
			strcpy(status,cmnds[2]);
		if(!strcmp("T",status))
			strcpy(thestatus,"Stopped");

		printf("[%d] %s %s [%d]\n",i+1,thestatus,jobs[i],bgpids[i]);
	}
}