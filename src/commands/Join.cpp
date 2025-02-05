
#include "Join.hpp"
#include <sstream>

Join::~Join( void ) {};

/* ------------------- PUBLIC MEMBER FUNCTIONS ------------------*/

static int sumChannels(Server* server, std::string &nick)
{
	int sum = 0;
	for (size_t i = 0; i < server->getChannels().size(); i++)
	{
		if (server->getChannels()[i].getCliInChannel(nick))
			sum++;
	}
	return sum;
}

static void	processJoin(Server* server, std::vector<std::pair<std::string, std::string> >parVec, int ipar, int jchan, int fd)
{
	std::vector<Channel> channels = server->getChannels();
	Client *cl = server->getClient(fd);
	std::string nick = cl->getNick();
	if (channels[jchan].getCliInChannel(nick)) // the client has already been in this channel
		return ;
	if (sumChannels(server, nick) >= 10) // the client cannot join more than 10 channels
	{
		std::string chaErrMsg = formatIRCMessage(ERR_TOOMANYCHANNELS(nick));
		server->sendResp(chaErrMsg, fd);
		return ;
	}
	// if the password of channel input is incorrect
	if (!channels[jchan].getPassword().empty() && channels[jchan].getPassword() != parVec[ipar].second)
	{
		if (!isInvited(server, parVec[ipar].first, 0))
		{
			std::string chaErrMsg = formatIRCMessage(ERR_BADCHANNELKEY(nick, channels[jchan].getChannelName()));
			server->sendResp(chaErrMsg, fd);
			return ;
		}
	}
	//if the channel is in only-invited mode
	if (channels[jchan].getInviteOnly())
	{
		if (!isInvite(server, parVec[ipar].first, 1))
		{
			std::string chaErrMsg = formatIRCMessage(ERR_INVITEONLYCHAN(nick, channels[jchan].getChannelName()));
			server->sendResp(chaErrMsg, fd);
			return ;
		}
	}
	if (channels[jchan].getLimite() && channels[jchan].getClientSum() >= channels[jchan].getLimite())
	{
		std::string chaErrMsg = formatIRCMessage(ERR_CHANNELISFULL(nick, channels[jchan].getChannelName()));
		server->sendResp(chaErrMsg, fd);
		return ;
	}
	channels[jchan].addMem(cl);
	if (channels[jchan].getTopic().empty())
	{
		std::string replyMsg1 = formatIRCMessage(RPL_JOINMSG(cl->getNick() + "!" + cl->getUserName(), cl->getIpClient(), channels[jchan].getChannelName()));
		std::string replyMsg2 = formatIRCMessage(RPL_NAMREPLY(nick, channels[jchan].getChannelName(), channels[jchan].getClientsList()));
		std::string replyMsg3 = formatIRCMessage(RPL_ENDOFNAMES(nick, channels[jchan].getChannelName()));
		std::string replyMsg = replyMsg1 + replyMsg2 + replyMsg3;
		server->sendResp(replyMsg, fd);
	}
	else
	{
		std::string replyMsg1 = formatIRCMessage(RPL_JOINMSG(cl->getNick() + "!" + cl->getUserName(), cl->getIpClient(), channels[jchan].getChannelName()));
		std::string replyMsg2 = formatIRCMessage(RPL_TOPICIS(cl->getNick(), channels[jchan].getChannelName(), channels[jchan].getTopic()));
		std::string replyMsg3 = formatIRCMessage(RPL_NAMREPLY(nick, channels[jchan].getChannelName(), channels[jchan].getClientsList()));
		std::string replyMsg4 = formatIRCMessage(RPL_ENDOFNAMES(nick, channels[jchan].getChannelName()));
		std::string replyMsg = replyMsg1 + replyMsg2 + replyMsg3 + replyMsg4;
		server->sendResp(replyMsg, fd);
	}
}

bool Join::parseJoin(Server* server, std::vector<std::pair<std::string, std::string> >parVec, std::string &msg, int fd)
{
	std::vector<std::string> vecStr;
	std::string channelName, passWor, buff;
	std::istringstream ss(msg);
	while (ss >> msg)
		vecStr.push_back(msg);
	if (vecStr.size() < 2)
	{
		parVec.clear();
		return false;
	}
	vecStr.erase(vecStr.begin());
	channelName = vecStr[0];
	vecStr.erase(vecStr.begin());
	if (!vecStr.empty())
	{
		passWor = vecStr[0];
		vecStr.clear();
	}
	for (size_t i = 0; i < channelName.size(); i++)
	{
		if (channelName[i] == ',')
		{
			parVec.push_back(std::make_pair(buff, ""));
			buff.clear();
		}
		else
			buff += channelName[i];
	}
	parVec.push_back(std::make_pair(buff, ""));
	if (!passWor.empty())
	{
		size_t j = 0;
		buff.clear();
		for (size_t i = 0; i < passWor.size(); i++)
		{
			if (passWor[i] == ',')
			{
				parVec[j].second = buff;
				j++;
				buff.clear();
			}
			else
				buff += passWor[i];
		}
		parVec[j].second = buff;
	}
	for (size_t i = 0; i < parVec.size(); i++)
	{
		if (parVec[i].first.empty())
			parVec.erase(parVec.begin() + i--);
	}
	for (size_t i = 0; i < parVec.size(); i++)
	{
		if (*(parVec[i].first.begin()) != '#' && *(parVec[i].first.begin()) != '&')
		{
			std::string chaErrMsg = formatIRCMessage(ERR_CHANNELNOTFOUND(server->getClient(fd)->getNick(), parVec[i].first));
			server->sendResp(chaErrMsg, fd);
			parVec.erase(parVec.begin() + i--);
		}
		else
			parVec[i].first.erase(parVec[i].first.begin());
	}
	return true;
}

void Join::execute( Server* server, std::string &msg , int fd)
{
	/*
	(void)fd;
	(void)msg;
	// std::cout << "    ----" << std::endl;
	// std::cout << "JOIN  => TODO with message " << msg << std::endl;
	// std::cout << "    ----" << std::endl;

	std::cout << "getChannels: " << server->getChannels().size() << std::endl;
	std::cout << "getClients:" << server->getClients().size() << std::endl;
	for (unsigned long i=0; i < server->getClients().size(); i++)
	{
		std::cout << "getFD[" << i << "]:" << server->getClients()[i].getFdClient() << std::endl;
	}
	*/
	std::vector<std::pair<std::string, std::string> > parVec;
	msg = trimLeft(msg);
	std::string cmd = msg.substr(0, 4);

	if (!parseJoin(server, parVec, msg, fd))
	{
		std::string joinMsg = formatIRCMessage(ERR_NEEDMOREPARAMS(server->getClient(fd)->getNick(), std::string(cmd)));
		server->sendResp(joinMsg, fd);
	}
	for (size_t i = 0; i < parVec.size(); i++)
	{
		bool f = false;
		for (size_t j = 0; j < server->getChannels().size(); j++)
		{
			if (server->getChannels()[j].getChannelName() == parVec[i].first)
			{
				processJoin(server, parVec, i, j, fd);
				f = true;
				break ;
			}
		}
		if (!f)
			handleNonChannel(parVec, i, fd);
	}
}
