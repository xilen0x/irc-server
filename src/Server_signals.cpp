#include "Server.hpp"

bool Server::_Signal = false;
void Server::signalsHandler(int signal)
{
    (void)signal;
    if (signal == SIGINT)
    {
        std::cout << "\nSIGINT received. \nShutting down the server..." << std::endl;
        _Signal = true;
    }
    else if (signal == SIGQUIT)
    {
        std::cout << "\nSIGQUIT received. \nShutting down the server..." << std::endl;
        _Signal = true;
    }
}
