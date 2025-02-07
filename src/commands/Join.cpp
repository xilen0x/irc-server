
#include <sstream>

#include "Join.hpp"
#include <sstream>

#define MY_CHANNEL_NAME "MyChannel"
#define BASE_NICK "nick_"
#define BASE_USER_NAME "userName_"

// Start  apardo-m functions

static void	printChannelsInfo(Server *server)
{
	Channel *channel;

	std::cout << "========= Start Channels info =======" << std::endl;
	for (size_t i = 0; i < server->getChannels().size(); i++)
	{
		channel = server->getChannelsByNumPosInVector(i);
		channel->printChannelVars();
	}   
	std::cout << "========= End Channels info =======" << std::endl;
}
// End  apardo-m functions

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

static bool isInvited(Client *cl, std::string channelName, int f)
{
	if (cl->checkInviteChannel(channelName))
	{
		if (f == 1)
			cl->deleteInviteChannel(channelName);
		return true;
	}
	return false;
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
	if (!channels[jchan].getChannelKey().empty() && channels[jchan].getChannelKey() != parVec[ipar].second)
	{
		if (!isInvited(cl, parVec[ipar].first, 0))
		{
			std::string chaErrMsg = formatIRCMessage(ERR_BADCHANNELKEY(nick, channels[jchan].getChannelName()));
			server->sendResp(chaErrMsg, fd);
			return ;
		}
	}
	//if the channel is in only-invited mode
	if (channels[jchan].isInviteChannel())
	{
		if (!isInvited(cl, parVec[ipar].first, 1))
		{
			std::string chaErrMsg = formatIRCMessage(ERR_INVITEONLYCHAN(nick, channels[jchan].getChannelName()));
			server->sendResp(chaErrMsg, fd);
			return ;
		}
	}
	if (channels[jchan].getUserLimitNumber() && channels[jchan].getClientSum() >= channels[jchan].getUserLimitNumber())
	{
		std::string chaErrMsg = formatIRCMessage(ERR_CHANNELISFULL(nick, channels[jchan].getChannelName()));
		server->sendResp(chaErrMsg, fd);
		return ;
	}
	channels[jchan].addMem(cl);
	if (channels[jchan].getTopic().empty())
	{
		std::cout << "processJoin!" << std::endl;///////////////////////
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

static void handleNonChannel(Server* server, std::vector<std::pair<std::string, std::string> >parVec, int ipar, int fd)
{
	Client *cl = server->getClient(fd);
	std::string nick = cl->getNick();
	if (sumChannels(server, nick) >= 10)
	{
		std::string chaErrMsg = formatIRCMessage(ERR_TOOMANYCHANNELS(nick));
		server->sendResp(chaErrMsg, fd);
		return ;
	}
	Channel newChan;
	newChan.setChannelName(parVec[ipar].first);
	newChan.addOpe(cl);
	server->getChannels().push_back(newChan);
	std::cout << "handleNonChannel!" << std::endl;///////////////////////////
	std::string replyMsg1 = formatIRCMessage(RPL_JOINMSG(cl->getNick() + "!" + cl->getUserName(), cl->getIpClient(), newChan.getChannelName()));
	std::string replyMsg2 = formatIRCMessage(RPL_NAMREPLY(nick, newChan.getChannelName(), newChan.getClientsList()));
	std::string replyMsg3 = formatIRCMessage(RPL_ENDOFNAMES(nick, newChan.getChannelName()));
	std::string replyMsg = replyMsg1 + replyMsg2 + replyMsg3;
	server->sendResp(replyMsg, fd);
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
	std::cout << "JOIN processing..." << std::endl;
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
			handleNonChannel(server, parVec, i, fd);
	}

	printChannelsInfo(server);
}
