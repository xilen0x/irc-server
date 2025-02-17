
#include "Kick.hpp"
#include "Messageprocessing.hpp"
#include "replies.hpp"

Kick::~Kick( void ) {};

/*
Cuando el usuario NO está en ningún canal
KICK sin parámetros	461	KICK :Not enough parameters - ok
KICK con solo canal	461	KICK :Not enough parameters - ok
KICK con solo usuario	461	KICK :Not enough parameters - ok
KICK con canal inexistente	403	#general :No such channel - ok

Cuando el usuario YA está en un canal
KICK sin parámetros	461	KICK :Not enough parameters - ok
KICK con solo canal	461	KICK :Not enough parameters - ok
KICK con solo usuario (sin especificar canal)	461	KICK :Not enough parameters - ok
KICK con canal inexistente	403	#general :No such channel - ok
KICK con canal o usuario inexistente	441	JohnDoe #general :They aren't on that channel - ok
KICK con canal y usuario, pero quien lo ejecuta no es operador	482	#general :You're not channel operator
KICK con canal y usuario válido, ejecutado correctamente	No error	Usuario es expulsado y se notifica a todos en el canal

*/
/* Syntax del mensaje KICK: 
   KICK <channel> <user> *( "," <user> ) [<comment>] */

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
    if (msg.empty())
    {
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

    chName = str[0]; // Primer parámetro debe ser el canal
	if ((chName[0] != '#' && chName[0] != '&') || chName.size() == 1)
	{
		server->sendResp(ERR_NOSUCHCHANNEL(cl->getNick(), chName), fd);
		return (0);
	}
// std::cout << "chName before: " << chName << std::endl;//debug &42
    chName = chName.substr(1);
// std::cout << "chName after: " << chName << std::endl;//debug 42
    Channel* channel = server->getChannelByChannelName(chName);
	if (channel == NULL)
	{
		server->sendResp(ERR_NOSUCHCHANNEL(cl->getNick(), chName), fd);
		return (0);
	}
//--------- KICK sintaxis correcta pero con canal o usuario inexistente -----------------------
	user = str[1]; // Segundo parámetro debe ser el usuario
	kickedNick = cl->getNickByUser(str[1]);
	std::cout << "kickedNick: " << kickedNick << std::endl;//debug
	if (!server->getClientByNick(kickedNick))
	{
		server->sendResp(ERR_USERNOTINCHANNEL(cl->getNick(), chName), fd);
		return (0);
	}
//KICK con canal y usuario, pero quien lo ejecuta no es operador (482)	#general :You're not channel operator
	if (!channel->isOpe(cl->getNick()))
	{
		server->sendResp(ERR_CHANOPRIVSNEEDED(cl->getNick(), chName), fd);//482
		return (0);
	}
	//si todo va bien, se procede con el KICK
	kickedNick = uppercase(kickedNick);
	channel->deleteMem(kickedNick);
	server->sendResp(RPL_KICK(server->getClient(fd)->getNick(), chName, user, "Has been kicked"), fd);
    return (1);
}

void Kick::execute(Server* server, std::string &msg, int fd)
{
    if (!isAuthenticated(server->getClient(fd), server, fd)) {
        return;
    }
    
    if (!kickParsingIsCorrect(msg, server, fd)) {
        return;
    }
	printChannelsInfo(server);
    std::cout << YEL << "User " << server->getClient(fd)->getNick() << " has executed KICK command" << RES << std::endl;
	//:source KICK <channel> <user> :<comment>
	// server->sendBroadAllInChannel(msg, server->getChannelByChannelName("general"));//SEGV
}

/*
Numeric Replies:
• ERR_NEEDMOREPARAMS (461)
• ERR_NOSUCHCHANNEL (403)
• ERR_CHANOPRIVSNEEDED (482)//cuando el usuario no es operador
• ERR_USERNOTINCHANNEL (441)//cuando el usuario no está en el canal
• ERR_NOTONCHANNEL (442)
*/