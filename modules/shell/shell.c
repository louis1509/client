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
  char currentDirectory[100];
  memset(path,0,1035);      // reset to 0 path
  memset(buffer,0,10000);  // reset to 0 buffer
  memset(currentDirectory,0,100);  // reset to 0 currentDirectory

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
  //Setting current direcorty
  getcwd(currentDirectory,100);
  printf("Current Working Directory : %s\n",currentDirectory);
  /***
  * If changing directory
  ***/
  if (strcmp(commandSplittedArray[0],"cd") == 0){
    printf("%s\n", "on passe dans la command cd");
    if(chdir(commandSplittedArray[1]) == -1){
       printf( "Unable to locate the directory: %s\n", commandSplittedArray[1]);
    }else{
        printf("Current Working Directory : %s\n",currentDirectory);
    }

     finalOutput = malloc((strlen(currentDirectory))*sizeof(char));
     if(finalOutput == NULL){
       printf("%s\n", "Failed to allocate memory");
      exit(0);
     }
     strcpy(finalOutput,currentDirectory);
     printf("Final output (path): %s \n", finalOutput);

  }

  /***
  * If creating  a directory
  ***/

  else if(strcmp(commandSplittedArray[0],"mkdir") == 0){
      printf("%s\n", "on passe dans la command mkdir\n");
        printf("le nom du dossier à créer est : %s\n", commandSplittedArray[1]) ;
        char* test;
        test = (char* )malloc((strlen(buffer))*sizeof(char) +1);
        if(test == NULL){
          printf("%s\n", "Failed to allocate memory");
          exit(0);
          }
        strcpy(test,commandSplittedArray[1]);
      int n=mkdir(test);
      if(n==0)
      printf("Directory Created");
      else
      printf("Unable to Create a Directory");

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

         finalOutput = (char* )malloc((strlen(buffer))*sizeof(char) +1);
         if(finalOutput == NULL){
          printf("%s\n", "Failed to allocate memory");
          exit(0);
         }
         strcpy(finalOutput,buffer); //fais peter

     }

      /* close */
      pclose(fp);
    }

  if (finalOutput == NULL){
    printf("%s\n", "finalOutput is NULL");
    return "NULL\n";
  }
  else{
    printf("finalOutput is not null : %s",finalOutput);
    return finalOutput;

  }
  printf("%s\n", "FREE MEMORY");
  free(finalOutput);

}
