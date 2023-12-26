//write a c program to change the permissions of files in a directory created after a certain date. Inputs to the program : directory, date and new permissions to be set as run time arguments.
#include<stdio.h>
#include<dirent.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<time.h>
#include<string.h>
#include<stdlib.h>
int main(){
	DIR *dir;
	struct dirent *dirent;
	struct stat statbuf;
	char path[100];
	char date[100];
	printf("Enter the path: ");
	scanf("%s", path);
	printf("Enter the date in dd/mm/yyyy format: ");
	scanf("%s", date);
	printf("Enter access modes as a 4 digit number:");
	int mode = scanf("%d", &mode);
	dir = opendir(path);
	if(dir == NULL)
	{
		printf("Error in opening the directory\n");
		return 1;
	}
	while((dirent = readdir(dir)) != NULL)
	{
		if(stat(dirent->d_name,&statbuf) == -1)
		{
			printf("Error in stat\n");
			return 1;
		}
		if(strcmp(date,ctime(&statbuf.st_ctime)) <= 0)
		{
			printf("%s\n", dirent->d_name);
			chmod(path, mode);
		}
	}
	closedir(dir);
	return 0;
}