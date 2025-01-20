#include "Server.hpp"

int main(int argc, char const *argv[])
{
    if (argc == 3)
    {
        int port = std::atoi(argv[1]);
        std::string serverName = "ircserv";
        std::string password = argv[2];
        
        if (port <= 0 || port > 65535)
        {
            std::cerr << "Invalid port number." << std::endl;
            return (1);
        }
        try
        {
            Server server(serverName, password, port);
            server.runServer();
        }
        catch (const std::exception &e)
        {
            std::cerr << e.what() << '\n';
        }
    }
    else
    {
        std::cerr << "Usage: " << argv[0] << " <port> <password>" << std::endl;
    }
    return (0);
}
