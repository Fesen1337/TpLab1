#include "clientTCP.hpp"

int main(int argc, char* argv[])
{
    int default_port = 1601;
    if(argc > 1)
        default_port = atoi(argv[1]);

    Client client(default_port);


    while(1)
    {
        client.openSocket();
        while(!client.connectToServer())
        {
            std::cout << std::endl;
        }
        
        std::string buffer;
        while(1)
        {
            getline(std::cin, buffer);
            //////////
            std::cout << 0 << std::endl;
            client.post(buffer);
            if(client.get() == 0)
            {
                std::cout << "Server crashed\n";
                break;
            }

            buffer = client.getFromBuffer();
            int s = stoi(buffer);
            for(int i = 0; i < s; i++)
            {
                if(client.get() == 0)
                {
                    std::cout << "Server crashed\n";
                    break;
                }
                buffer = client.getFromBuffer();
                std::cout << buffer << "\n";
            }
            
        }
    }


}