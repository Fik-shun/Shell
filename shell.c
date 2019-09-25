#include "functions/headers.h"

int main(int argc,char *argv[])
{
	//initial setup
	int i,y,j,k,h=39,res=0,r=0,bgpids[100];
	long no;
	char cdto[100], histor[20][100],host[100],orig[1024];
	char *jobs[20];
	for(int e=0;e<20;e++){
		jobs[e]=(char *)malloc(sizeof(char) *100);
	}
	
	for(k=0;k<20;++k)
		memset(histor[k],'\0',sizeof(histor[k]));


	gethostname(host,100);
	char *user = (char *)getenv("USER");


	//getting addr where a.out is
	for(y=strlen(argv[0])-1;;y--)
	{
		if(argv[0][y]=='/')
			break;
	}    
	strncpy(cdto,argv[0],y);

	cdir(cdto);
	getcwd(orig,sizeof(orig));

	
	while(1)
	{
		int w=0;
		char cwd[1024],cwdf[1024], inp[100],cmnds[100][100], parts[10][100][100];
		getcwd(cwd,sizeof(cwd));
		strcpy(cwdf,cwd);
		cwdf[strlen(orig)] = '\0';

		if(strlen(cwd)>=strlen(orig) && !strcmp(cwdf,orig) && (cwd[strlen(orig)]=='/' || cwd[strlen(orig)]=='\0'))
			printf("<%s@%s:~%s>",user,host,cwd+strlen(orig));
		else
			printf("<%s@%s:%s>",user,host,cwd);
		fflush(stdout);




		//inp command

		fgets(inp,10000,stdin);
		// printf("%d\n",res);
		// if(res!=0)
		
 

		inp[strlen(inp)-1] = '\0'; //removed \n


		//for hist
		if( h==39 || strcmp(inp,histor[h]))
		{
			h = (h + 1)%20;
			memset(histor[h],'\0',sizeof(histor[h]));
			strcpy(histor[h],inp);
		}	

		//breaking inp
		char *token = strtok(inp,";");
		while(token!=NULL)
		{
			strcpy(cmnds[w],token);
			w++;
			token = strtok(NULL, ";");
		}
		int totcmnds = w;

		//executing
		for(i=0;i<totcmnds;++i)
		{
			

			memset(parts[i],'\0',sizeof(parts[i]));
			// printf("%s\n",jobs[0]);
			char *toke = (char *) calloc(100,sizeof(char));
			toke = strtok(cmnds[i]," ");
			int e = 0;
			while(toke!=NULL)
			{
				strcpy(parts[i][e],toke);
				e++;
				toke = strtok(NULL, " ");
			}
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
	}		
}