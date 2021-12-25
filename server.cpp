#include <iostream>
#include <string>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <cstring>
#include <netdb.h>
#include <netinet/in.h> 
#include <thread>
#include <vector>
#include <mutex>

#include "parser.hpp"

#define DEFAULT_PORT 1601
#define ERROR_S "SERVER ERROR: "
#define BUFFER_SIZE 1024
#define CLIENT_CLOSE_CONNECTION_SYMBOL '#'

int client, server;
char buffer[BUFFER_SIZE];

std::mutex mtx;

void clientHandler(int ser)
{
    std::vector<std::string>ans;
    std::string b;
    Parser p;
    char buf[BUFFER_SIZE];
    while(1)
    {
        b.clear();
        if(recv(ser, buf, BUFFER_SIZE, 0) == -1)
            break;
        if(buf[0] == '#')
            break;
        std::cout << ser << " " << buf << std::endl;

        
        int i = 0;
        while((int)buf[i] != 0)
        {
            b.push_back(buf[i]);
            i++;
        }

        mtx.lock();
        p.getQuery(b);
        ans = p.getAns();
        mtx.unlock();

        b = std::to_string(ans.size());

        strcpy(buf, b.c_str());

        send(ser, buf, BUFFER_SIZE, 0);

        for(int i = 0; i < ans.size(); i++)
        {
            strcpy(buf, ans[i].c_str());
            send(ser, buf, BUFFER_SIZE, 0);
        }
    }
    
}

int main(int argc, char* argv[])
{

    struct sockaddr_in server_address;
    client = socket(AF_INET, SOCK_STREAM, 0);
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
        return 0;

    }   

    socklen_t size = sizeof(server_address);
    std::cout << "SERVER: " << "Listening clients... \n";
    listen(client, SOMAXCONN);

    while(1)
    {
        server = accept(client, reinterpret_cast<struct sockaddr*>(&server_address), &size);
        if(server < 0)
        {
            std::cout << ERROR_S << "Cant accepting client.\n";

        }
        
        strcpy(buffer, "server connected\n");
        send(server, buffer, BUFFER_SIZE, 0);

        std::thread *t = new std::thread(clientHandler, server);
        t -> detach();
    }


}
