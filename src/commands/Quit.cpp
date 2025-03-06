
#include "Quit.hpp"

/* ------------------- PRIVATE FUNCTIONS ------------------*/

void Quit::_selectMemberAsOperator( Server* server, Channel* actualChannel)
{
	if (actualChannel->sizeOpe() == 0)
	{
		if ( actualChannel->sizeMem() != 0 )
		{
			std::string	nick;
			Client		*cl;

			std::cout << "[LOG][INFO] Set a member as operator" << std::endl;//debug
			nick = actualChannel->getFirstMemNick();
			cl = server->getClientByNick(nick);
			if (!cl)
		   	{
				std::cerr << "[LOG][ERROR] No client found with nick: " << nick << std::endl;
				actualChannel->deleteMem(nick);
				return;
			}
			actualChannel->addOpe(cl);
			actualChannel->deleteMem(nick);
			actualChannel->printChannelVars(); //debug
			server->sendResp(MSG_QUIT_CHANGE_OPERATOR(nick, actualChannel->getChannelName()), cl->getFdClient());
			cl = actualChannel->getFirstOpe();
			std::cout << "[LOG][INFO] access new operator : " << cl->getNick() << std::endl;//debug
			cl->printClientVars(); //debug
		}
	}
}

Quit::~Quit( void ) {};

/* ------------------- PUBLIC MEMBER FUNCTIONS ------------------*/


void Quit::execute( Server* server, std::string &msg , int fd)
{
	std::vector<std::string>	str;
	std::vector<std::string>	splitedStrVect;
	std::string					nick;
	std::string					user;
	Client						*client;
	Channel						*actualChannel;
	size_t						channelsSize;

	client = server->getClientByFD(fd);
	nick = client->getNick();
	user = client->getUserName();
	channelsSize = server->getChannelsSize();

	deleteRN(msg);
	splitedStrVect = splitByDoublePoint(msg);
	str = split_msg(splitedStrVect[0]);
	if (str.size() > 2)
	{
		server->sendResp(FAIL_LOTPARAMS(msg), fd);
		return;
	}
	server->sendResp(ERR_QUIT_MSG, fd);

	// std::cout << "Delete nick client from any channel. Number of Channels : " << channelsSize << std::endl;//debug
	for( size_t i = 0; i < channelsSize; i++)
	{
		// std::cout << " - Start Channel number : " << i << std::endl;//debug
		actualChannel = server->getChannelsByNumPosInVector(i);
		if (actualChannel->isOpe(nick) || actualChannel->isMem(nick))
		{
			if (splitedStrVect.size() == 2)
				server->sendBroad(MSG_QUIT_CHANNEL_REASON(nick, user, splitedStrVect[1]), fd);
			else
				server->sendBroad(MSG_QUIT_CHANNEL_NO_REASON(nick, user), fd);
			if (actualChannel->isOpe(nick))
			{
				actualChannel->deleteOpe(nick);
				if (actualChannel->sizeOpe() == 0)
					_selectMemberAsOperator( server, actualChannel);
				std::cout << "[LOG][WARN] Deleted as operator " << std::endl;//debug
				actualChannel->printChannelVars();
			}
			else if (actualChannel->isMem(nick))
			{
				actualChannel->deleteMem(nick);
				std::cout << "[LOG][WARN] Deleted as member" << std::endl;//debug
				actualChannel->printChannelVars();
			}
		}
		else
			std::cout << nick << "[LOG][WARN] no found in Channel[" << i << "] = " << actualChannel->getChannelName() << std::endl;//debug
		// std::cout << " - End Channel number : " << i << std::endl;//debug
	}
	server->deleteEmptyChannels();	
	server->clearClientFromClientsAndChanels(fd, "[LOG][INFO] client has QUIT from server !!!");
}
