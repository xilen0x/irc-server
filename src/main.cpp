#include <iostream>
#include "Channel.hpp"
#include "Client.hpp"
#include "Messageprocessing.hpp"
#include "Server.hpp"

int main(int argc, char const *argv[])
{
    //signal(SIGINT, signalHandler); here//check if needed
    //signal(SIGTERM, signalHandler); here//check if needed
    //signal(SIGQUIT, signalHandler); here//check if needed
    if (argc == 3)
    {
        int port = std::atoi(argv[1]);
        // std::string serverName = ;
        std::string password = argv[2];

        try
        {
            if (!parseInput(password, port))
            {
                Server server("ircserv", password, port);
                server.runServer();
            }
        }
        catch (const std::exception &e)
        {
            std::cerr << e.what() << '\n';
            //free resources if needed
        }
    }
    else
        std::cerr << "Usage: " << argv[0] << " <port> <password>" << std::endl;
    return (0);
}
