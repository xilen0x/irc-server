
#ifndef CLIENT_HPP
# define CLIENT_HPP

# include <iostream>
# include "Server.hpp"

class Client
{
	private:
		int			_fdClient;//file descriptor of the client
		std::string	_ipClient;

		std::string	_nick;
		std::string _userName;
		std::string _realName;

		std::string	_bufferInMessage;
		std::string	_bufferOutResponse;

		bool		_hasPass;
		bool		_hasNick;
		bool		_hasUser;
		bool		_hasAuth;	  // Athenticated user with  password, nick, USER

		std::vector<std::string> _inviteChannels; // the channels list that invite the client
							   

	public:
		Client( void );
		Client( int fd, std::string ipClient );
		Client( Client const &src );
		Client &operator=( Client const &src );
		~Client( void );

		int			getFdClient( void ) const;
		void		setFdClient( int fd );
		std::string	getIpClient( void ) const;
		void		setIpClient( std::string ip );

		std::string	getNick( void ) const;
		std::string	getNickByUser( std::string user ) const;
		void		setNick( std::string nick );
		std::string getUserName( void ) const;
		void		setUserName( std::string user );
		std::string getRealName( void ) const;
		void		setRealName( std::string real ) ;

		std::string	getBufferInMessage( void ) const;
		void		setBufferInMessage( std::string inMessage ) ;
		std::string	getBufferOutResponse( void ) const;
		void 		setBufferOutResponse( std::string outResponse ) ;

		bool		getHasPass( void ) const;
		bool		getHasNick( void ) const;
		bool		getHasUser( void ) const;
		bool		getHasAuth( void ) const;	
		void		setHasPass( void );
		void		setHasNick( void );
		void		setHasUser( void );
		void		setHasAuth( void );	

		bool 		checkInviteChannel(std::string &channelName);
		void		addInviteChannel(std::string &channelName);
		void		deleteInviteChannel(std::string &channelName);

		// for handling the buffer(ctrl-d)
		void appendToBuffer(const std::string& data);
		bool hasCompleteCommand() const;
		std::string extractCommand();

// For debugging
		void		printClientVars( void ); 
};

#endif
