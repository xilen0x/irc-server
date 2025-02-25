
#include "Pass.hpp"
#include "Client.hpp"

void Pass::execute(Server* server, std::string &msg, int fd)
{
    Client* client = server->getClient(fd);

    msg = trimLeft(msg);
    msg = msg.substr(4);
    msg = trimLeft(msg);
    msg = trimRight(msg);
    
    if (!msg.empty() && msg[0] == ':')
        msg = msg.substr(1);
    if (msg.empty())
    {
        server->sendResp(ERR_NEEDMOREPARAMS(std::string("*"), "PASS"), fd);  // 461
        return;
    }
    if (client->getHasPass()) {
        server->sendResp(ERR_ALREADYREGISTERED(std::string("*")), fd);  // 462
        return; 
    }
    msg.erase(std::remove(msg.begin(), msg.end(), '\r'), msg.end());
    msg.erase(std::remove(msg.begin(), msg.end(), '\n'), msg.end());
    if (msg == server->getPassword()) {
        std::cout << "[LOG][INFO] Correct password!" << std::endl;//debug
        client->setHasPass();
    } 
    else
        server->sendResp(ERR_PASSWDMISMATCH(std::string("*")), fd);  // 464
}

Pass::~Pass( void ) {};
