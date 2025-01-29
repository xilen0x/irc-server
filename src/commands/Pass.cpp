
#include "Pass.hpp"

Pass::~Pass( void ) {};

/* ------------------- PUBLIC MEMBER FUNCTIONS ------------------*/

void Server::sendResp(std::string resp, int fd)
{
	if(send(fd, resp.c_str(), resp.size(), 0) == -1)
		std::cerr << "Response failed!" << std::endl;
}

void Pass::execute( Server* server, std::string &msg , int fd)
{
	std::string password = msg.substr(5);
	
	// std::cout << "Password: " << password << std::endl;
	// std::cout << "Server password: " << server->getPassword() << std::endl;
	//remve the /r/n from the password
	password.erase(std::remove(password.begin(), password.end(), '\r'), password.end());
	password.erase(std::remove(password.begin(), password.end(), '\n'), password.end());
	if (password == server->getPassword())
	{
		// server->addClient(Client(fd));
		// std::cout << "Client connected" << std::endl;
		std::cout << "Password correct" << std::endl;
	}
	else
	{
		server->sendResp(ERR_PASSWDMISMATCH(std::string("*")), fd);//ultima linea agregada
		// std::cout << server->getClients()
		close(fd);
	}
}
