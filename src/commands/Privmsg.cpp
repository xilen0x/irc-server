
#include "Privmsg.hpp"

Privmsg::~Privmsg( void ) {};

/* ------------------- PUBLIC MEMBER FUNCTIONS ------------------*/


void Privmsg::execute( Server* server, std::string &msg , int fd)
{
	std::vector<std::string>	str;
	std::vector<std::string>	splitedStrVect;
	Client						*cl;
	std::string					nick;
	std::string					target;
	Channel						*ch;

	if (isAuthenticated(server->getClient(fd), server, fd))
	{
		cl = server->getClientByFD(fd);
		nick = cl->getNick();
		deleteRN(msg);
		splitedStrVect = splitByDoublePoint(msg);
		str = split_msg(splitedStrVect[0]);
		if (str.size() == 1)
		{
			server->sendResp(ERR_NEEDMOREPARAMS(nick, "PRIVMSG"), fd);  // 461 
			return;
		}
		else if (str.size() > 2)
		{
			server->sendResp(FAIL_LOTPARAMS(msg), fd);
			return;
		}
		if ((str[1][0] == '#' || str[1][0] == '&'))
		{
			str[1] = str[1].substr(1);
			if (!server->isInChannels(str[1])) 
			{
				server->sendResp(ERR_NOSUCHNICK(("#" + str[1])), fd); // 401
				return;
			}
			ch = server->getChannelByChanName(str[1]);
			if (!ch->isOpe(nick) && !ch->isMem(nick))
			{
				server->sendResp(ERR_USERNOTINCHANNEL(nick, str[1]), fd); // 441
				return;
			}
			if (splitedStrVect.size() == 1)
			{
				server->sendResp(ERR_NOTEXTTOSEND(nick), fd); // 412
				return;
			}
			server->sendBroadOthersInChannel(MSG_PRIVMSG_TO_CHANNEL(cl->getNick(), str[1], splitedStrVect[1]), ch, fd);
		}
		else
		{
			str[1] = uppercase(str[1]);
			if (!server->isInClients(str[1])) 
			{
				server->sendResp(ERR_NOSUCHNICK(str[1]), fd); // 401
				return;
			}
			if (splitedStrVect.size() == 1)
			{
				server->sendResp(ERR_NOTEXTTOSEND(nick), fd);  // 412
				return;
			}
			server->sendResp(MSG_PRIVMSG_TO_NICK(cl->getNick(), str[1], splitedStrVect[1]), server->getFdClientByNick(str[1]));
		}
	}
}
