#pragma once

#include <iostream>
#include <vector>
#include <poll.h>
#include <fcntl.h>
#include <netinet/in.h>
#include <cstring>
#include <unistd.h>


class Server 
{
	private:

    	std::string                 _serverName;
	    int			                _port;
	    std::string	                _password;
	    int			                _fdServer;
	    //static bool                 _Signal;
    	std::vector<struct pollfd> 	_fdsClients;
    	// std::vector<Client>		_clients;
	    // std::vector<Channel>		_channels;

		//createSocket
        void createSocket();

		//listenSocket
        void listenSocket();
		
		//llenar estruct pollfd 
        void fillPollfd();
		
		// loop	
        void loop();
		
		// //clean
        // void clean();

    public:
		Server();
		Server(int port, std::string password);
		//getters and setters
		

		void runServer();
		~Server();
};