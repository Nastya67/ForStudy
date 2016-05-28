#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<ctype.h>
#include<windows.h>
#include<winsock2.h>
#include "client.h"

#pragma comment(lib,"ws2_32.lib") //Winsock Library
#define NO_FLAGS_SET 0
#define PORT 80
#define MAXBUFLEN 20480

char * read_file(char * name){
    FILE * file = fopen(name, "r");

    char line[50];
    char text[200] = "";
    while(fgets(line, 100, file)) {
        strcat(text, line);
    }
    printf("%s", text);
    return &text;
}


int main(int argc , char *argv[])
{
    WSADATA Data;
    SOCKADDR_IN recvSockAddr;
    SOCKET recvSocket;
    int status;
    int numrcv = 0;
    struct hostent * remoteHost;
    char * ip;
    char string [100];
    const char * host_name = "pb-homework.appspot.com";
    char buffer[MAXBUFLEN];
    memset(buffer,0,MAXBUFLEN);

    // Initialize Windows Socket DLL
    //printf ("Initializing Socket");
    status = WSAStartup(MAKEWORD(2, 2), &Data);
    if(status != 0)    {
        printf("ERROR: WSAStartup unsuccessful\r\n");
        return 0;
    }
   // printf ("Initialized");

	// Get IP address from host name
	remoteHost = gethostbyname(host_name);
	ip = inet_ntoa(*(struct in_addr *)*remoteHost->h_addr_list);
	printf("IP address is: %s.\n", ip);
	recvSockAddr = get_Addr (ip);

    //Creating new socket
    recvSocket = socket_new ();

    //Connecting
    con_to_serv (recvSocket, recvSockAddr);

    read_file("stud.xml");

    //Sending request 1
    //send_request1(recvSocket, host_name);



    //Receiving the answer
    //rec_answer (recvSocket, buffer);

    //Sending request 2
    //send_request2(recvSocket,host_name, buffer);

    //Receiving the answer
    //rec_answer (recvSocket, buffer);

    //Function
    //strcpy(string, Max_word (buffer));

    //Sending request 3
    //send_request3(recvSocket,host_name, string);

    //Receiving the answer
    //rec_answer (recvSocket, buffer);

    //Looking for answer
    //printf ("\n The result is: %s\n", buffer);

    //Closing socket
    closesocket(recvSocket);

    WSACleanup();

    getchar();

    return 0;
}


