char *format(char *str, time_t val)
{
	strftime(str,100,"%b %d %H:%M",localtime(&val));
	return str;
}

void ls(char flag[100][100])
{

	DIR *d = opendir(".");
    struct dirent *dir;
    char date[100];
    memset(date,'\0',sizeof(date));
    struct stat fileStat;
    

    int hid=0,ll=0;

    if(!strcmp("",flag[1])) //this is ls
	    ;
	else if(!strcmp("-a",flag[1]))
		hid = 1;
	else if(!strcmp("-l",flag[1]))
		ll=1;
	else if(!(strcmp("-la",flag[1])&&strcmp("-al",flag[1])))
	{
		ll=1;
		hid=1;
	}
	else
	{
		d = opendir(flag[1]);
		if(d==0)
			printf("ERROR!\n");
	}


    
    if (d)
    {
        while ((dir = readdir(d)) != NULL)
        {
        	
    		if((strcmp(dir->d_name,".")&&strcmp(dir->d_name,"..")) || hid == 1)
		    {
		    	if(ll==0)   
		            printf("%s\n", dir->d_name); //ll=0
	        	else
        		{
					stat(dir->d_name,&fileStat);
	        		printf( (S_ISDIR(fileStat.st_mode)) ? "d" : "-");
				    printf( (fileStat.st_mode & S_IRUSR) ? "r" : "-");
				    printf( (fileStat.st_mode & S_IWUSR) ? "w" : "-");
				    printf( (fileStat.st_mode & S_IXUSR) ? "x" : "-");
				    printf( (fileStat.st_mode & S_IRGRP) ? "r" : "-");
				    printf( (fileStat.st_mode & S_IWGRP) ? "w" : "-");
				    printf( (fileStat.st_mode & S_IXGRP) ? "x" : "-");
				    printf( (fileStat.st_mode & S_IROTH) ? "r" : "-");
				    printf( (fileStat.st_mode & S_IWOTH) ? "w" : "-");
				    printf( (fileStat.st_mode & S_IXOTH) ? "x" : "-");
					printf("\t%ld",fileStat.st_nlink);
					printf("\t%s",getpwuid(fileStat.st_uid)->pw_name);
					printf("\t%s",getgrgid(fileStat.st_gid)->gr_name);
	
					printf("\t%ld",fileStat.st_size);
					printf("\t%s",format(date,fileStat.st_mtime));
					printf("\t%s\n",dir->d_name);
        		}
		    }
        }
        closedir(d);
    }

    return;



}