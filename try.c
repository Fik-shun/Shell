#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>

int main(void)
{
        int     fd[2], nbytes;
        pid_t   childpid;
        char    string[50];
        char    string2[50];
        char    readbuffer[80];

        pipe(fd);
        
        scanf("%s %s",string,string2);
                        if((childpid = fork()) == -1)
        {
                perror("fork");
                exit(1);
        }

        if(childpid == 0)
        {
                close(fd[0]);
                dup2(fd[1],1);
                // close(1);
                /* Child process closes up input side of pipe */
                // dup2(0, fd[0]);
                /* Send "string" through the output side of pipe */
                printf("%s",string);
                // write(fd[1], string2, (strlen(string2)+1));
                exit(0);
        }
        else
        {
                 // Parent process closes up output side of pipe 
                // dup2(fd[1],1);
                nbytes = read(fd[0], readbuffer, sizeof(readbuffer));
                printf("Received string: %s\n", readbuffer);

                close(fd[1]);
                dup2(fd[0],0);
                // dup2(1,fd[0]);
                // dup2(fd[1],0);

                // char *argv[101];
                // argv[0] = "grep";
                // argv[1] = "g";
                // argv[2] = NULL;
                // // printf("%s\n",argv[0]);
                // execvp(argv[0],argv);
                printf("hi1\n");
                /* Read in a string from the pipe */
        }
        return(0);
}

//input aayeg toh in mei
//in close krdiya
//if piping: out = p[1], in = p[0]
//output jaayega  out mei
//out close kiya
//fork
//child->execute
//parent->wait forc hild,
//0,1 normal




// stdout_copy = dup(1);//out ki copy
// close(1);//out band
// open(file1)



// close(file1);
// dup2(stdout_copy, 1); //out vapis uski copy mei
// close(stdout_copy);//copy band