#include "headers.h"

void fg(char cmnd[100][100],int *bgpids)
{
	if(!strcmp("",cmnd[1]))
	{
		printf("ERROR!");
		return;
	}
	int jobno = atoi(cmnd[1]);
	
}