#include "headers.h"
void the_jobs(char *jobs[],int *bgpids,int r)
{
	for(int i=0;i<r;++i)
	{
		printf("[%d] %s [%d]\n",i+1,jobs[i],bgpids[i]);
	}
}