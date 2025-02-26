
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
        server->sendResp(ERR_NEEDMOREPARAMS(cl->getNick(), "KICK"), fd);
        return (0);
    }    
    deleteRN(msg);
	splitedMsg = splitByDoublePoint(msg);
	str = split_msg(splitedMsg[0]);
    if (str.size() < 2) {
        server->sendResp(ERR_NEEDMOREPARAMS(cl->getNick(), "KICK"), fd);
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
	user = str[1];
	kickedNick = cl->getNickByUser(str[1]);
	kickedNick = uppercase(kickedNick);
	if (!server->getClientByNick(kickedNick)) {
		server->sendResp(ERR_USERNOTINCHANNEL(cl->getNick(), chName), fd);
		return (0);
	}
	if (!channel->isOpe(cl->getNick()))	{
		server->sendResp(ERR_CHANOPRIVSNEEDED(cl->getNick(), chName), fd);//482 - You're not channel operator
		return (0);
	}
	else if (channel->isOpe(kickedNick)) {
		channel->deleteOpe(kickedNick);
	}
	else {
		channel->deleteMem(kickedNick);
	}
	//----------------------- con sintaxis correcta y canal y usuario existente -----------------------
	if (splitedMsg.size() == 1)
	{
		//message to the kicked
		server->sendResp(RPL_KICK(server->getClient(fd)->getNick(), chName, user, "You have been kicked"), server->getFdClientByNick(kickedNick));
		
		// Mensaje para todos en el canal
		server->sendBroadAllInChannel(RPL_KICK(server->getClient(fd)->getNick(), chName, user, "Has been kicked"), channel);
	}
	else
	{
		//message to the kicked with reason of the kick
		server->sendResp(RPL_KICK(server->getClient(fd)->getNick(), chName, user, "You have been kicked :" + splitedMsg[1]), server->getFdClientByNick(kickedNick));
	
		//message to all in the channel with the reason of the kick
		server->sendBroadAllInChannel(RPL_KICK(server->getClient(fd)->getNick(), chName, user, "Has been kicked :" + splitedMsg[1]), channel);
	}
    return (1);
}

// ------------------------ KICK command --------------------------------
//KICK <channel> <nick>
void Kick::execute(Server* server, std::string &msg, int fd)
{
    if (!isAuthenticated(server->getClient(fd), server, fd)) {
        return;
    }
    
    if (!kickParsingIsCorrect(msg, server, fd)) {
        return;
    }
	printChannelsInfo(server);//debug
    std::cout << "[LOG][INFO] User " << server->getClient(fd)->getNick() << " has executed KICK command" << std::endl;//debug
}
