
#include "Topic.hpp"
#include "replies.hpp"

Topic::~Topic( void ) {};

/* ------------------- PUBLIC MEMBER FUNCTIONS ------------------*/

void Topic::execute( Server* server, std::string &msg , int fd)
{
	std::vector<std::string>	str;
	std::vector<std::string>	splitedStrVect;
	std::string					chName;
	std::string					topic = "";
	Client						*cl;
	Channel						*ch;


	cl = server->getClient(fd);

//	if (isAuthenticated(server->getClient(fd), server, fd))
//	{
		std::cout << "    ----" << std::endl;
		std::cout << "TOPIC  => TODO : several cases " << msg << std::endl;
		std::cout << "TOPIC  => TODO : Check if client is auth to continue " << msg << std::endl;
		deleteRN(msg);
		splitedStrVect = splitByDoublePoint(msg);
		str = split_msgAPM(splitedStrVect[0]);
		if (str.size() == 1)
		{
			server->sendResp(ERR_NEEDMOREPARAMS(cl->getNick(), "TOPIC"), fd);  // 461  
			return;
		}
		else if (str.size() > 2)
		{
			std::cout << "TODO : a lot of params =" << splitedStrVect[0] << std::endl;
			return;
		}
		std::cout << "TODO : str[1]=" << str[1] << std::endl;
		/*
		 * si  No empieza con # o & error -> ERR_NOSUCHCHANNEL(nickname, channelname) //403
		 *
		 * Mirar el nombre a partir del segundo char (evitar el primer # ó &)
		 * Si canal no esta en la lista de canales -> ERR_NOSUCHCHANNEL nickname, channelname) //403
		 * Si el cliente no está en este canal -> ERR_NOTONCHANNEL(nickname, channelname) //442
		 * Si el topic is protected -> ERR_CHANOPRIVSNEEDED(nickname, channelname) //482
		 *
		 */
		for (size_t i=0; i < str.size(); ++i)
			std::cout << "- str[" << i << "]=" << str[i] << std::endl;
/*
		chName = str[1];
		if ((chName[0] != '#' || chName[0] != '&') && chName.size() == 1 )
		{
			server->sendResp(ERR_NOSUCHCHANNEL(cl->getNick(), chName), fd);
			return;
		}
		chName = chName.substr(1);
		if (!server->isInChannels(chName))
		{
			server->sendResp(ERR_NOSUCHCHANNEL(cl->getNick(), chName), fd);
			return;
		}
*/
		if (str[1].size() >1)
			chName = str[1].substr(1);
		if ( ((str[1][0] != '#' || str[1][0] != '&') && str[1].size() == 1) \
			   	|| !server->isInChannels(chName)) 
		{
			server->sendResp(ERR_NOSUCHCHANNEL(cl->getNick(), chName), fd);
			return;
		}

		ch = server->getChannelByChannelName(chName);
		ch->setTopicRestricted();  //  For test 
		if (!ch->isOpe(cl->getNick()) && !ch->isMem(cl->getNick()))
		{
			server->sendResp(ERR_NOTONCHANNEL(cl->getNick(), chName), fd);
			return;
		}
		std::cout << "Channel name = " << ch->getChannelName() << std::endl;
		if (splitedStrVect.size() == 2)
		{
			if (ch->isTopicRestricted() && !ch->isOpe(cl->getNick()))
			{
				std::cout << "TODO : rigth evaluation for topicResticted" << std::endl;
				server->sendResp(ERR_CHANOPRIVSNEEDED(cl->getNick(), chName), fd);
				return;
			}
			topic = splitedStrVect[1];
			if (topic.empty())
			{
				ch->setTopic("");
				std::cout << "----- Clear Topic" << std::endl;
			}
			else
				ch->setTopic(topic);
			//No se implementa RPL_TOPICWHOTIME (en https://modern.ircdocs.horse/#topic-message indica  SHOULD y en https://datatracker.ietf.org/doc/html/rfc2812 no lo comentan.
			server->sendResp(RPL_TOPIC(cl->getNick(), chName, topic),fd);
			// See : https://datatracker.ietf.org/doc/html/rfc2812#section-3.2.4 
			server->sendBroadAll(MSG_TOPIC_BROAD_ALL(cl->getNick(), chName, topic));
		}
		else
		{
			std::cout << "TODO : Send topic=" << topic << std::endl;
			topic = ch->getTopic();
			if (topic.empty())
				server->sendResp(RPL_NOTOPIC(cl->getNick(), chName),fd);
			else
			{
			//No se implementa RPL_TOPICWHOTIME (en https://modern.ircdocs.horse/#topic-message indica  SHOULD y en https://datatracker.ietf.org/doc/html/rfc2812 no lo comentan.
				server->sendResp(RPL_TOPIC(cl->getNick(), chName, topic),fd);
			}
		}
		std::cout << "    ----" << std::endl;
//	}
}
