#include <sstream>

#include "Client.hpp"

// Client::Client() :_fdClient(-1), _ipClient("")
// {}
Client::Client() : _hasPass(false), _hasNick(false), _hasUser(false), _hasAuth(false) 
{

// 250207   Ver si estas 5 lineas se han de cambiar
	this->_nick = "*";
	this->_userName = "*User";  
	this->_realName = "*Real";

	this->_bufferInMessage = "";
	// this->_bufferOutResponse = "";
	this->_fdClient = -1;

//	std::cout << "Client() => Set default values" << std::endl;
}

Client::Client(int fd, std::string ipClient) : _fdClient(fd), _ipClient(ipClient)
{
	//Comment to LIN and CARLOS
	this->_nick = "*";
	this->_userName = "*User";  
	this->_realName = "*Real";

	this->_bufferInMessage = "";
	// this->_bufferOutResponse = "";

	this->_hasPass = false;
	this->_hasNick = false;
	this->_hasUser = false;
	this->_hasAuth = false;

	std::cout << "Client(fp, ipClient) => Set initial values" << std::endl;
}

Client::Client( Client const &src){ *this = src; }

Client &Client::operator=( Client const &src )
{
	if (this != &src)
	{
		this->_fdClient = src._fdClient;	
		this->_ipClient = src._ipClient;
		this->_nick = src._nick;
		this->_userName = src._userName;
		this->_realName = src._realName;
		this->_bufferInMessage = src._bufferInMessage;
		// this->_bufferOutResponse = src._bufferOutResponse;
		this->_hasPass = src._hasPass;
		this->_hasNick = src._hasNick;
		this->_hasUser = src._hasUser;
		this->_hasAuth = src._hasAuth;
	}
	return (*this);
}

Client::~Client( void )
{
	// std::cout << "~Client() => TODO (_fdClient= \"" << this->_fdClient << "\")" << std::endl;
}

int		Client::getFdClient( void ) const { return (this->_fdClient	); }

void	Client::setFdClient( int fd )
{ 
	this->_fdClient = fd; 

//TODO Delete the next lines
	std::ostringstream	str1;


	str1 << fd;
	this->_nick = this->_nick + str1.str();   
}

std::string	Client::getIpClient( void ) const { return ( this->_ipClient ); }

void	Client::setIpClient( std::string ip ) {	this->_ipClient = ip; }

std::string	Client::getNick( void ) const { return ( this->_nick ); }

// Function to get the nick from a user string
std::string	Client::getNickByUser( std::string user ) const
{
	std::string nick = user;
	nick = nick.substr(0, nick.find("!"));
	return (nick);
}

void	Client::setNick( std::string nick ) { this->_nick = nick;}
		
std::string Client::getUserName( void ) const { return ( this->_userName ); }

void	Client::setUserName( std::string user ) { this->_userName = user;}
	
std::string Client::getRealName( void ) const { return ( this->_realName ); }

 void	Client::setRealName( std::string real ) { this->_realName = real ;}

std::string	Client::getBufferInMessage( void ) const { return ( this->_bufferInMessage ); }

void	Client::setBufferInMessage( std::string inMessage ) { this->_bufferInMessage = inMessage; }
	
// std::string	Client::getBufferOutResponse( void ) const { return ( this->_bufferOutResponse ); }

// void	Client::setBufferOutResponse( std::string outResponse ) { this->_bufferOutResponse = outResponse; }

bool	Client::getHasPass( void ) const { return ( this->_hasPass ); }
		
bool	Client::getHasNick( void ) const { return ( this->_hasNick ); }
	
bool	Client::getHasUser( void ) const { return ( this->_hasUser ); }
	
bool	Client::getHasAuth( void ) const { return ( this->_hasAuth ); }
	
void	Client::setHasPass( void ) { this->_hasPass = true; }

void	Client::setHasNick( void ) { this->_hasNick = true; }
		
void	Client::setHasUser( void ) { this->_hasUser = true; }
	
void	Client::setHasAuth( void ) { this->_hasAuth = true; }	

bool 	Client::checkInviteChannel(std::string &channelName)
{
	for (size_t i = 0; i < this->_inviteChannels.size(); i++)
	{
		if (this->_inviteChannels[i] == channelName)
			return true;
	}
	return false;
}

void	Client::addInviteChannel(std::string &channelName)
{
	this->_inviteChannels.push_back(channelName);
}

void	Client::deleteInviteChannel(std::string &channelName)
{
	for (size_t i = 0; i < this->_inviteChannels.size(); i++)
	{
		if (this->_inviteChannels[i] == channelName)
		{
			this->_inviteChannels.erase(this->_inviteChannels.begin() + i);
			return ;
		}
	}
}

// append data to the buffer
void Client::appendToBuffer(const std::string& data) {
    _bufferInMessage += data;
}

// check if the buffer has a complete command
bool Client::hasCompleteCommand() const {
    return (_bufferInMessage.find('\n') != std::string::npos);//if find '\n' and is not at the end of the string return true
}

// extract a command from the buffer
std::string Client::extractCommand() {
    size_t pos = _bufferInMessage.find('\n');//find the first '\n'

    if (pos == std::string::npos) {//if not found
        return ("");
    }
    std::string command = _bufferInMessage.substr(0, pos);//extract the command
    _bufferInMessage.erase(0, pos + 1);//erase the command from the buffer
    return (command);
}

// For debugging
void	Client::printClientVars( void )
{
	std::cout << "----- CLIENT DATA  (start)-----" << std::endl;
	std::cout << "_fdClient = " << this->_fdClient << std::endl; 
	std::cout << "_ipClient = " << this->_ipClient << std::endl;
	std::cout << "_nick = " << this->_nick << std::endl;
	std::cout << "_userName = " << this->_userName << std::endl;
    std::cout << "_realName = " << this->_realName << std::endl;

    std::cout << "_bufferInMessage = " << this->_bufferInMessage << std::endl;
    // std::cout << "_bufferOutResponse = " << this->_bufferOutResponse << std::endl;

    std::cout << "_hasPass = " << this->_hasPass << std::endl;
    std::cout << "_hasNick = " << this->_hasNick << std::endl;
    std::cout << "_hasUser = " << this->_hasNick << std::endl;
    std::cout << "_hasAuth = " << this->_hasAuth << std::endl;
	std::cout << "----- CLIENT DATA  (end)-----" << std::endl;
}
