#include "clientTCP.hpp"

Client::Client(int default_port)
{
    DEFAULT_PORT = default_port;
}

Client::~Client()
{
    close(client);
}

int Client::get()
{
    return recv(client, buffer, BUFFER_SIZE, MSG_WAITALL);
}

void Client::addToBuffer(std::string msg)
{
    for(int i = 0; i < msg.size(); i++)
    {
        buffer[i] = msg[i];
    }
    buffer[msg.size()] = (char)0;
}

std::string Client::getFromBuffer()
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


void Client::post(std::string msg)
{
    this -> addToBuffer(msg);
    send(client, buffer, BUFFER_SIZE, 0);
}

void Client::openSocket()
{
    client = socket(AF_INET, SOCK_STREAM, 0);
    if(client < 0)
    {
        std::cout << "SERVER ERROR: establishing socket error.";
        exit(0);
    }
    server_address.sin_port = htons(DEFAULT_PORT);
    server_address.sin_family = AF_INET;
    inet_pton(AF_INET, SERVER_IP, &server_address.sin_addr);
    
    std::cout << "\n=> Client socket created\n";
}

int Client::connectToServer()
{
    int ret = connect(client, reinterpret_cast<const struct sockaddr*>(&server_address), sizeof(server_address));
    long long q = 0;
    while(ret == -1)
    {
        ret = connect(client, reinterpret_cast<const struct sockaddr*>(&server_address), sizeof(server_address));
        q++;
        if(q > 1000000)
        {
            std::cout << "server is not responding";
            return 0;

        }   
            
    }
    recv(client, buffer, BUFFER_SIZE, 0);

    std::cout << "=> Connection established.\n";
    return 1;
}