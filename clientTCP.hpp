#pragma once
#include <iostream>
#include <string>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <cstring>
#include <netdb.h>
#include <netinet/in.h> 

#define SERVER_IP "127.0.0.1"
#define BUFFER_SIZE 1024

class Client
{
public:
    ~Client();
    Client(int);
    int connectToServer();
    void post(std::string);
    int get();
    void openSocket();
    std::string getFromBuffer();
    void addToBuffer(std::string);
private:
    int DEFAULT_PORT;
    int client;
    struct sockaddr_in server_address;
    char buffer[BUFFER_SIZE];
};