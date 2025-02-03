
#include "Quit.hpp"

Quit::~Quit( void ) {};

/* ------------------- PUBLIC MEMBER FUNCTIONS ------------------*/

void Quit::execute( Server* server, std::string &msg , int fd)
{
	std::vector<std::string> splitedStrVect;

	std::string nick;
	std::string user;
//	(void)fd;
//	(void)server;

	Client*	client;

	client = server->getClientByFD(fd);
	nick = client->getNick();
	user = client->getUserName();

	std::cout << "    ----" << std::endl;
	std::cout << "QUIT  => TODO test bad format" << std::endl;
	deleteRN(msg);
	splitedStrVect = splitByDoublePoint(msg);
	if (splitedStrVect.size() == 2)
		server->sendBroad(MSG_QUIT_CHANNEL_REASON(nick, user, splitedStrVect[1]), fd);
	else
		server->sendBroad(MSG_QUIT_CHANNEL_NO_REASON(nick, user), fd);
	server->sendResp(ERR_QUIT_MSG, fd);
			
	std::cout << "    ----" << std::endl;
	
	//Borrar cliente de server->clients , de server->_fdclients y cerrar el canal de cliente
	std::cout << "Delete client : " << fd << std::endl;
	server->deleteClientFromAnyChannel(fd);
	server->clearClients(fd, "A client has QUIT from server !!!");
}
