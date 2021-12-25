#include <iostream>
#include <string>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <cstring>
#include <netdb.h>
#include <netinet/in.h> 

#define DEFAULT_PORT 1601
#define ERROR_S "SERVER ERROR: "
#define BUFFER_SIZE 1024
#define CLIENT_CLOSE_CONNECTION_SYMBOL '#'

class Server
{ 
public:
    
private:
    int client;
    int server;
    struct sockaddr_in server_address;
    char *buffer[BUFFER_SIZE];
};