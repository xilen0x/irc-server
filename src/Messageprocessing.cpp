
# include "Messageprocessing.hpp"
# include <sstream>
# include "replies.hpp"

#define CAP "CAP"
#define INVITE "INVITE"
#define JOIN "JOIN"
#define KICK "KICK"
#define MODE "MODE"
#define NICK "NICK"
#define PASS "PASS"
#define PING "PING"
#define PRIVMSG "PRIVMSG"
#define TOPIC "TOPIC"
#define USER "USER"
#define QUIT "QUIT"

Messageprocessing::Messageprocessing( void )
{
	this->_commands[CAP] = new Cap();
	this->_commands[INVITE] = new Invite();
	this->_commands[JOIN] = new Join();
	this->_commands[KICK] = new Kick();
	this->_commands[MODE] = new Mode();
	this->_commands[NICK] = new Nick();
 	this->_commands[PASS] = new Pass();
	this->_commands[PING] = new Ping();
	this->_commands[PRIVMSG] = new Privmsg();
	this->_commands[TOPIC] = new Topic();
	this->_commands[USER] = new User();
	this->_commands[QUIT] = new Quit();
}

Messageprocessing::~Messageprocessing( void )
{
	for (std::map<std::string, ICommand*>::iterator it = _commands.begin(); it != _commands.end(); ++it)
    {
        delete it->second;
    } 
}

void Messageprocessing::processMessage(Server* server, std::string message, int fd)
{
 	std::vector<std::string> str = split_msg(message);
	if (str.empty())
	{
		// std::cout << "[LOG][INFO] Empty message" << RES << std::endl;//debug
		return ;
	}
	if (this->_commands.find(uppercase(str[0])) != this->_commands.end())
		this->_commands[uppercase(str[0])]->execute(server, message, fd);
	else if (!isAuthenticated(server->getClient(fd), server, fd))
		return ;
}
