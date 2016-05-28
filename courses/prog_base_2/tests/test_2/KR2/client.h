#ifndef CLIENT_H_INCLUDED
#define CLIENT_H_INCLUDED

SOCKET socket_new(void);
void con_to_serv (SOCKET recvSocket, SOCKADDR_IN recvSockAddr);
void send_request1(SOCKET recvSocket, const char * host_name, const char * text);
void rec_answer (SOCKET recvSocket, char * buffer);
void send_request2(SOCKET recvSocket, const char * host_name, char * buffer);
void send_request3(SOCKET recvSocket, const char* host_name, char * word);
SOCKADDR_IN get_Addr(char * ip);
char * Max_word(char *message);


#endif // CLIENT_H_INCLUDED
