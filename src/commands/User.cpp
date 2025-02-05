
#include "User.hpp"


/* ------------------- PUBLIC MEMBER FUNCTIONS ------------------*/
/*
Note: Tiene que tener nick y pass antes de poder usar este comando
*/

// void User::execute(Server* server, std::string& msg, int fd) 
// {
//     Client* client = server->getClient(fd);

//     std::cout << "Client FD****: " << fd << " | Has pass (before set): " << client->getHasPass() << std::endl;//debug
//     msg = trimLeft(msg);
// 	msg = msg.substr(4);
// 	msg = trimLeft(msg);
// 	if (!msg.empty() && msg[0] == ':')
// 		msg = msg.substr(1);
//     if (msg.empty()) {
//         server->sendResp(ERR_NEEDMOREPARAMS(std::string("*"), "USER"), fd);  // 461
//         return;
//     }
//     // if (!client->getHasPass()) {
//     //     server->sendResp(ERR_ALREADYREGISTERED(std::string("*")), fd);  // 462
//     //     return;
//     // }
//     // if (client->getHasUser()) {
//     //     server->sendResp(ERR_ALREADYREGISTERED(std::string("*")), fd);  // 462
//     //     return;
//     // }
    
//     // std::string username = msg.substr(5); // From the 6th character to the end
//     std::string username = msg;
//     username.erase(std::remove(username.begin(), username.end(), '\r'), username.end());
//     username.erase(std::remove(username.begin(), username.end(), '\n'), username.end());

//     if (client->getHasNick() && client->getHasPass())
//     {
//         client->setHasUser();
// 	    std::cout << YEL << client->getNick() << " has set user: " << username << RES << std::endl;//debug

//         // std::string welcomeMsg = formatIRCMessage(RPL_WELCOME(server->getServerName(), username));
//         // server->sendResp(welcomeMsg, fd); // 001
//         server->sendResp(RPL_WELCOME(server->getServerName(), username), fd); // 001

//         // std::string hostMsg = formatIRCMessage(RPL_YOURHOST(server->getServerName()));
//         // server->sendResp(hostMsg, fd); // 002
//         server->sendResp(RPL_YOURHOST(server->getServerName()), fd); // 002

//         // std::string createdMsg = formatIRCMessage(RPL_CREATED(server->getServerName()));
//         // server->sendResp(createdMsg, fd); // 003
//         server->sendResp(RPL_CREATED(server->getServerName()), fd); // 003
//     }
//     else if (!client->getHasNick())
//     {
//         //461
//         server->sendResp(ERR_NEEDMOREPARAMS(std::string("*"), "NICK"), fd);
//     }
//     else if (!client->getHasPass())
//     {
//         //462
//         server->sendResp(ERR_ALREADYREGISTERED(std::string("*")), fd);
//     }
//     else
//     {
//         //462
//         server->sendResp(ERR_ALREADYREGISTERED(std::string("*")), fd);
//     }
// }

void User::execute(Server* server, std::string& msg, int fd) 
{
    Client* client = server->getClient(fd);

    msg = trimLeft(msg);
    msg = msg.substr(4);
    msg = trimLeft(msg);

    if (!msg.empty() && msg[0] == ':')
        msg = msg.substr(1);

    if (msg.empty()) {
        server->sendResp(ERR_NEEDMOREPARAMS(std::string("*"), "USER"), fd);  // 461
        return;
    }

    if (client->getHasUser()) {
        server->sendResp(ERR_ALREADYREGISTERED(std::string("*")), fd);  // 462
        return;
    }

    // Limpiar caracteres CR y LF
    msg.erase(std::remove(msg.begin(), msg.end(), '\r'), msg.end());
    msg.erase(std::remove(msg.begin(), msg.end(), '\n'), msg.end());

    // std::cout << YEL << " userName(before): " << RES << client->getUserName() << std::endl;//debug
    client->setUserName(msg);
    // std::cout << YEL << " userName(after): " << RES << client->getUserName() << std::endl;//debug
    
    // std::cout << RED << " hasUser(before): " << RES << client->getHasUser() << std::endl;//debug
    client->setHasUser();
    // std::cout << RED << " hasUser(after): " << RES << client->getHasUser() << std::endl;//debug
    
    if (client->getHasNick() && client->getHasPass()) {
        server->sendResp(RPL_WELCOME(server->getServerName(), client->getNick()), fd);  // 001
        server->sendResp(RPL_YOURHOST(server->getServerName()), fd);  // 002
        server->sendResp(RPL_CREATED(server->getServerName()), fd);  // 003
    }
}


User::~User( void ) {};