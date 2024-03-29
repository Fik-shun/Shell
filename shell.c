#include "functions/headers.h"
void sigintHandler(int sig_num) 
{ 
    signal(SIGINT, sigintHandler); 
    fflush(stdout); 
}

void sigabrtHandler(int sig_num) 
{ 
    signal(SIGABRT, sigabrtHandler); 
    fflush(stdout); 
}

void sigtermHandler(int sig_num) 
{ 
    signal(SIGTERM, sigtermHandler); 
    fflush(stdout); 
}

void sighupHandler(int sig_num) 
{ 
    signal(SIGHUP, sighupHandler); 
    fflush(stdout); 
}

void sigtstpHandler(int sig_num) 
{ 
    signal(SIGTSTP, sigtstpHandler); 
    fflush(stdout); 
}

void sigquitHandler(int sig_num) 
{ 
    signal(SIGQUIT, sigquitHandler); 
    fflush(stdout); 
}

int main(int argc,char *argv[])
{
	totalkill = 0;

	signal(SIGINT, sigintHandler);
	signal(SIGABRT, sigabrtHandler);
	signal(SIGTERM, sigtermHandler);
	signal(SIGHUP, sighupHandler);
	signal(SIGTSTP, sigtstpHandler);
	signal(SIGQUIT, sigquitHandler);



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

		//print prompt
		if(strlen(cwd)>=strlen(orig) && !strcmp(cwdf,orig) && (cwd[strlen(orig)]=='/' || cwd[strlen(orig)]=='\0'))
			printf("<%s@%s:~%s>",user,host,cwd+strlen(orig));
		else
			printf("<%s@%s:%s>",user,host,cwd);
		fflush(stdout);

		//inp command
		fgets(inp,10000,stdin);
		inp[strlen(inp)-1] = '\0'; //removed \n

		//for hist
		if( h==39 || strcmp(inp,histor[h]))
		{
			h = (h + 1)%20;
			memset(histor[h],'\0',sizeof(histor[h]));
			strcpy(histor[h],inp);
		}	

		//breaking inp by ;
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


			//checking output redirection
			//iterate...and find
			int w2 = 0;
			char cmndcopy[100];
			sprintf(cmndcopy,"%s",cmnds[i]);
			char *tokenNew = strtok(cmnds[i],">");
			char rcmnds[100][100];
			while(tokenNew!=NULL)
			{
				strcpy(rcmnds[w2],tokenNew);
				w2++;
				tokenNew = strtok(NULL, ">");
			}

			int redirect = 0;
			int file1;
			int append=0;
			int stdout_copy;
			if(w2==2)
			{
				for(int v=0;v<strlen(cmndcopy);++v)
					if(cmndcopy[v]=='>'&&cmndcopy[v-1]=='>')
						append=1;
				printf("%d\n",append);
				redirect = 1;
				stdout_copy = dup(1);
				close(1);
				if(append==1)
					file1 = open(rcmnds[1]+1,O_APPEND | O_WRONLY | O_CREAT, 0644);
				else
					file1 = open(rcmnds[1]+1,O_WRONLY | O_CREAT | O_TRUNC, 0644);
			}


			//checking input redirection
			int w7 = 0;
			char *tokenNew2 = strtok(rcmnds[0],"<");
			char r2cmnds[100][100];
			while(tokenNew2!=NULL)
			{
				strcpy(r2cmnds[w7],tokenNew2);
				w7++;
				tokenNew2 = strtok(NULL, "<");
			}
			int redirect2 = 0;
			int file2;
			int stdin_copy;
			if(w7==2)
			{
				redirect2 = 1;
				stdin_copy = dup(0);
				close(0);
				char thefilename[100];
				sprintf(thefilename,"%s",r2cmnds[1]+1);
				for(int o=0;o<strlen(thefilename);++o)
					if(thefilename[o]==' ')
						thefilename[o] = '\0';
				file2 = open(thefilename,O_RDONLY, 0644);
			}


			int w3 = 0;
			char r3cmnds[100][100];
			char *tokenPipe = strtok(r2cmnds[0],"|");
			while(tokenPipe!=NULL)
			{
				strcpy(r3cmnds[w3],tokenPipe);
				w3++;
				tokenPipe = strtok(NULL, "|");
			}

			if(w3>1)
			{

				int in = dup(0);
				int out = dup(1);


				int pipes[2];
				pipe(pipes);
				pid_t pipepid = fork();


				if(pipepid == 0)
		        {

		        	close(pipes[0]);
		        	dup2(pipes[1],1);

	                memset(parts[i],'\0',sizeof(parts[i]));
					char *toke = (char *) calloc(100,sizeof(char));
					toke = strtok(r3cmnds[0]," ");
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
					else if(!strcmp(parts[i][0],"bg"))
					{
						bg(parts[i],bgpids);
					}
					else
					{
						int heyyy = 0;
						char *hello[100];
						for(int l=0;l<100;++l)
							hello[l] = (char *)malloc(sizeof(char) *100);
						for(int g=0;g<100;++g)
						{
							strcpy(hello[g],parts[i][g]);
						}
						heyyy = others(hello,jobs,bgpids,r);
						if(heyyy==1)
							r++;
					}

	                exit(0);

		        }
		        else
		        {

		       		close(pipes[1]);
		       		dup2(pipes[0],0);

		        	waitpid(pipepid,NULL,0);
	                /* Parent process closes up output side of pipe */
	               
	                memset(parts[i],'\0',sizeof(parts[i]));
					char *toke = (char *) calloc(100,sizeof(char));
					toke = strtok(r3cmnds[1]," ");
					int e = 0;
					while(toke!=NULL)
					{
						strcpy(parts[i][e],toke);
						e++;
						toke = strtok(NULL, " ");
					}
					

					
					int heyyy = 0;
					char *hello[100];
					for(int l=0;l<100;++l)
						hello[l] = (char *)malloc(sizeof(char) *100);
					for(int g=0;g<100;++g)
					{
						strcpy(hello[g],parts[i][g]);
					}
					heyyy = others(hello,jobs,bgpids,r);
					if(heyyy==1)
						r++;


					
		        }
		        dup2(out,1);
		        dup2(in,0);
			}
			else
			{
				memset(parts[i],'\0',sizeof(parts[i]));
				char *toke = (char *) calloc(100,sizeof(char));
				toke = strtok(r2cmnds[0]," ");
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
				else if(!strcmp(parts[i][0],"bg"))
				{
					bg(parts[i],bgpids);
				}
				else
				{
					int heyyy = 0;
					char *hello[100];
					for(int l=0;l<100;++l)
						hello[l] = (char *)malloc(sizeof(char) *100);
					for(int g=0;g<100;++g)
					{
						strcpy(hello[g],parts[i][g]);
					}
					heyyy = others(hello,jobs,bgpids,r);
					if(heyyy==1)
						r++;
				}
					
			}

			if(redirect2==1)
			{
				close(file2);
				dup2(stdin_copy, 0);
				close(stdin_copy);
			}

			if(redirect==1)
			{
				close(file1);
				dup2(stdout_copy, 1);
				close(stdout_copy);
			}
		}
	}		
}