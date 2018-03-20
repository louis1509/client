#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "shell.h"


char* shellcommand(char* command )
{
  printf("test du shell... : \n");
  FILE *fp;
  char path[1035];          
  char buffer[10000];       // Buffer
  char* finalOutput = NULL; // Final result
  char* commandSplitted;   // Command splitted to check if cd  
  char* commandSplittedArray[2];
  memset(path,0,1035);      // reset to 0 path
  memset(buffer,0,10000);   // reset to 0 buffer

  int i =0;
 
  /**
  Spliting command to see if there is change directory (cd)
  **/
  commandSplitted = strtok (command," ,.-");
  while (commandSplitted != NULL)
  {
    commandSplittedArray[i] = commandSplitted;
    commandSplitted = strtok (NULL, " "); 
    i++;
  }
  printf("0 %s\n", commandSplittedArray[0]);
  printf("1 %s\n", commandSplittedArray[1]);

  //If changing directory 
  if (strcmp(command,"cd") == 0){
    chdir("C:");
    char st[80];
    getcwd(st,80);
    printf("Current Working Directory : %s",st);
   
  }
   /* Open the command for reading. */
  else{
      fp = popen(command, "r");
      if (fp == NULL) {
        printf("Failed to run command\n" );
        exit(1);
      }
      else {
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
    }

  if (finalOutput == NULL){
    return 'NULL';
  }
  else{
    return finalOutput;
  }
  
}
