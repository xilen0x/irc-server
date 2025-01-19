#include "../inc/Server.hpp"

int main()
{
    // signal(SIGINT, signalHandler);
	// signal(SIGQUIT, signalHandler);

    Server server;
    
    //check conexion args
    // ...
    try
    {
        server.runServer();        
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        // server.clean();
    }
    return (0);
}
