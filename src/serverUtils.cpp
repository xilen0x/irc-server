#include "Server.hpp"

int parseInput(std::string serverName, std::string password, int port)
{
        (void)serverName;
        (void)password;
        
        if (port <= 0 || port > 65535)
        {
            std::cerr << "Invalid port number." << std::endl;
            return (1);
        }
        //... other checks





        return (0);
}