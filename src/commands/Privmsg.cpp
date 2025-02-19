
#include "Privmsg.hpp"

Privmsg::~Privmsg( void ) {};

/* ------------------- PUBLIC MEMBER FUNCTIONS ------------------*/


//PRIVMSG  <target>{,<target>} <text to be sent>
//	target can be client or Channel

void Privmsg::execute( Server* server, std::string &msg , int fd)
{
	std::vector<std::string>	str;
	std::vector<std::string>	splitedStrVect;
	Client						*cl;
	std::string					nick;
	std::string					target;

	if (isAuthenticated(server->getClient(fd), server, fd))
	{
		std::cout << "    ----" << std::endl;
		std::cout << "PRIVMSG  => WIP" << std::endl;
		cl = server->getClientByFD(fd);
		nick = cl->getNick();
		deleteRN(msg);
		splitedStrVect = splitByDoublePoint(msg);
		str = split_msg(splitedStrVect[0]);
		if (str.size() == 1)
		{
			server->sendResp(ERR_NEEDMOREPARAMS(cl->getNick(), "TOPIC"), fd);  // 461  
			return;
		}
		else if (str.size() > 2)
		{
			std::cout << "TODO : a lot of elements =" << splitedStrVect[0] << std::endl;
			return;
		}

		if (splitedStrVect.size() == 2)
		{
		}
		else
			server->sendResp(ERR_NOTEXTTOSEND(nick), fd);
		std::cout << "    ----\n" << std::endl;
	}
}
