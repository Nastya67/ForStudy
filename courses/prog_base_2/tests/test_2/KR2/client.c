 #include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<ctype.h>
#include<windows.h>
#include<winsock2.h>
#include <libxml/parser.h>
#include <libxml/tree.h>

#pragma comment(lib,"ws2_32.lib") //Winsock Library
#define NO_FLAGS_SET 0
#define PORT 80
#define MAXBUFLEN 20480


 SOCKET socket_new(void) {
     SOCKET recvSocket  = socket(AF_INET , SOCK_STREAM,  IPPROTO_TCP);
     if( recvSocket == INVALID_SOCKET)
    {
        printf("Could not create socket : %d" , WSAGetLastError());
    }
    printf("Socket created.\n");
    return recvSocket;
}

void con_to_serv (SOCKET recvSocket, SOCKADDR_IN recvSockAddr){
    if(connect(recvSocket,(SOCKADDR*)&recvSockAddr,sizeof(SOCKADDR_IN)) == SOCKET_ERROR){
        printf("ERROR: socket could not connect\r\n");
        closesocket(recvSocket);
        WSACleanup();
    }
}

void send_request1(SOCKET recvSocket, const char * host_name, const char text[200]){
    char request[200] = "";
    send(recvSocket, text, strlen(text), 0);
}

void rec_answer (SOCKET recvSocket, char * buffer){
    int numrcv = recv(recvSocket, buffer, MAXBUFLEN, NO_FLAGS_SET);
    printf("%s\n", buffer);
	if (numrcv == SOCKET_ERROR)
	{
		printf("ERROR: recvfrom unsuccessful\r\n");
		int status = closesocket(recvSocket);
		if (status == SOCKET_ERROR)
			printf("ERROR: closesocket unsuccessful\r\n");
		status = WSACleanup();
		if (status == SOCKET_ERROR)
			printf("ERROR: WSACleanup unsuccessful\r\n");
		system("pause");
		return(1);
	}
}

void send_request2(SOCKET recvSocket, const char * host_name, char * buffer){
    char request[200];
    sprintf(request, "GET /test/var/8?format=xml HTTP/1.1\r\nHost:%s\r\n\r\n", host_name);  // add Host header with host_name value
    printf("Request: %s\n", request);
    send(recvSocket, request, strlen(request), 0);
}
void send_request3(SOCKET recvSocket, const char* host_name, char * word){
	char request[200];
	char imp [50];
	printf("The max-length word is: %s\n", word);
	sprintf(imp, "result=%s", word);
	sprintf(request, "POST %s/var/4 HTTP/1.0\r\nContent-length: %d\r\n\r\n%s", host_name, strlen(imp), imp);
		//"Host: %s\r\n"
    send(recvSocket, request, strlen(request), 0);
}

SOCKADDR_IN get_Addr(char * ip)
{
    SOCKADDR_IN recvSockAddr;
    memset(&recvSockAddr, 0, sizeof(recvSockAddr));
    recvSockAddr.sin_port=htons(PORT); // specify the port portion of the address
    recvSockAddr.sin_family=AF_INET; // specify the address family as Internet
    recvSockAddr.sin_addr.s_addr= inet_addr(ip); // specify ip address
    return recvSockAddr;
}
