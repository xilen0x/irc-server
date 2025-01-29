
#include "Pass.hpp"
#include "Client.hpp"

Pass::~Pass( void ) {};

/* ------------------- PUBLIC MEMBER FUNCTIONS ------------------*/

void Server::sendResp(std::string resp, int fd)
{
	if(send(fd, resp.c_str(), resp.size(), 0) == -1)
		std::cerr << RED << "Response error!" << RES << std::endl;
}

void Pass::execute( Server* server, std::string &msg , int fd)
{
	const std::vector<Client>& clients = server->getClients();

	for (size_t i = 0; i < clients.size(); i++) {
		std::cout << "Client: " << i << std::endl;
		std::cout << "Has pass: " << ": " << clients[i].getHasPass() << std::endl;
    	// std::cout << "getNick " << ": " << clients[i].getNick() << std::endl;
		// std::cout << "getUserName " << ": " << clients[i].getUserName() << std::endl;
		// std::cout << "getRealName " << ": " << clients[i].getRealName() << std::endl;
		// std::cout << "getIpClient " << ": " << clients[i].getIpClient() << std::endl;
		// std::cout << "getFdClient " << ": " << clients[i].getFdClient() << std::endl;
		// std::cout << "getHasNick " << ": " << clients[i].getHasNick() << std::endl;
		// std::cout << "getHasUser " << ": " << clients[i].getHasUser() << std::endl;
		// std::cout << "getHasAuth " << ": " << clients[i].getHasAuth() << std::endl;
		// std::cout << "getBufferInMessage " << ": " << clients[i].getBufferInMessage() << std::endl;
		// std::cout << "getBufferOutResponse " << ": " << clients[i].getBufferOutResponse() << std::endl;
	}

	// std::vector<Client> clients = server->getClients();
	// if (fd >= 0 && fd < static_cast<int>(clients.size()))
	// {
	// 	std::cout << YEL << "Has pass: " << clients[fd].getHasPass() << RES << std::endl;
	// } else {
	// 	std::cerr << "Error: índice fd fuera de rango en getClients()" << std::endl;
	// }
	
	std::string password = msg.substr(5);
	
	// std::cout << "Password: " << password << std::endl;
	// std::cout << "Server password: " << server->getPassword() << std::endl;
	//remve the /r/n from the password
	password.erase(std::remove(password.begin(), password.end(), '\r'), password.end());
	password.erase(std::remove(password.begin(), password.end(), '\n'), password.end());
	if (password == server->getPassword())
	{
		std::cout << "Correct password!" << std::endl;
			for (size_t i = 0; i < clients.size(); i++) {
		std::cout << "Client: " << i << std::endl;
		std::cout << "Has pass: " << ": " << clients[i].getHasPass() << std::endl;
	}
	}
	else
	{
		server->sendResp(ERR_PASSWDMISMATCH(std::string("*")), fd);
	}
}
