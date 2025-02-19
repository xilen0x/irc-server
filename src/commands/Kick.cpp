
#include "Kick.hpp"
#include "Messageprocessing.hpp"
#include "replies.hpp"

Kick::~Kick( void ) {};

//
int kickParsingIsCorrect(std::string &msg, Server* server, int fd)
{
    std::vector<std::string>	str;
    std::vector<std::string>	splitedMsg;
    std::string                 chName;
	std::string					user;
	std::string					kickedNick;
    Client						*cl;

    cl = server->getClient(fd);
    msg = trimLeft(msg);
    msg = msg.substr(4);
    msg = trimLeft(msg);
    
    if (!msg.empty() && msg[0] == ':')
        msg = msg.substr(1);
    if (msg.empty()) {
        server->sendResp(ERR_NEEDMOREPARAMS(cl->getNick(), "KICK sin argumentos"), fd);  // 461 - editar mensaje luego
        return (0);
    }    
    deleteRN(msg);
	splitedMsg = splitByDoublePoint(msg);
	str = split_msg(splitedMsg[0]);
    if (str.size() < 2) {
        server->sendResp(ERR_NEEDMOREPARAMS(cl->getNick(), "KICK con argumentos insuficientes"), fd);  // 461 - editar mensaje luego
        return (0);
    }
    chName = str[0]; // el canal
	if ((chName[0] != '#' && chName[0] != '&') || chName.size() == 1) {
		server->sendResp(ERR_NOSUCHCHANNEL(cl->getNick(), chName), fd);
		return (0);
	}
    chName = chName.substr(1);
    Channel* channel = server->getChannelByChannelName(chName);
	if (channel == NULL) {
		server->sendResp(ERR_NOSUCHCHANNEL(cl->getNick(), chName), fd);
		return (0);
	}
	//----------------------- con sintaxis correcta pero con canal o usuario inexistente -----------------------
	user = str[1]; // el usuario
	kickedNick = cl->getNickByUser(str[1]);
	if (!server->getClientByNick(kickedNick)) {
		server->sendResp(ERR_USERNOTINCHANNEL(cl->getNick(), chName), fd);
		return (0);
	}
	if (!channel->isOpe(cl->getNick()))	{
		server->sendResp(ERR_CHANOPRIVSNEEDED(cl->getNick(), chName), fd);//482 - You're not channel operator
		return (0);
	}
	kickedNick = uppercase(kickedNick);
	channel->deleteMem(kickedNick);
	//message to the kicker(operator)
	server->sendResp(RPL_KICK(server->getClient(fd)->getNick(), chName, user, "Has been kicked"), fd);
	//message to the kicked
	server->sendResp(RPL_KICK(server->getClient(fd)->getNick(), chName, user, "You have been kicked"), server->getFdClientByNick(kickedNick));
	//message to all in the channel
	server->sendBroadAllInChannel(RPL_KICK(server->getClient(fd)->getNick(), chName, user, "Has been kicked"), channel);
    return (1);
}

// ------------------------ KICK command --------------------------------
void Kick::execute(Server* server, std::string &msg, int fd)
{
    if (!isAuthenticated(server->getClient(fd), server, fd)) {
        return;
    }
    
    if (!kickParsingIsCorrect(msg, server, fd)) {
        return;
    }
	printChannelsInfo(server);//debug
	//log to the console
    std::cout << YEL << "User " << server->getClient(fd)->getNick() << " has executed KICK command" << RES << std::endl;
}
