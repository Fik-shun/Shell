#include "headers.h"

void kjob(char cmnd[100][100], int *bgpids, int r)
{
	//not empty
	if(!(strcmp("",cmnd[1])&&strcmp("",cmnd[2])))
	{
		printf("ERROR!");
		return;
	}	

	int jobno = atoi(cmnd[1]);
	int signo = atoi(cmnd[2]);

	int thepid = bgpids[jobno-1];

	//error if negative,signo greater,
	if(signo<0 || signo > 31 || thepid<=0 || jobno >r) 
		printf("ERROR!\n");
	else
		kill(thepid,signo);
	
}

void overkill(int *bgpids,int r)
{
	int i = 0;
	while(i<r)
	{
		kill(bgpids[i],9);
		i++;
	}
}

void quit()
{
	kill(0,9);
}