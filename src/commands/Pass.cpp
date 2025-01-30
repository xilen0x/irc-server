
#include "Pass.hpp"
#include "Client.hpp"

Pass::~Pass( void ) {};

void Pass::execute( Server* server, std::string &msg , int fd)
{
	std::vector<Client>clients = server->getClients();

	std::string password = msg.substr(5); //msg.substr(5) means from the 6th character to the end
	if (msg.size() < 6)
	{
		server->sendResp(ERR_NEEDMOREPARAMS(std::string("*"), password), fd);
		return;
	}
	password.erase(std::remove(password.begin(), password.end(), '\r'), password.end());//move to a function
	password.erase(std::remove(password.begin(), password.end(), '\n'), password.end());//move to a function
	if (password == server->getPassword())
	{
		std::cout << YEL << "Correct password!" << RES << std::endl;
		
		size_t i = 0;
		std::cout << "*********************** Client: " << i << std::endl;//delete later
		std::cout << "Has pass(before set): " << ": " << clients[i].getHasPass() << std::endl;//delete later
		clients[i].setHasPass();
		std::cout << "Has pass(after set): " << ": " << clients[i].getHasPass() << std::endl;//delete later
	}
	else
	{
		server->sendResp(ERR_PASSWDMISMATCH(std::string("*")), fd);
	}
}
