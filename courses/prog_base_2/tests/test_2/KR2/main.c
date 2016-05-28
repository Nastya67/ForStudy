#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<ctype.h>
#include<windows.h>
#include<winsock2.h>
#include "client.h"
#include <libxml/parser.h>
#include <libxml/tree.h>

#pragma comment(lib,"ws2_32.lib") //Winsock Library
#define NO_FLAGS_SET 0
#define PORT 80
#define MAXBUFLEN 20480

struct stud{
    char student[20];
    char group[8];
    char variant[2];
};

struct stud * stud_parse(char text[200]){
    struct stud * i_am;
    xmlDoc * xDoc;
    xDoc = xmlReadMemory(text, strlen(text), NULL, NULL, 0);
    if (NULL == xDoc) {
        printf("Error parsing xml from memory");
        return NULL;
    }
    xmlNode * HeadElem = xmlDocGetRootElement(xDoc);
    xmlNode * xKids = HeadElem->children;
    for(xKids = HeadElem->children; NULL != xKids && NULL != xKids->next; xKids = xKids->next) {
        if (XML_ELEMENT_NODE == xKids->type) {
            const char * content = xmlNodeGetContent(xKids);
            if(strcmp(xKids->name, "student") == 0)
                strcpy(i_am->student, content);
            else if(strcmp(xKids->name, "group") == 0)
                strcpy(i_am->group, content);
            else if(strcmp(xKids->name, "variant") == 0)
                strcpy(i_am->variant, (content));
        }
    }
    return i_am;
}
char * create_xml(){
    struct stud i_am = {"Nastya_Hradil", "KP-51", "8"};
    xmlDoc * doc = NULL;
	xmlNode * rootNode = NULL;
	xmlNode * studentNode = NULL;
	//xmlNode * groupNode = NULL;
	char strBuf[100];

	doc = xmlNewDoc("1.0");
	rootNode = xmlNewNode(NULL, "stud");
	xmlDocSetRootElement(doc, rootNode);

	xmlNewChild(rootNode, NULL, "student", i_am.student);
	xmlNewChild(rootNode, NULL, "group", i_am.group);
	xmlNewChild(rootNode, NULL, "variant", i_am.variant);

	xmlBuffer * bufferPtr = xmlBufferCreate();
	xmlNodeDump(bufferPtr, NULL, (xmlNode *)doc, 0, 1);
	//printf("%s", (const char *)bufferPtr->content);
	return (char*)bufferPtr->content;
	/*xmlBufferFree(bufferPtr);

    xmlFreeDoc(doc);
	xmlCleanupParser();*/
}

char * read_file(char * name, char * text){
    FILE * file = fopen(name, "r");
    char line[50];
    //char text[200] = "";
    while(fgets(line, 100, file)) {
        strcat(text, line);
    }
    //printf("%s", text);
    //return &text;
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

    char * i_am = create_xml();
    send_request1(recvSocket, host_name, i_am);

    //Sending request 2
    send_request2(recvSocket,host_name, buffer);

    //Receiving the answer
    rec_answer (recvSocket, buffer);
    //printf("%s", buffer);
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


    return 0;
}


