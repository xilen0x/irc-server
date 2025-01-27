
#include "Messageprocessing.hpp"
# include <sstream>//
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
#define TEST "TEST"

// Public
Messageprocessing::Messageprocessing( void )
{
	std::cout << "Messageprocessing => Creating _command Map" << std::endl;
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
	std::cout << "~Messageprocessing => Delete _commands" << std::endl;
	for (std::map<std::string, ICommand*>::iterator it = _commands.begin(); it != _commands.end(); ++it)
    {
        delete it->second;
    } 
}

/* ------------------- PUBLIC MEMBER FUNCTIONS ------------------*/

std::vector<std::string> Messageprocessing::split_msg(std::string &msg)
{
	std::vector<std::string> res;
	std::istringstream stream(msg);
	std::string s;
	while (stream >> s)
	{
		res.push_back(s);
		s.clear();
	}
	return (res);
}

void	Messageprocessing::processMessage(std::string message, int fd)
{
	// TODO
	//
	// 1 - Parssing message
	// 2 - Detect COMMAND
	// 3 - Execute COMMAND
	
	std::cout << "processMessage(std:string message) with message = " << message << std::endl;

	std::vector<std::string> str = split_msg(message);
	// if (_commands.find(uppercase(str[0])) != _commands.end())
	// 	_commands[uppercase(str[0])]();
	if (str[0] == TEST)
	{
		this->_commands[TEST]->execute(message, fd);
	}
	else if (str[0] == CAP)
	{
		this->_commands[CAP]->execute(message, fd);
	}
	else if (str[0] == INVITE)
	{
		this->_commands[INVITE]->execute(message, fd);
	}
	else if (str[0] == JOIN)
	{
		this->_commands[JOIN]->execute(message, fd);
	}
	else if (str[0] == KICK)
	{
		this->_commands[KICK]->execute(message, fd);
	}
	else if (str[0] == MODE)
	{
		this->_commands[MODE]->execute(message, fd);
	}
	else if (str[0] == NICK)
	{
		this->_commands[NICK]->execute(message, fd);
	}
	else if (str[0] == PASS)
	{
		this->_commands[PASS]->execute(message, fd);
	}
	else if (str[0] == PING)
	{
		this->_commands[PING]->execute(message, fd);
	}
	else if (str[0] == PRIVMSG)
	{
		this->_commands[PRIVMSG]->execute(message, fd);
	}
	else if (str[0] == QUIT)
	{
		this->_commands[QUIT]->execute(message, fd);
	}
	else if (str[0] == TOPIC)
	{
		this->_commands[TOPIC]->execute(message, fd);
	}
	else if (str[0] == USER)
	{
		this->_commands[USER]->execute(message, fd);
	}
	else
	{
		std::cout << "Command not found" << std::endl;
	}
	
}
