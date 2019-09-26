void command(parts,)
{
	if(!strcmp(parts[i][0],"pwd"))
		pwd();
	else if(!strcmp(parts[i][0],"echo"))
	{
		echo(parts[i][1]);
	}	
	else if(!strcmp(parts[i][0],"cd"))
	{
		if(strcmp(parts[i][1],"~")&&strcmp(parts[i][1],""))
			cdir(parts[i][1]);
		else
			cdir(orig);
	}
	else if(!strcmp(parts[i][0],"ls"))
	{
		ls(parts[i]);
	}
	else if(!strcmp(parts[i][0],"pinfo"))
	{
		if(!strcmp(parts[i][1],""))
		{
			char theid[10];
			memset(theid,'\0',sizeof(theid));
			sprintf(theid,"%d", getpid());
			pinfo(theid);
		}
		else
			pinfo(parts[i][1]);
	}
	else if(!strcmp(parts[i][0],"history"))
	{
		if(!strcmp(parts[i][1],""))
			hist(histor,h,10);
		else
		{
			char *ptr;
			no = strtol(parts[i][1],&ptr,10);
			hist(histor,h,no);
		}
	}
	else if(!strcmp(parts[i][0],"setenv"))
	{
		set_env(parts[i]);
	}
	else if(!strcmp(parts[i][0],"unsetenv"))
	{
		unset_env(parts[i]);
	}
	else if(!strcmp(parts[i][0],"jobs"))
	{
		the_jobs(jobs,bgpids,r);
	}
	else if(!strcmp(parts[i][0],"kjob"))
	{
		kjob(parts[i],bgpids,r);
	}
	else if(!strcmp(parts[i][0],"overkill"))
	{
		overkill(bgpids,r);
	}
	else if(!strcmp(parts[i][0],"quit"))
	{
		quit();
	}
	else if(!strcmp(parts[i][0],"fg"))
	{
		fg(parts[i],bgpids);
	}
	else
	{
		int heyyy = 0;
		char *hello[100];
		for(int l=0;l<100;++l)
			hello[l] = (char *)malloc(sizeof(char) *100);

		// memset(hello,'\0',sizeof(hello));
		
		for(int g=0;g<100;++g)
		{
			strcpy(hello[g],parts[i][g]);
		}
		heyyy = others(hello,jobs,bgpids,r);
		if(heyyy==1)
			r++;
	}
}	