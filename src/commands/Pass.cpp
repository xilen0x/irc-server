
#include "Pass.hpp"
#include "Client.hpp"

Pass::~Pass( void ) {};

/* ------------------- PUBLIC MEMBER FUNCTIONS ------------------*/
/*
void Server::sendResp(std::string resp, int fd)
{
	if(send(fd, resp.c_str(), resp.size(), 0) == -1)
		std::cerr << RED << "Response error!" << RES << std::endl;
}
*/

void Pass::execute( Server* server, std::string &msg , int fd)
{
	std::vector<Client>clients = server->getClients();

	// for (size_t i = 0; i < clients.size(); i++) //delete later this for loop
	// {
	// 	std::cout << "Client: " << i << std::endl;
	// 	std::cout << "Has pass: " << ": " << clients[i].getHasPass() << std::endl;
	// }
	// std::cout << "+++++++++++++ msg: " << msg << std::endl;
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
