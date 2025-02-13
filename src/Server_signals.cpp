#include "Server.hpp"

bool Server::_Signal = false;
void Server::signalsHandler(int signal)
{
    (void)signal;
    if (signal == SIGINT)//Ctrl+C
    {
        std::cout << "\nSIGINT received. \nShutting down the server..." << std::endl;
        _Signal = true;
    }
    else if (signal == SIGQUIT)//Ctrl+\    /
    {
        std::cout << "\nSIGQUIT received. \nShutting down the server..." << std::endl;
        _Signal = true;
    }
}
