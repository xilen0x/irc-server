
#include "Privmsg.hpp"

Privmsg::~Privmsg( void ) {};

/* ------------------- PUBLIC MEMBER FUNCTIONS ------------------*/


//PRIVMSG  <target>{,<target>} <text to be sent>
//	target can be client or Channel

void Privmsg::execute( Server* server, std::string &msg , int fd)
{
	std::vector<std::string>	splitedStrVect;
	Client						*client;
	std::string					nick;

	std::cout << "    ----" << std::endl;
	client = server->getClientByFD(fd);
	nick = client->getNick();
	deleteRN(msg);
	splitedStrVect = splitByDoublePoint(msg);
	if (splitedStrVect.size() == 2)
	{
		std::cout << "PRIVMSG  => WIP" << std::endl;
	}
	else
		server->sendResp(ERR_NOTEXTTOSEND(nick), fd);
	std::cout << "    ----\n" << std::endl;
}
