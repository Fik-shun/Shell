#include "headers.h"
void set_env(char cmnd[100][100])
{
	char *var = cmnd[1];
	char *val = cmnd[2];

	if(!strcmp(var,"") || strcmp(cmnd[3],""))
		printf("ERROR! wrong no of args\n");
	else
	{
		setenv(var,val,1);
	}
}

void unset_env(char cmnd[100][100])
{
	int i=1;	
	while(strcmp(cmnd[i],""))
	{
		unsetenv(cmnd[i]);
		i++;
	}
	if(i==1)
		printf("ERROR! need vars\n");
}