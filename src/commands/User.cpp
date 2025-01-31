
#include "User.hpp"


/* ------------------- PUBLIC MEMBER FUNCTIONS ------------------*/
/*
USER: <username> 0 * <realname>
*/

void User::execute( Server* server, std::string &msg , int fd)
{
	std::vector<Client>clients = server->getClients();
	if (msg.size() < 5)
	{
		server->sendResp(ERR_NEEDMOREPARAMS(std::string("*"), "USER"), fd);//461
		return;
	}
	if (clients[0].getHasUser())//si ya tiene user
	{
		server->sendResp(ERR_ALREADYREGISTERED(std::string("*")), fd);//462
		return;
	}
	//tiene que tener nick y pass antes de user
	size_t i = 0;
	// if (!clients[0].getHasNick() || !clients[0].getHasPass())
	// {
	// 	server->sendResp(ERR_NOTREGISTERED(std::string("*")), fd);//451
	// 	return;
	// }
	std::string username = msg.substr(5); //msg.substr(5) means from the 6th character to the end
	username.erase(std::remove(username.begin(), username.end(), '\r'), username.end());//move to a function
	username.erase(std::remove(username.begin(), username.end(), '\n'), username.end());//move to a function
	// std::cout << "Has user(before set): " << ": " << clients[i].getHasUser() << std::endl;//debug
	clients[i].setHasUser();
	// std::cout << "Has user(after set): " << ": " << clients[i].getHasUser() << std::endl;//debug
	// std::cout << YEL << RPL_CONNECTED(clients[i].getNick()) << RES << std::endl;
	server->sendResp(RPL_CONNECTED(clients[i].getNick()), fd);
}


User::~User( void ) {};