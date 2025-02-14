
#include "Kick.hpp"
#include "Messageprocessing.hpp"
#include "replies.hpp"

Kick::~Kick( void ) {};

/*
Casos cuando el usuario NO está en ningún canal
Situación	Código IRC	Mensaje
KICK sin parámetros	461	KICK :Not enough parameters
KICK con solo canal	461	KICK :Not enough parameters
KICK con solo usuario	461	KICK :Not enough parameters
- KICK con canal y usuario (pero el usuario que lo ejecuta no está en el canal)	442	#general :You're not on that channel
KICK con canal inexistente	403	#general :No such channel

🔹 Casos cuando el usuario YA está en un canal
Situación	Código IRC	Mensaje
KICK sin parámetros	461	KICK :Not enough parameters
KICK con solo canal	461	KICK :Not enough parameters
KICK con solo usuario (sin especificar canal)	461	KICK :Not enough parameters
KICK con canal inexistente	403	#general :No such channel
KICK con canal y usuario inexistente	441	JohnDoe #general :They aren't on that channel
- KICK con canal y usuario, pero quien lo ejecuta no está en el canal	442	#general :You're not on that channel
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
    Client						*cl;

    cl = server->getClient(fd);
    msg = trimLeft(msg);
    msg = msg.substr(4);
    msg = trimLeft(msg);
    
    if (!msg.empty() && msg[0] == ':')
        msg = msg.substr(1);
    if (msg.empty())
    {
        server->sendResp(ERR_NEEDMOREPARAMS(cl->getNick(), "KICK sin argumentos"), fd);  // 461
        return 0;
    }
    
    deleteRN(msg);
	splitedMsg = splitByDoublePoint(msg);
	str = split_msg(splitedMsg[0]);

    if (str.size() < 2) {
        server->sendResp(ERR_NEEDMOREPARAMS(cl->getNick(), "KICK con argumentos insuficientes"), fd);  // 461
        return 0;
    }

    chName = str[0]; // Primer parámetro debe ser el canal
	if ((chName[0] != '#' && chName[0] != '&') || chName.size() == 1)
	{
		server->sendResp(ERR_NOSUCHCHANNEL(cl->getNick(), chName), fd);
		return 0;
	}

    chName = chName.substr(1);
    Channel* channel = server->getChannelByChannelName(chName);
	if (!channel)
	{
		server->sendResp(ERR_NOSUCHCHANNEL(cl->getNick(), chName), fd);
		return 0;
	}
	// if (!channel->isMember(cl->getNick()))
	// {
	// 	server->sendResp(ERR_NOTONCHANNEL(cl->getNick(), chName), fd);
	// 	return 0;
	// }

    return 1;
}

void Kick::execute(Server* server, std::string &msg, int fd)
{
    if (!isAuthenticated(server->getClient(fd), server, fd)) {
        return;
    }
    
    if (!kickParsingIsCorrect(msg, server, fd)) {
        return;
    }

    std::cout << "KICK processing continues..." << std::endl;

    // ...
}

/*
Numeric Replies:
• ERR_NEEDMOREPARAMS (461)
• ERR_NOSUCHCHANNEL (403)
• ERR_CHANOPRIVSNEEDED (482)
• ERR_USERNOTINCHANNEL (441)
• ERR_NOTONCHANNEL (442)
*/