
#include "Kick.hpp"

Kick::~Kick( void ) {};

int	kickParsingIsCorrect(std::string &msg)
{
	// Check if the message is empty
	if (msg.empty())
		return (0);
	// Check if the message has at least 2 parameters
	if (msg.find(" ") == std::string::npos)
		return (0);


	return (1);
}

/* ------------------- PUBLIC MEMBER FUNCTIONS ------------------*/
/* Syntax KICK message: 
	KICK <channel> <user> *( "," <user> ) [<comment>]*/
void Kick::execute( Server* server, std::string &msg , int fd)
{
	if (isAuthenticated(server->getClient(fd), server, fd))
	{
		//CHECK PARAMETERS(parsing)
		if (!kickParsingIsCorrect(msg))
		{
			server->sendResp(ERR_NEEDMOREPARAMS(std::string("*"), "KICK"), fd);  // 461
			return;
		}
std::cout << "KICK ok" << std::endl;
		// 0.1 Check if the channel exists
		// 0.2 Check if the user exists
		// 1. Check if the user is in the channel
		//IF (PERMISO)// 2. Check if the user(OPERATOR) has the permission to kick
			// 3. Kick the user from the channel
			// 4. Send the message to the channel
			// 5. Send the message to the user

		//ELSE(NO PERMISO)
			// 6. Send ERR_CHANOPRIVSNEEDED //482
	}
}

/*
Numeric Replies:
• ERR_NEEDMOREPARAMS (461)
• ERR_NOSUCHCHANNEL (403)
• ERR_CHANOPRIVSNEEDED (482)
• ERR_USERNOTINCHANNEL (441)
• ERR_NOTONCHANNEL (442)
*/