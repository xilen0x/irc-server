#ifndef SERVER_HPP
# define SERVER_HPP

# include <vector>
# include <poll.h>
# include <fcntl.h>
# include <netinet/in.h>
# include "irc.hpp"
# include "Client.hpp"
# include "Channel.hpp"
# include <csignal>

# define BUFFER_SIZE 1024

class Client;
class Channel;

class Server
{
	private:

    	std::string                 _serverName;
	    std::string	                _password;
	    int			                _port;
	    int			                _fdServer;
	    static bool		           	_Signal;
		std::vector<struct pollfd> 	_fdsClients;//fds for poll 
    	std::vector<Client>			_clients;
		std::vector<Channel>		_channels;

        void createSocket();
        void listenSocket();
		void fillPollfd();
		void loop();
		
		void acceptClient();
		void receiveData(int fd);
    
	public:
		void clearClients(int fd, std::string msg);
		Server();
		Server(std::string serverName, std::string password, int port);
		std::string	getServerName( void ) const;
		std::string	getPassword( void ) const;
		int 		getPort( void ) const;
		int			getFdServer( void ) const;
		std::vector<Channel> getChannels( void );
//		std::vector<Client> getClients( void );
		std::vector<Client>& getClients( void );
		Client 		*getClient(int fd);

		size_t		getChannelsSize( void );

		void		addClient( Client newClient );
		void		addChannel( Channel newChannel );  

		void		deleteClient( int fd );
		void		deleteChannel( std::string chName );

		void runServer(void);
		void sendResp(std::string resp, int fd);
		void sendBroad(std::string resp, int fd);

		static void signalsHandler(int signal);
// apardo-m need to be public
//		void clearClients(int fd, std::string msg);

// apardo-m need for QUIT
		void	clearClientFromClientsAndChanels( int fd, std::string msg);

//For test proposal
		Client	*getClientByFD(int fd);
		Channel	*getChannelsByNumPosInVector(size_t pos);

		~Server();
};


#endif
