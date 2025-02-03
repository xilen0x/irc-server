
#include "User.hpp"


/* ------------------- PUBLIC MEMBER FUNCTIONS ------------------*/
/*
Note: Tiene que tener nick y pass antes de poder usar este comando
*/

// void User::execute( Server* server, std::string &msg , int fd)
// {
// 	std::vector<Client>clients = server->getClients();
// 	if (msg.size() < 5)
// 	{
// 		server->sendResp(ERR_NEEDMOREPARAMS(std::string("*"), "USER"), fd);//461
// 		return;
// 	}
// 	if (clients[0].getHasUser())//si ya tiene user
// 	{
// 		server->sendResp(ERR_ALREADYREGISTERED(std::string("*")), fd);//462
// 		return;
// 	}
// 	size_t i = 0;
// 	std::string username = msg.substr(5); //msg.substr(5) means from the 6th character to the end
// 	username.erase(std::remove(username.begin(), username.end(), '\r'), username.end());//move to a function
// 	username.erase(std::remove(username.begin(), username.end(), '\n'), username.end());//move to a function
// 	clients[i].setHasUser();
// 	std::cout << YEL << clients[i].getNick() << " has set user: " << username << RES << std::endl;
// 	server->sendResp(RPL_WELCOME(server->getServerName(), username), fd);//001
// 	server->sendResp(RPL_YOURHOST(server->getServerName()), fd);//002
// 	server->sendResp(RPL_CREATED(server->getServerName()), fd);//003
// }

void User::execute(Server* server, std::string& msg, int fd) {
    std::vector<Client> clients = server->getClients();

    // Check if the message is too short
    if (msg.size() < 5) {
        std::string errorMsg = formatIRCMessage(ERR_NEEDMOREPARAMS(std::string("*"), "USER"));
        server->sendResp(errorMsg, fd); // 461
        return;
    }

    // Check if the client is already registered
    if (clients[0].getHasUser()) {
        std::string errorMsg = formatIRCMessage(ERR_ALREADYREGISTERED(std::string("*")));
        server->sendResp(errorMsg, fd); // 462
        return;
    }

    // Extract and clean the username
    std::string username = msg.substr(5); // From the 6th character to the end
    username.erase(std::remove(username.begin(), username.end(), '\r'), username.end());
    username.erase(std::remove(username.begin(), username.end(), '\n'), username.end());

    // Set the user flag for the client
    clients[0].setHasUser();
    std::cout << YEL << clients[0].getNick() << " has set user: " << username << RES << std::endl;

    // Send welcome messages with timestamps
    std::string welcomeMsg = formatIRCMessage(RPL_WELCOME(server->getServerName(), username));
    server->sendResp(welcomeMsg, fd); // 001

    std::string hostMsg = formatIRCMessage(RPL_YOURHOST(server->getServerName()));
    server->sendResp(hostMsg, fd); // 002

    std::string createdMsg = formatIRCMessage(RPL_CREATED(server->getServerName()));
    server->sendResp(createdMsg, fd); // 003
}

User::~User( void ) {};