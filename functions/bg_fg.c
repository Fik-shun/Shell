#include "headers.h"

void bg(char cmnd[100][100],int *bgpids)
{
	if(!strcmp("",cmnd[1]))
	{
		printf("ERROR!\n");
		return;
	}
	int jobno = atoi(cmnd[1]);
	int thepid = bgpids[jobno-1];
	if(thepid<=0)
		printf("ERROR!\n");
	else
		kill(thepid,18);
}


void fg(char cmnd[100][100],int *bgpids)
{
	if(!strcmp("",cmnd[1]))
	{
		printf("ERROR!\n");
		return;
	}
	int jobno = atoi(cmnd[1]);
	
}