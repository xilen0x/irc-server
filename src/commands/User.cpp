
#include "User.hpp"
#include "Messageprocessing.hpp"
#include "Nick.hpp"
#include "irc.hpp"

/* ------------------- PUBLIC MEMBER FUNCTIONS ------------------*/

User::User( void ) : welcomeMsgUser(false) {};

/*
Sobre los valores 0 y * de USER:
    El valor 0 históricamente representaba el modo de usuario, pero en la mayoría de los servidores modernos no tiene efecto.
    El * era un campo originalmente usado para el hostname, pero tampoco tiene impacto en servidores actuales.
    Tu servidor solo necesita verificar que estos valores existan, pero puede ignorarlos.
*/

void User::execute(Server* server, std::string& msg, int fd) 
{
    Client* client = server->getClient(fd);

    msg = trimLeft(msg);  
    if (msg.substr(0, 4) == "USER" || msg.substr(0, 4) == "user")
        msg.erase(0, 4);
    else {
        server->sendResp(ERR_NEEDMOREPARAMS(std::string("*"), "USER"), fd);  // 461
        return;
    }
    msg = trimLeft(msg);
    if (client->getHasPass())
    {
        if (client->getHasUser()) {
            server->sendResp(ERR_ALREADYREGISTERED(std::string("*")), fd);  // 462
            return;
        }
        std::vector<std::string> params = split_msg(msg);
        if (params.size() < 4) {
            server->sendResp(ERR_NEEDMOREPARAMS(std::string("*"), "USER"), fd);  // 461
            return;
        }
        std::string username = params[0];
        std::string mode = params[1];   // Debe ser "0"
        std::string unused = params[2]; // Debe ser "*"
        std::string realname;
        std::size_t pos = msg.find(" :");
        if (pos != std::string::npos) {
            realname = msg.substr(pos + 2); // se extrae realname
            // std::cout << "Realname------------->: " << realname << std::endl;//debug
        } else {
            server->sendResp(ERR_NEEDMOREPARAMS(std::string("*"), "USER"), fd);  // 461
            return;
        }
        if (mode != "0" || unused != "*") {
                server->sendResp(ERR_USERSYNTAXERROR(std::string("*"), "USER"), fd);
            return;
        }
        realname.erase(std::remove(realname.begin(), realname.end(), '\r'), realname.end());
        realname.erase(std::remove(realname.begin(), realname.end(), '\n'), realname.end());
        client->setUserName(username);
        client->setHasUser();
        std::cout << YEL << "Correct user format!" << RES << std::endl;  //debug
        if (client->getHasNick()) {
            server->sendResp(RPL_WELCOME(server->getServerName(), client->getNick()), fd);  // 001
            server->sendResp(RPL_YOURHOST(server->getServerName()), fd);  // 002
            server->sendResp(RPL_CREATED(server->getServerName()), fd);  // 003
            client->setHasAuth();
        }
    }
    else {
        server->sendResp(ERR_NOTREGISTERED(std::string("*")), fd);  // 451
    }
}

User::~User( void ) {};
