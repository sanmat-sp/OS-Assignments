//implement pipe operator in c with following functionality
//1. the parent process reads in a file "input.txt" and redirects the output to the pipe
//2. the child process must read the contents of the file and perform a word count


#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<sys/wait.h>
#include<sys/types.h>

#define BUF_SIZE 25
#define Read_END 0
#define WRITE_END 1

int main()
{
	char Read[BUF_SIZE]="";
	int fd[2];
	pid_t pid;
	
	if(pipe(fd) == -1)
	{
		printf("Pipe Failed\n");
		return 1;
	}
    	pid = fork();
	
	if(pid>0)
	{
		FILE *fp;
		fp = fopen("input.txt","r");
        	char buff[20],ch;
        	int i=0;
       	while((ch=fgetc(fp))!=EOF)
       	{
        	    buff[i]=ch;
        	    i++;
       	}
       	buff[i]=0;
        	close(fd[Read_END]);
        	write(fd[WRITE_END],buff,strlen(buff)+1);
        	close(fd[WRITE_END]);
        	wait(NULL);
        	fclose(fp);
	}
	else if(pid==0)
	{
   		int cnt = 0;
    		close(fd[WRITE_END]);
    		read(fd[Read_END],Read,BUF_SIZE);
    		printf("%s\n",Read);
    		char *token = strtok(Read," ");



		while(token!=NULL)
		{
    			cnt++;
    			token = strtok(NULL," ");
		}
		printf("child process read word count: %d\n",cnt);
		close(fd[Read_END]);
	}
	else
	{
  		 printf("Fork Failed\n");
   		 return 1;
   	}
}
 
