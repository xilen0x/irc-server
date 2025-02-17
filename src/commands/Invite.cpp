
#include "Invite.hpp"
#include "irc.hpp"

Invite::~Invite( void ) {};

/* ------------------- PUBLIC MEMBER FUNCTIONS ------------------*/

void Invite::execute( Server* server, std::string &msg , int fd)
{
	if (isAuthenticated(server->getClient(fd), server, fd))
	{
		/*
		std::cout << "    ----" << std::endl;
		std::cout << "INVITE  => TODO wit message " << msg << std::endl;
		std::cout << "    ----" << std::endl;
		*/
		msg = trimLeft(msg);
		std::vector<std::string>vec = split_msg(msg);
		Client *cl = server->getClient(fd);
		std::string nick = cl->getNick();
		// wrong parameters 461
		if (vec.size() < 3)
		{
			std::string chaErrMsg = formatIRCMessage(ERR_NEEDMOREPARAMS(nick, uppercase(vec[0])));
			server->sendResp(chaErrMsg, fd);
			return ;
		}
		std::string channelName = vec[2].substr(1);
		//if the input channelname doesn't exist 403
		if ((vec[2][0] != '#' && vec[2][0] != '&') || !server->getChannelByChanName(channelName))
		{
			std::string chaErrMsg = formatIRCMessage(ERR_CHANNELNOTFOUND(nick, channelName));
			server->sendResp(chaErrMsg, fd);
			return ;
		}
		// if the inviting client doesn't in this channel 442
		if (!server->getChannelByChanName(channelName)->getCliInChannel(nick))
		{
			std::string chaErrMsg = formatIRCMessage(ERR_NOTONCHANNEL(nick, channelName));
			server->sendResp(chaErrMsg, fd);
			return ;
		}
		//if the nickname of invited client doesn't exist 401
		if (!server->getClientByNick(vec[1]))
		{
			std::string chaErrMsg = formatIRCMessage(ERR_NOSUCHNICK(vec[1]));
			server->sendResp(chaErrMsg, fd);
			return ;
		}
		//if the invited client is already in this channel 443
		if (server->getChannelByChanName(channelName)->getCliInChannel(vec[1]))
		{
			std::string chaErrMsg = formatIRCMessage(ERR_USERONCHANNEL(vec[1], channelName));
			server->sendResp(chaErrMsg, fd);
			return ;
		}
		//if the channel is invite-only mode and invitor isn't operator 482
		if (server->getChannelByChanName(channelName)->isInviteChannel() && \
									!server->getChannelByChanName(channelName)->isOpe(nick))
		{
			std::string chaErrMsg = formatIRCMessage(ERR_CHANOPRIVSNEEDED(vec[1], channelName));
			server->sendResp(chaErrMsg, fd);
			return ;
		}
		//if client number exceeds the limit of the channel 471
		if (server->getChannelByChanName(channelName)->getUserLimitNumber() && \
					server->getChannelByChanName(channelName)->getClientSum() \
					>= server->getChannelByChanName(channelName)->getUserLimitNumber())
		{
			std::string chaErrMsg = formatIRCMessage(ERR_CHANNELISFULL(vec[1], channelName));
			server->sendResp(chaErrMsg, fd);
			return ;
		}
		// Add new nick into the channel inviting-list 341
		server->getClientByNick(vec[1])->addInviteChannel(channelName);
		server->getChannelByChanName(channelName)->addInv(server->getClientByNick(vec[1]));
		std::string chaInvMsg = formatIRCMessage(RPL_INVITING(nick, channelName, vec[1]));
		server->sendResp(chaInvMsg, fd);
		std::string chaInvitedMsg = formatIRCMessage(MSG_INVITED(nick, server->getClientByFD(fd)->getUserName(), vec[1], channelName));
		server->sendResp(chaInvitedMsg, server->getClientByNick(vec[1])->getFdClient());

		printChannelsInfo(server); // linnnnnnnnn for test
	}
}
