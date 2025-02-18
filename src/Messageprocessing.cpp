
#include "Messageprocessing.hpp"
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
#define TEST "TEST"  // Delete before close project


// Public
Messageprocessing::Messageprocessing( void )
{
	// std::cout << "Messageprocessing => Creating _command Map" << std::endl;
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
	//std::cout << "~Messageprocessing => Delete _commands" << std::endl;
	for (std::map<std::string, ICommand*>::iterator it = _commands.begin(); it != _commands.end(); ++it)
    {
        delete it->second;
    } 
}

/* ------------------- PUBLIC MEMBER FUNCTIONS ------------------*/

// std::vector<std::string> Messageprocessing::split_msg(std::string &msg)
// {
// 	std::vector<std::string> res;
// 	std::istringstream stream(msg);
// 	std::string s;
// 	while (stream >> s)
// 	{
// 		res.push_back(s);
// 		s.clear();
// 	}
// 	return (res);
// }

/*
char to_upper(char c)
{
	return (std::toupper(static_cast<unsigned char>(c)));
}

std::string uppercase(std::string &s)
{
	std::transform(s.begin(), s.end(), s.begin(), to_upper);
	return (s);
}
*/

// void	Messageprocessing::processMessage(std::string message, int fd)
// {
// 	// TODO
// 	//
// 	// 1 - Parssing message
// 	// 2 - Detect COMMAND
// 	// 3 - Execute COMMAND
// 	(void)fd;
// 	std::cout << "processMessage(std:string message) with message = " << message << std::endl;

// 	std::vector<std::string> str = split_msg(message);
// 	if (this->_commands.find(uppercase(str[0])) != this->_commands.end())
// 		this->_commands[uppercase(str[0])]->execute(message, fd);

// }

void Messageprocessing::processMessage(Server* server, std::string message, int fd)
{
 	std::vector<std::string> str = split_msg(message);
	if (str.empty())
	{
		std::cout << YEL << "Empty message" << RES << std::endl;//debug
		return ;
	}
	if (this->_commands.find(uppercase(str[0])) != this->_commands.end())
		this->_commands[uppercase(str[0])]->execute(server, message, fd);
	else if (!isAuthenticated(server->getClient(fd), server, fd))
	{
		// server->sendResp(ERR_NEEDMOREPARAMS(std::string("*"), "MODE"), fd);
		return ;
	}
}
