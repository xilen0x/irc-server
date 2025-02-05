#ifndef SERVER_HPP
# define SERVER_HPP

# include <vector>
# include <poll.h>
# include <fcntl.h>
# include <netinet/in.h>
# include "irc.hpp"
# include "Client.hpp"
# include "Channel.hpp"

class Client;
class Channel;

class Server
{
	private:

    	std::string                 _serverName;
	    std::string	                _password;
	    int			                _port;
	    int			                _fdServer;
	    //static bool                 _Signal;
		std::vector<struct pollfd> 	_fdsClients;
    	std::vector<Client>			_clients;
		std::vector<Channel>		_channels;

        void createSocket();
        void listenSocket();
		void fillPollfd();
		void loop();
		
		void acceptClient();
		void receiveData(int fd);
	//	void clearClients(int fd, std::string msg);
    
	public:

		Server(std::string serverName, std::string password, int port);

		std::string	getServerName( void ) const;
		std::string	getPassword( void ) const;
		int 		getPort( void ) const;
		int			getFdServer( void ) const;
		std::vector<Channel> getChannels( void );
//		std::vector<Client> getClients( void );
		std::vector<Client>& getClients( void );
		Client 		*getClient(int fd);

		void		addClient( Client newClient );
		void		addChannel( Channel newChannel );  
		
		void		delClient( int fd );

		void runServer(void);
		void sendResp(std::string resp, int fd);
		void sendBroad(std::string resp, int fd);

// apardo-m need to be public
		void clearClients(int fd, std::string msg);

// apardo-m need for QUIT
		void deleteClientFromAnyChannel(int fd);

//For test proposal
		Client	*getClientByFD(int fd);
		Channel	*getChannelsByNumPosInVector(int pos);

		~Server();
};

void deleteRN(std::string &msg);
int	 parseInput(std::string password, int port);
std::vector<std::string> splitByDoublePoint(const std::string & msg);
std::string trimLeft(std::string &str);
std::string uppercase(std::string &s);

#endif
