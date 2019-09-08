void bgend()
{
	int pid,status;
	char *nrml = (char *)calloc(20,sizeof(char));
	pid = waitpid(0,&status,WNOHANG); 
	//return immediately if no child exited

	if(WIFEXITED(status)) //true if child terminated normally
	{
		int st = WEXITSTATUS(status);
		if(st==0)
			nrml = "normally";
		else
			nrml = "abnormally";
	}
	char *theexit = (char *)calloc(100,sizeof(char));
	sprintf(theexit,"\npid %d exited.\n%s\n",pid,nrml);
	if(pid>0)//means parent
	{
		write(2,theexit,strlen(theexit));
		int i,y,j,k,h=39;
		long no;
		char host[100],orig[1024];

		gethostname(host,100);
		char *user = (char *)getenv("USER");
		getcwd(orig,sizeof(orig));
		char cwd[1024],cwdf[1024];
		getcwd(cwd,sizeof(cwd));
		strcpy(cwdf,cwd);
		cwdf[strlen(orig)] = '\0';

		if(strlen(cwd)>=strlen(orig) && !strcmp(cwdf,orig) && (cwd[strlen(orig)]=='/' || cwd[strlen(orig)]=='\0'))
			printf("<%s@%s:~%s>",user,host,cwd+strlen(orig));
		else
			printf("<%s@%s:%s>",user,host,cwd);
		fflush(stdout);


	}

	free(theexit);
	return;

}