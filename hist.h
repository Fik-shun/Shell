void hist(char histor[20][100], int h, int n)
{
	int x,w,z=1;
	for(x=h;;x=(x+19)%20)
	{
		if(histor[x][0]=='\0' || z>n)
			break;
		z++;
	}
	for(w=(x+1)%20;;w=(w+1)%20)
	{
		printf("%s\n",histor[w]);
		if(w==h)
			break;
	}
}
