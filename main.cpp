#include "Server.hpp"

int main()
{
    // signal(SIGINT, signalHandler);
	// signal(SIGQUIT, signalHandler);

    Server server;
    
    //check conexion args
    // ...
    try
    {
        server::createSocket();
        // server.bindSocket();
        // server.listenSocket();
        // server.fillPollfd();
        // server.serverConnected();
        // server.loop();
        // server.clean();
        
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        // server.clean();
    }
    return (0);
}
