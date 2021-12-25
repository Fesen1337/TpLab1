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

#define ERROR_S "SERVER ERROR: "
#define BUFFER_SIZE 1024

class Server
{
public:
    Server(int);
    ~Server();
    int openSocket();
    void listenClient();
    void post(std::string);
    int get();
    std::string getFromBuffer();
    void addToBuffer(std::string);
private:
    int DEFAULT_PORT;
    int client;
    int server;
    struct sockaddr_in server_address;
    char buffer[BUFFER_SIZE];
};


Server::Server(int default_port)
{
    DEFAULT_PORT = default_port;
}

void Server::addToBuffer(std::string msg)
{
    for(int i = 0; i < msg.size(); i++)
    {
        buffer[i] = msg[i];
    }
    buffer[msg.size()] = (char)0;
}

std::string Server::getFromBuffer()
{
    std::string ans;
    int i = 0;
    while((int)buffer[i] != 0)
    {
        ans.push_back(buffer[i]);
        i++;

    }
    return ans;
}

Server::~Server()
{
    std::cout << "Closing sockets";
    close(client);
    close(server);
}

void Server::post(std::string msg)
{
    this -> addToBuffer(msg);
    send(server, buffer, BUFFER_SIZE, 0);
}

int Server::get()
{
    return recv(server, buffer, BUFFER_SIZE, MSG_WAITALL);
}


void Server::listenClient()
{
    socklen_t size = sizeof(server_address);
    std::cout << "SERVER: " << "Listening clients... \n";
    listen(client, 1);

    server = accept(client, reinterpret_cast<struct sockaddr*>(&server_address), &size);
    if(server < 0)
    {
        std::cout << ERROR_S << "Cant accepting client.\n";

    }

}

int Server::openSocket()
{
    struct sockaddr_in server_address;
    client = socket(AF_INET, SOCK_STREAM, 0);
    std::cout << client << std::endl;
    if(client < 0)
    {
        std::cout << "SERVER ERROR: establishing socket error.";
        exit(0);
    }

    std::cout << "SERVER: socket for server was successfully created\n";

    server_address.sin_port = htons(DEFAULT_PORT);
    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = htons(INADDR_ANY);

    int ret = bind(client, reinterpret_cast<struct sockaddr*>(&server_address), sizeof(server_address)); 
    if(ret < 0)
    {
        std::cout << ERROR_S << "binding connection. Socket was already been establishing";
        return -1;

    }

}