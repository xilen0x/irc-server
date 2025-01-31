
#include "Pass.hpp"
#include "Client.hpp"

void Pass::execute( Server* server, std::string &msg , int fd)
{
	std::vector<Client>clients = server->getClients();
	if (clients[0].getHasPass())//si ya tiene pass
	{
		server->sendResp(ERR_ALREADYREGISTERED(std::string("*")), fd);//462 //falta testear este msg cuando ya se ha registrado
		return;
	}
	if (msg.size() < 5)
	{
		server->sendResp(ERR_NEEDMOREPARAMS(std::string("*"), "PASS"), fd);//461
		return;
	}
	std::string password = msg.substr(5); //msg.substr(5) means from the 6th character to the end
	password.erase(std::remove(password.begin(), password.end(), '\r'), password.end());//move to a function
	password.erase(std::remove(password.begin(), password.end(), '\n'), password.end());//move to a function
	if (password == server->getPassword())
	{
		std::cout << YEL << "Correct password!" << RES << std::endl;
		
		size_t i = 0;
		// std::cout << "*********************** Client: " << i << std::endl;//debug
		// std::cout << "Has pass(before set): " << ": " << clients[i].getHasPass() << std::endl;//debug
		clients[i].setHasPass();
		// std::cout << "Has pass(after set): " << ": " << clients[i].getHasPass() << std::endl;//debug
	}
	else
	{
		server->sendResp(ERR_PASSWDMISMATCH(std::string("*")), fd);//464
	}
}

Pass::~Pass( void ) {};