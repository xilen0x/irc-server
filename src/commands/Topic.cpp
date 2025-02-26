
#include "Topic.hpp"
#include "replies.hpp"

Topic::~Topic( void ) {};

/* ------------------- PUBLIC MEMBER FUNCTIONS ------------------*/

/*
 * si  No empieza con # o & error -> ERR_NOSUCHCHANNEL(nickname, channelname) //403
 * Mirar el nombre a partir del segundo char (evitar el primer # ó &)
 * Si canal no esta en la lista de canales -> ERR_NOSUCHCHANNEL nickname, channelname) //403
 * Si el cliente no está en este canal -> ERR_NOTONCHANNEL(nickname, channelname) //442
 * Si el topic is protected -> ERR_CHANOPRIVSNEEDED(nickname, channelname) //482
 *
 */
void Topic::execute( Server* server, std::string &msg , int fd)
{
	std::vector<std::string>	str;
	std::vector<std::string>	splitedStrVect;
	std::string					chName;
	std::string					topic = "";
	Client						*cl;
	Channel						*ch;

	cl = server->getClient(fd);
	if (isAuthenticated(server->getClient(fd), server, fd))
	{
		std::cout << "    ----" << std::endl;
		deleteRN(msg);
		splitedStrVect = splitByDoublePoint(msg);
		str = split_msg(splitedStrVect[0]);
		if (str.size() == 1)
		{
			server->sendResp(ERR_NEEDMOREPARAMS(cl->getNick(), "TOPIC"), fd);  // 461  
			return;
		}
		else if (str.size() > 2)
		{
			server->sendResp(FAIL_LOTPARAMS(msg), fd);
			return;
		}
		//Check str.size  great than 1 char
		if (str[1].size() >1)
			chName = str[1].substr(1);
		if ( ((str[1][0] != '#' || str[1][0] != '&') && str[1].size() == 1) \
			   	|| !server->isInChannels(chName)) 
		{
			server->sendResp(ERR_NOSUCHCHANNEL(cl->getNick(), chName), fd);
			return;
		}
		ch = server->getChannelByChannelName(chName);
		if (!ch->isOpe(cl->getNick()) && !ch->isMem(cl->getNick()))
		{
			server->sendResp(ERR_NOTONCHANNEL(cl->getNick(), chName), fd);
			return;
		}
		if (splitedStrVect.size() == 2)
		{
			if (ch->isTopicRestricted() && !ch->isOpe(cl->getNick()))
			{
				server->sendResp(ERR_CHANOPRIVSNEEDED(cl->getNick(), chName), fd);
				return;
			}
			topic = splitedStrVect[1];
			if (topic.empty())
				ch->setTopic("");
			else
				ch->setTopic(topic);
			server->sendResp(RPL_TOPIC(cl->getNick(), chName, topic),fd);
			server->sendBroadAllInChannel(MSG_TOPIC_BROAD_ALL(cl->getNick(), chName, topic), ch);
		}
		else
		{
			topic = ch->getTopic();
			if (topic.empty())
				server->sendResp(RPL_NOTOPIC(cl->getNick(), chName),fd);
			else
				server->sendResp(RPL_TOPIC(cl->getNick(), chName, topic),fd);
		}
	}
}
// Tras enviar RPL_TOPIC , No se implementa RPL_TOPICWHOTIME (en https://modern.ircdocs.horse/#topic-message indica  SHOULD y en https://datatracker.ietf.org/doc/html/rfc2812 no lo comentan.
// See : https://datatracker.ietf.org/doc/html/rfc2812#section-3.2.4 
