#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "shell.h"


char* shellcommand(char* command )
{
  printf("test du shell... : \n");
  FILE *fp;
  char path[1035];
  char buffer[10000];
  char *finalOutput = NULL;
  memset(path,0,1035);
  memset(buffer,0,10000);
  /* Open the command for reading. */
  fp = popen(command, "r");
  if (fp == NULL) {
    printf("Failed to run command\n" );
    exit(1);
  } else {
    /* Read the output a line at a time - output it. */
    while (fgets(path, sizeof(path)-1, fp) != NULL) {
     
      printf("%s", path);
      strcat(buffer,path);
    }

     printf("BUFFER : \n");
     printf("%s\n", buffer);
     int size = strlen(buffer)*sizeof(char);
     printf("size of the buffer : %d\n", size);

     finalOutput = malloc((strlen(buffer))*sizeof(char));
     strcpy(finalOutput,buffer);
 }

  /* close */
  pclose(fp);

  return finalOutput;
}
