
#include "User.hpp"
#include "Messageprocessing.hpp"
#include "Nick.hpp"
#include "irc.hpp"

/* ------------------- PUBLIC MEMBER FUNCTIONS ------------------*/

User::User( void ) : welcomeMsgUser(false) {};

void User::execute(Server* server, std::string& msg, int fd) 
{
    Client*             client = server->getClient(fd);
    Messageprocessing   parameters;
    Nick                nick;

    msg = trimLeft(msg);
    msg = msg.substr(4);
    msg = trimLeft(msg);

    if (client->getHasPass())
    {
        if (!msg.empty() && msg[0] == ':')//
            msg = msg.substr(1);

        if (msg.empty()) {
            server->sendResp(ERR_NEEDMOREPARAMS(std::string("*"), "USER"), fd);  // 461
            return;
        }
        //verificar formato - Parameters: <username> 0 * <realname>
        std::vector<std::string> params = split_msg(msg);
        if (params.size() < 4) {
            server->sendResp(ERR_NEEDMOREPARAMS(std::string("*"), "USER"), fd);  // 461
            return;
        }
        if (client->getHasUser()) {
            server->sendResp(ERR_ALREADYREGISTERED(std::string("*")), fd);  // 462
            return;
        }

        msg.erase(std::remove(msg.begin(), msg.end(), '\r'), msg.end());
        msg.erase(std::remove(msg.begin(), msg.end(), '\n'), msg.end());

        client->setUserName(msg);
        client->setHasUser();
        std::cout << YEL << "Correct user format!" << RES << std::endl;  //added to test
        if (client->getHasNick()) //&& client->getHasUser() && client->getHasPass())
        {
            server->sendResp(RPL_WELCOME(server->getServerName(), client->getNick()), fd);  // 001
            server->sendResp(RPL_YOURHOST(server->getServerName()), fd);  // 002
            server->sendResp(RPL_CREATED(server->getServerName()), fd);  // 003
            client->setHasAuth();
        }
    }
    else
        server->sendResp(ERR_NOTREGISTERED(std::string("*")), fd);  // 451
}

User::~User( void ) {};
