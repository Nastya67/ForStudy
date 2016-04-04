#include<stdio.h>
#include<winsock2.h>
#include <ctype.h>

#pragma comment(lib,"ws2_32.lib") //Winsock Library

#define NO_FLAGS_SET 0
#define PORT 80
#define SIZE_M 2000

void request_to_serv(SOCKET s, char * address, char * myVar, char * dop_arg, char * server_repl){
    char request[200];
    int numrcv;
    int status;
    char server_reply[SIZE_M];
    //printf("%s\n", dop_arg);
    if(dop_arg == NULL){
        sprintf(request, "GET %s HTTP/1.1\r\nHost:%s\r\n\r\n", myVar, address);  // add Host header with host_name value
    }
    else{
        sprintf(request, "GET %s?%s HTTP/1.1\r\nHost:%s\r\n\r\n", myVar, dop_arg, address);  // add Host header with host_name value
    }
    send(s, request, strlen(request), 0);

	// Receieve
    numrcv = recv(s, server_reply, SIZE_M, NO_FLAGS_SET);
    if (numrcv == SOCKET_ERROR)
    {
        printf("ERROR: recvfrom unsuccessful\r\n");
        status = closesocket(s);
        if(status == SOCKET_ERROR)
			printf("ERROR: closesocket unsuccessful\r\n");
        status = WSACleanup();
        if (status == SOCKET_ERROR)
			printf("ERROR: WSACleanup unsuccessful\r\n");
        system("pause");
        return(1);
    }
	server_reply[numrcv] = '\0';
    strcpy(server_repl, server_reply);
}
char * search_repl(char server_repl[100]){
    char cl[] = "Content-Length:";
    char * toSearch = strstr(server_repl, cl);
    int tmp = 0, i;
    for(i = 0; tmp < 2 || i < strlen(toSearch); i++){
        toSearch++;
        if(toSearch[0] == '\n'){
            tmp++;
        }
    }
    toSearch++;
    //printf("%s\n", toSearch);
    return toSearch;
}
int count(char str[]){
    int count = 0;
    int i;
    for(i = 0; str[i] != '\0'; i++){
        if(isspace(str[i]) && isalpha(str[i+1]))
            count++;
    }
    count++;
    return count;
}
int main(int argc , char *argv[]){
    WSADATA wsa;
    SOCKET s;
    struct sockaddr_in server;
    char *message , server_reply[SIZE_M];
    int status;
    int numrcv = 0;

   // printf("\nInitialising Winsock...");
    if (WSAStartup(MAKEWORD(2,2),&wsa) != 0){
        printf("Failed. Error Code : %d",WSAGetLastError());
        return 1;
    }
    //Create a socket
    if((s = socket(AF_INET , SOCK_STREAM , 0 )) == INVALID_SOCKET){
        printf("Could not create socket : %d" , WSAGetLastError());
    }
    struct hostent * host;
    char * address = "pb-homework.appspot.com";
    char * myVar = "/var/5";
    char * ip;

    if ((host = gethostbyname(address) ) == NULL){
        printf("get host by name failed : %d" , WSAGetLastError());
        return 1;
    }
    ip = inet_ntoa(*(struct in_addr *)*host->h_addr_list);
	printf("IP address is: %s\n", ip);
    memset(&server, 0, sizeof(server));
    server.sin_port = htons(PORT);
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = inet_addr(ip);

    //Connect to remote server
    if(connect(s, (struct sockaddr *)&server , sizeof(server)) < 0){
        puts("connect error");
        return 1;
    }

    char * server_repl = malloc(sizeof(char)*SIZE_M);
    request_to_serv(s, address, myVar, NULL, server_repl);
    char * answer;
    answer = search_repl(server_repl);
    char cur_address[50];
    sprintf(cur_address, "%s%s?5s", address, myVar, answer);
    request_to_serv(s, address, myVar, answer, server_repl);
    answer = search_repl(server_repl);
   // printf("%s\n", answer);
    int num_word = count(answer);
   // printf("%i", num_word);
    char result[10];
    sprintf(result, "result=%i", num_word);
    char request[200];

    sprintf(request, "POST %s%s HTTP/1.1\r\nContent-Length: %d\r\n\r\n%s", address, myVar, strlen(result), result);
    printf("send: \n%s\n\n", request);
    send(s, request, strlen(request), 0);

    numrcv = recv(s, server_reply, SIZE_M, NO_FLAGS_SET);
    if (numrcv == SOCKET_ERROR){
        printf("ERROR: recvfrom unsuccessful\r\n");
        status = closesocket(s);
        if(status == SOCKET_ERROR)
			printf("ERROR: closesocket unsuccessful\r\n");
        status = WSACleanup();
        if (status == SOCKET_ERROR)
			printf("ERROR: WSACleanup unsuccessful\r\n");
        system("pause");
        return(1);
    }
	server_reply[numrcv] = '\0';
	printf("get: \n%s", server_repl);

    closesocket(s);
    WSACleanup();
    printf("\n\n:(\n");

    return 0;
}
