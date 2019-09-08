void cdir(char *cmnd2)
{
	int a = chdir(cmnd2);
	if(a!=0)
		printf("ERROR!\n");
	return;
}