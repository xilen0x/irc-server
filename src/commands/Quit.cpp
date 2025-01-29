
#include "Quit.hpp"

Quit::~Quit( void ) {};

/* ------------------- PUBLIC MEMBER FUNCTIONS ------------------*/

void Quit::execute( Server* server, std::string &msg , int fd)
{
	std::vector<std::string> splitedStrVect;

	std::string nick = "nickTest";
	std::string user = "userName";
//	(void)fd;
//	(void)server;

	std::cout << "    ----" << std::endl;
	deleteRN(msg);
	splitedStrVect = splitByDoublePoint(msg);
	std::cout << "QUIT  => TODO with token " << splitedStrVect[1] << std::endl;
	server->sendResp(MSG_QUIT_CHANNEL(nick, user, splitedStrVect[1]), fd);
	std::cout << "    ----" << std::endl;
}
