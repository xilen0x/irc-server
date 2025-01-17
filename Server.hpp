#pragma once
#include <iostream>
#include <vector>

class Server 
{
	private:

    	std::string                 _serverName;
	    int			                _port;
	    std::string	                _password;
	    int			                _fdServer;
	    static bool                 _Signal;
    	std::vector<struct pollfd> 	_fdsClients;
    	// std::vector<Client>		_clients;
	    // std::vector<Channel>		_channels;

		//Server(); //private or public?

    public:

		//getters and setters

		//createSocket

			//bindSocket with port and ip

			//listenSocket

			//llenar estruct pollfd 

			//server connected!

		// loop	
			
			//poll

			//accept

			//recv

			//send

			//close

		//clean

		~Server();
};