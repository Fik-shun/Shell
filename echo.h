void echo(char *toPrint)
{
	int i;
	if(toPrint[0] == 34)
	{	
		for(i=1;i<strlen(toPrint)-1;++i)
			printf("%c",toPrint[i]);
		printf("\n");
	}
	else	
		printf("%s\n",toPrint);
}