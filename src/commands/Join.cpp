
#include "Join.hpp"
#include <sstream>

Join::~Join( void ) {};

/* ------------------- PUBLIC MEMBER FUNCTIONS ------------------*/

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
}
