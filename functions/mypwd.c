#include "headers.h"
void pwd()
{
	char mypwd[1024];
	getcwd(mypwd,sizeof(mypwd));
	printf("%s\n",mypwd);
}