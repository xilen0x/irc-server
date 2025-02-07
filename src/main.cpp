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
            signal(SIGINT, handleSIGINT);//Ctrl+C
	        signal(SIGQUIT, handleSIGQUIT);//Ctrl+\        /
            signal(SIGPIPE, SIG_IGN);//Ignore SIGPIPE //Cuando un cliente se desconecta inesperadamente.
            if (!parseInput(password, port))
            {
                Server server("ircserv", password, port);
                server.runServer();
                std::cout << "IRC server is running. Press Ctrl+C to stop." << std::endl;
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
