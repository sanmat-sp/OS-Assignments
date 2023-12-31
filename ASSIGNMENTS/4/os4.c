// Write a C program to list all the files that have been created after a certain date. Inputs to the program : directory and date
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>
#include <time.h>

int main () {
  DIR *d;
  struct dirent *dir;
  struct stat stats;
  struct tm dt;

  char dirname[256];
  printf("Enter directory ('.' for current directory): "); fflush(stdout);
  scanf("%s", dirname);
  d = opendir(dirname);

  int dd, mm, yyyy;
  printf("Enter date: "); fflush(stdout);
  scanf("%d", &dd);
  printf("Enter month: "); fflush(stdout);
  scanf("%d", &mm);
  printf("Enter year: "); fflush(stdout);
  scanf("%d", &yyyy);

  if (!d) {
    printf("Error opening directory!");
    exit(0);
  }

  while ((dir = readdir(d))) {
    if (stat(dir->d_name, &stats) == 0) {
      dt = *gmtime(&stats.st_ctime);
      int d = dt.tm_mday;
      int m = dt.tm_mon+1;
      int y = dt.tm_year + 1900;

      if (yyyy < y)
        printf("File: %s\n", dir->d_name);
      else if (yyyy == y && mm < m)
        printf("File: %s\n", dir->d_name);
      else if (yyyy == y && mm == m && dd < d)
        printf("File: %s\n", dir->d_name);
    }
    else
      printf("Couldn't read file properties of file: %s", dir->d_name);
  }
  closedir(d);

  return 0;
}