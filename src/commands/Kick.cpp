
#include "Kick.hpp"
#include "Messageprocessing.hpp"

Kick::~Kick( void ) {};

int	kickParsingIsCorrect(std::string &msg, Server* server, int fd)
{
    Client*             client = server->getClient(fd);
    Messageprocessing   parameters;
    Nick                nick;

    msg = trimLeft(msg);
    msg = msg.substr(4);
    msg = trimLeft(msg);

    if (client->getHasAuth() && client->
    {
        if (!msg.empty() && msg[0] == ':')//
            msg = msg.substr(1);

        if (msg.empty()) {
            server->sendResp(ERR_NEEDMOREPARAMS(std::string("*"), "KICK"), fd);  // 461
            return;
        }
		std::vector<std::string> params = parameters.split_msg(msg);
		if (params.size() < 4) {
			server->sendResp(ERR_NEEDMOREPARAMS(std::string("*"), "KICK"), fd);  // 461
			return;
		}
	}
	else
		server->sendResp(ERR_NOTREGISTERED(std::string("*")), fd);  // 451
	return (1);
}
/* ------------------- PUBLIC MEMBER FUNCTIONS ------------------*/
/* Syntax KICK message: 
	KICK <channel> <KICK> *( "," <KICK> ) [<comment>]*/
void Kick::execute( Server* server, std::string &msg , int fd)
{
	if (isAuthenticated(server->getClient(fd), server, fd))
	{
		//CHECK PARAMETERS(parsing)
		if (!kickParsingIsCorrect(msg, server, fd))
		{
			server->sendResp(ERR_NEEDMOREPARAMS(std::string("*"), "KICK"), fd);  // 461
			return;
		}
std::cout << "KICK ok" << std::endl;
		// 0.1 Check if the channel exists
		// 0.2 Check if the KICK exists
		// 1. Check if the KICK is in the channel
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