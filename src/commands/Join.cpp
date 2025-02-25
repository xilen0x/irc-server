
#include <sstream>

#include "Join.hpp"
#include <sstream>

#define MY_CHANNEL_NAME "MyChannel"
#define BASE_NICK "nick_"
#define BASE_USER_NAME "userName_"

Join::~Join( void ) {};

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

static bool isInvited(Server* server, Client *cl, std::string channelName, int f)
{
	std::string nick = cl->getNick();
	if (cl->checkInviteChannel(channelName))
	{
		if (f == 1)
		{
			cl->deleteInviteChannel(channelName);
			server->getChannelByChannelName(channelName)->deleteInv(nick);
		}			
		return true;
	}
	return false;
}

/*
// 250207 revisar por que no queda persistente
static void	processJoin(Server* server, std::vector<std::pair<std::string, std::string> >parVec, int ipar, int jchan, int fd)
{
//	std::vector<Channel> channels = server->getChannels();
	Channel *ch = server->getChannelsByNumPosInVector(jchan);
	Client *cl = server->getClient(fd);
	std::string nick = cl->getNick();
	if (ch->getCliInChannel(nick)) // the client has already been in this channel
		return ;
	if (sumChannels(server, nick) >= 10) // the client cannot join more than 10 channels
	{
		std::string chaErrMsg = formatIRCMessage(ERR_TOOMANYCHANNELS(nick));
		server->sendResp(chaErrMsg, fd);
		return ;
	}
	// if the password of channel input is incorrect
	if (!ch->getChannelKey().empty() && ch->getChannelKey() != parVec[ipar].second)
	{
		if (!isInvited(cl, parVec[ipar].first, 0))
		{
			std::string chaErrMsg = formatIRCMessage(ERR_BADCHANNELKEY(nick, ch->getChannelName()));
			server->sendResp(chaErrMsg, fd);
			return ;
		}
	}
	//if the channel is in only-invited mode
	if (ch->isInviteChannel())
	{
		if (!isInvited(cl, parVec[ipar].first, 1))
		{
			std::string chaErrMsg = formatIRCMessage(ERR_INVITEONLYCHAN(nick, ch->getChannelName()));
			server->sendResp(chaErrMsg, fd);
			return ;
		}
	}
	if (ch->getUserLimitNumber() && ch->getClientSum() >= ch->getUserLimitNumber())
	{
		std::string chaErrMsg = formatIRCMessage(ERR_CHANNELISFULL(nick, ch->getChannelName()));
		server->sendResp(chaErrMsg, fd);
		return ;
	}
	ch->addMem(cl);
	if (ch->getTopic().empty())
	{
		std::cout << "processJoin!" << std::endl;///////////////////////
		std::string replyMsg1 = formatIRCMessage(RPL_JOINMSG(cl->getNick() + "!" + cl->getUserName(), cl->getIpClient(), ch->getChannelName()));
		std::string replyMsg2 = formatIRCMessage(RPL_NAMREPLY(nick, ch->getChannelName(), ch->getClientsList()));
		std::string replyMsg3 = formatIRCMessage(RPL_ENDOFNAMES(nick, ch->getChannelName()));
		std::string replyMsg = replyMsg1 + replyMsg2 + replyMsg3;
		server->sendResp(replyMsg, fd);
	}
	else
	{
		std::string replyMsg1 = formatIRCMessage(RPL_JOINMSG(cl->getNick() + "!" + cl->getUserName(), cl->getIpClient(), ch->getChannelName()));
		std::string replyMsg2 = formatIRCMessage(RPL_TOPICIS(cl->getNick(), ch->getChannelName(), ch->getTopic()));
		std::string replyMsg3 = formatIRCMessage(RPL_NAMREPLY(nick, ch->getChannelName(), ch->getClientsList()));
		std::string replyMsg4 = formatIRCMessage(RPL_ENDOFNAMES(nick, ch->getChannelName()));
		std::string replyMsg = replyMsg1 + replyMsg2 + replyMsg3 + replyMsg4;
		server->sendResp(replyMsg, fd);
	}
}
*/

// 250210 Done by apardo-m
static void	processJoin(Server* server, std::vector<std::pair<std::string, std::string> >parVec, int ipar, int jchan, int fd)
{
	Channel	*ch = server->getChannelsByNumPosInVector(jchan);
	Client *cl = server->getClient(fd);
	std::string nick = cl->getNick();
	std::cout << "processJoining... nick= " << nick << std::endl;///////////////////
	if (ch->getCliExceptInv(nick)) // the client has already been in the _memClient(_operators) list of this channel
		{
			server->sendResp(ERR_USERONCHANNEL(nick, ch->getChannelName()), fd);///testing!!!!!!
			return ;
		}
	if (sumChannels(server, nick) >= 10) // the client cannot join more than 10 channels
	{
		std::string chaErrMsg = formatIRCMessage(ERR_TOOMANYCHANNELS(nick));
		server->sendResp(chaErrMsg, fd);
		return ;
	}
	// if the password of channel input is incorrect
	if (!ch->getChannelKey().empty() && ch->getChannelKey() != parVec[ipar].second)//////////////////////???
	{
		if (!isInvited(server, cl, parVec[ipar].first, 0))
		{
			std::string chaErrMsg = formatIRCMessage(ERR_BADCHANNELKEY(nick, ch->getChannelName()));
			server->sendResp(chaErrMsg, fd);
			return ;
		}
	}
	std::cout << "check isInviteChannel " << std::endl;///////////////////
	//if the channel is in only-invited mode
	if (ch->isInviteChannel())
	{
		if (!isInvited(server, cl, parVec[ipar].first, 1))
		{
			std::string chaErrMsg = formatIRCMessage(ERR_INVITEONLYCHAN(nick, ch->getChannelName()));
				server->sendResp(chaErrMsg, fd);
			return ;
		}
	}
	if (ch->getUserLimitNumber() && ch->getClientSum() >= ch->getUserLimitNumber())
	{
		std::string chaErrMsg = formatIRCMessage(ERR_CHANNELISFULL(nick, ch->getChannelName()));
		server->sendResp(chaErrMsg, fd);
		return ;
	}
	ch->addMem(cl);

	if (ch->getTopic().empty())
	{
		std::cout << "processJoin!" << std::endl;///////////////////////
		std::string replyMsg1 = formatIRCMessage(RPL_JOINMSG(cl->getNick() + "!" + cl->getUserName(), cl->getIpClient(), ch->getChannelName()));
		std::cout << "LLega 1!" << std::endl;///////////////////////
		std::string replyMsg2 = formatIRCMessage(RPL_NAMREPLY(nick, ch->getChannelName(), ch->getClientsList()));
		std::cout << "LLega 2!"  << std::endl;///////////////////////
		std::string replyMsg3 = formatIRCMessage(RPL_ENDOFNAMES(nick, ch->getChannelName()));
		std::string replyMsg = replyMsg1 + replyMsg2 + replyMsg3;
		server->sendResp(replyMsg, fd);
	}
	else
	{
		std::string replyMsg1 = formatIRCMessage(RPL_JOINMSG(cl->getNick() + "!" + cl->getUserName(), cl->getIpClient(), ch->getChannelName()));
		std::string replyMsg2 = formatIRCMessage(RPL_TOPIC(cl->getNick(), ch->getChannelName(), ch->getTopic()));
		std::string replyMsg3 = formatIRCMessage(RPL_NAMREPLY(nick, ch->getChannelName(), ch->getClientsList()));
		std::string replyMsg4 = formatIRCMessage(RPL_ENDOFNAMES(nick, ch->getChannelName()));
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
//	server->getChannels().push_back(newChan);
	server->addChannel(newChan);
	std::cout << "handleNonChannel!" << std::endl;///////////////////////////
	std::string replyMsg1 = formatIRCMessage(RPL_JOINMSG(cl->getNick() + "!" + cl->getUserName(), cl->getIpClient(), newChan.getChannelName()));
	std::string replyMsg2 = formatIRCMessage(RPL_NAMREPLY(nick, newChan.getChannelName(), newChan.getClientsList()));
	std::string replyMsg3 = formatIRCMessage(RPL_ENDOFNAMES(nick, newChan.getChannelName()));
	std::string replyMsg = replyMsg1 + replyMsg2 + replyMsg3;
	server->sendResp(replyMsg, fd);
}

bool Join::parseJoin(Server* server, std::vector<std::pair<std::string, std::string> >& parVec, std::string &msg, int fd)
{
	std::vector<std::string> vecStr;
	std::string channelName, passWor, buff;
	std::istringstream ss(msg);
	while (ss >> msg)
		vecStr.push_back(msg);
	if (vecStr.size() < 2)
	{
		std::string joinMsg = formatIRCMessage(ERR_NEEDMOREPARAMS(server->getClient(fd)->getNick(), vecStr[0]));
		server->sendResp(joinMsg, fd);
		parVec.clear();
		return false;
	}
	else if (vecStr.size() > 3 || (vecStr.size() == 2 && !vecStr[1].empty() && vecStr[1].size() == 1) ||
				(vecStr.size() == 3 && !vecStr[1].empty() && !vecStr[2].empty() && vecStr[1].size() == 1))
	{
//		std::string vecStr[1] = trimRight(vecStr[1]);
		std::string joinMsg = formatIRCMessage(FAIL_BADPARAMSFORMAT(msg));
		server->sendResp(joinMsg, fd);
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
	size_t numChComma = 0;// count the number of commas in channelName
	size_t numPaComma = 0;// count the number of commas in passWor
	for (size_t i = 0; i < channelName.size(); i++)
	{
		if (channelName[i] == ',')
		{
			parVec.push_back(std::make_pair(buff, ""));
			buff.clear();
			numChComma++;
		}
		else
			buff += channelName[i];
	}
	for (size_t i = 0; i < passWor.size(); i++)
	{
		if (passWor[i] == ',')
			numPaComma++;
	}
	if (numChComma != numPaComma)
	{
		std::string joinMsg = formatIRCMessage(FAIL_BADPARAMSFORMAT(msg));
		server->sendResp(joinMsg, fd);
		parVec.clear();
		return false;
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
			std::string chaErrMsg = formatIRCMessage(ERR_NOSUCHCHANNEL(server->getClient(fd)->getNick(), parVec[i].first));
			server->sendResp(chaErrMsg, fd);
			parVec.erase(parVec.begin() + i--);
			return false;
		}
		else
			parVec[i].first.erase(parVec[i].first.begin());
	}
	return true;
}

void Join::execute( Server* server, std::string &msg , int fd)
{
	if (isAuthenticated(server->getClient(fd), server, fd))
	{
		std::cout << "JOIN processing..." << std::endl;
		std::vector<std::pair<std::string, std::string> > parVec;
		msg = trimLeft(msg);
		std::string cmd = msg.substr(0, 4);

		if (!parseJoin(server, parVec, msg, fd))
		{
//			std::string joinMsg = formatIRCMessage(ERR_NEEDMOREPARAMS(server->getClient(fd)->getNick(), std::string(cmd)));
//			server->sendResp(joinMsg, fd);
			return ;
		}

		if (parVec.size() > 1)
		{
			std::string joinMsg = formatIRCMessage(RPL_INFO(server->getClient(fd)->getNick()));
			server->sendResp(joinMsg, fd);	
			return ;
		}
		bool f = false;
		for (size_t j = 0; j < server->getChannels().size(); j++)
		{
			if (server->getChannels()[j].getChannelName() == parVec[0].first)
			{
				processJoin(server, parVec, 0, j, fd);
				f = true;
				break ;
			}
		}
		if (!f)
			handleNonChannel(server, parVec, 0, fd);
/*
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
*/
	}

	printChannelsInfo(server); // apardo-m for test
}
