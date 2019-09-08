void pinfo(char *id)
{
	char path[100];
	char pathlink[100];
	sprintf(path,"/proc/%s/stat", id);
	sprintf(pathlink,"/proc/%s/exe", id);

	int fd1 = open(path, O_RDONLY);
	
	char *BUFFER = (char *) calloc(1000, sizeof(char)); 
	char *BUFFER2 = (char *) calloc(1000, sizeof(char)); 
	read(fd1,BUFFER,1000);
	readlink(pathlink,BUFFER2,1000);

	char cmnds[100][100];

	char *mytoken = strtok(BUFFER," ");
	int wx = 0; 
	while(mytoken!=NULL)
	{
		strcpy(cmnds[wx],mytoken);
		wx++;
		mytoken = strtok(NULL, " ");
	}

	printf("pid -- %s\n",id);
	if(strchr(cmnds[2],')')!=NULL)
	{
		printf("Process Status -- %s\n",cmnds[3]);
		printf("memory -- %s\n",cmnds[23]);
	}
	else
	{
		printf("Process Status -- %s\n",cmnds[2]);
		printf("memory -- %s\n",cmnds[22]);
	}
	
	printf("Executable Path --​ ​ %s\n",BUFFER2);
}


