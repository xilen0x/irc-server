#include <iostream>
#include "Channel.hpp"
#include "Client.hpp"
#include "Messageprocessing.hpp"
#include "Server.hpp"

int main(int argc, char const *argv[])
{
    if (argc == 3)
    {
        int port = std::atoi(argv[1]);
        std::string password = argv[2];

        try
        {
            signal(SIGINT, Server::signalsHandler);
	        signal(SIGQUIT, Server::signalsHandler);
            signal(SIGPIPE, SIG_IGN);
            if (!parseInput(password, port))
            {
                Server server("ircserv", password, port);
                server.runServer();
            }
        }
        catch (const std::exception &e)
        {
            std::cerr << e.what() << '\n';
        }
    }
    else
        std::cerr << "Usage: " << argv[0] << " <port> <password>" << std::endl;
    return (0);
}
