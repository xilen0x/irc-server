
#include "Nick.hpp"


/* ------------------- PUBLIC MEMBER FUNCTIONS ------------------*/

	// clients[i].setHasNick();//debug
void Nick::execute( Server* server, std::string &msg , int fd)
{
	// (void)fd;
	// (void)server;

	std::vector<Client>clients = server->getClients();
	if (msg.size() < 5)
	{
		server->sendResp(ERR_NEEDMOREPARAMS(std::string("*"), "NICK"), fd);//461
		return;
	}
	// if (clients[0].getHasNick())//si ya tiene nick
	// {
	// 	server->sendResp(ERR_ALREADYREGISTERED(std::string("*")), fd);//462
	// 	return;
	// }
	std::string nickname = msg.substr(5); //msg.substr(5) means from the 6th character to the end
	nickname.erase(std::remove(nickname.begin(), nickname.end(), '\r'), nickname.end());//move to a function
	nickname.erase(std::remove(nickname.begin(), nickname.end(), '\n'), nickname.end());//move to a function
	// std::cout << "Has nick(before set): " << ": " << clients[0].getHasNick() << std::endl;//debug
	clients[0].setHasNick();
	// std::cout << "Has nick(after set): " << ": " << clients[0].getHasNick() << std::endl;//debug

	// std::cout << "Nickname_x: " << nickname << std::endl;//debug
	// std::cout << "clients[0].getNick(): " << clients[0].getNick() << std::endl;//debug
	clients[0].setNick(nickname);
	// std::cout << "clients[0].getNick(): " << clients[0].getNick() << std::endl;//debug
	// std::cout << "clients[0].getHasNick(): " << clients[0].getHasNick() << std::endl;//debug
	// std::cout << "clients[0].getHasUser(): " << clients[0].getHasUser() << std::endl;//debug
	// std::cout << "clients[0].getHasPass(): " << clients[0].getHasPass() << std::endl;//debug
	// std::cout << "clients[0].getHasRealname(): " << clients[0].getHasRealname() << std::endl;//debug
	// std::cout << "clients[0].getHasHost(): " << clients[0].getHasHost() << std::endl;//debug
	// std::cout << "clients[0].getHasServername(): " << clients[0].getHasServername() << std::endl;//debug
	// std::cout << "clients[0].getHasMode(): " << clients[0].getHasMode() << std::endl;//debug
	// std::cout << "clients[0].getHasIp(): " << clients[0].getHasIp() << std::endl;//debug
	// std::cout << "clients[0].getHasRealname(): " << clients[0].getHasRealname() << std::endl;//debug	
	
}

Nick::~Nick( void ) {};