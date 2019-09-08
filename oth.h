void oth(char *syscmnd)
{
	char *argv[2];
	argv[0] = syscmnd;
	argv[1] = NULL;
	int pid = fork();
	if(pid==0)
		execvp(argv[0], argv); //use in comb with fork
	else
	{
		wait(NULL);
		return;
	}
}
