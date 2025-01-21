#include "Server.hpp"

int main(int argc, char const *argv[])
{
    if (argc == 3)
    {
        int port = std::atoi(argv[1]);
        std::string serverName = "ircserv";
        std::string password = argv[2];

        try
        {
            parseInput(serverName, password, port);        
            Server server(serverName, password, port);
            server.runServer();
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
