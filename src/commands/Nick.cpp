
#include "Nick.hpp"

Nick::~Nick( void ) {};

/* ------------------- PUBLIC MEMBER FUNCTIONS ------------------*/

//Client *Server::getClient(std::vector<Client> clients, int fd)
Client *Server::getClient(int fd)
{
//	for (size_t i = 0; i < clients.size(); i++)
	std::vector<Client>& clientsRef = getClients();
	for (size_t i = 0; i < clientsRef.size(); i++)
	{
//		if (clients[i].getFdClient() == fd)
		if (clientsRef[i].getFdClient() == fd)
			return (&clientsRef[i]);
//			return (&(clients[i]));
	}
	return (NULL);
}

static bool checkNickInUse(std::vector<Client> clients, std::string &s)
{
	for (size_t i = 0; i < clients.size(); i++)
	{
		std::string str = clients[i].getNick();
		if (uppercase(str) == uppercase(s))
			return (true);
	}
	return (false);
}

static bool validateNick(std::string &s)
{
	if (s.size() > 9 || s.size() <= 0)
		return (false);
	const std::string allowedChars = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789-_[]{}\\|^";
	const std::string prohibited = " &#:@!*\t";
	if (!s.empty() && prohibited.find_first_of(s[0]) != std::string::npos)
		return (false);
	for (size_t i = 1; i < s.size(); i++)
	{
		if (allowedChars.find(s[i]) == std::string::npos)
			return (false);
	}
	if (uppercase(s) == "NICKSERV" || uppercase(s) == "CHANSERV")
		return (false);
	return (true);
}

void Nick::execute( Server* server, std::string &msg , int fd)
{
	msg = trimLeft(msg);
	msg = msg.substr(4);
	msg = trimLeft(msg);
	if (!msg.empty() && msg[0] == ':')
		msg = msg.substr(1);
	if (msg.empty())
	{
		server->sendResp(ERR_NEEDMOREPARAMS(std::string("*"), "NICK"), fd);
		std::cout << "input nick is empty, new nick is *" << std::endl;//////////////
		return ;
	}
	std::vector<Client> clients = server->getClients();
//	Client *cl = server->getClient(clients, fd);
	Client *cl = server->getClient(fd);
	if (checkNickInUse(clients, msg) && cl->getNick() != msg)
	{
		if (cl->getNick().empty())
			cl->setNick("*");
		std::cout << "input nick is in use, different from old one" << std::endl;///////////
		server->sendResp(ERR_NICKINUSE(std::string(msg)), fd);
		return ;
	}
	else if (checkNickInUse(clients, msg) && cl->getNick() == msg)
	{
		std::cout << "input nick is in use, same with old one,you don't change yr name" << std::endl;////////////////
		server->sendResp(ERR_NICKINUSE(std::string(msg)), fd);
		return ;
	}
	if (!validateNick(msg))
	{
		std::cout << "input nick is invalid" << std::endl;////////////////
		server->sendResp(ERR_ERRONEUSNICK(std::string(msg)), fd);
		return ;
	}
	else
	{
		if (cl && cl->getHasNick())
		{
			std::string preNick = cl->getNick();
			cl->setNick(msg);
			std::cout << "change global nick into: " << cl->getNick() << std::endl;////////////////
			std::vector<Channel> channels = server->getChannels();
			for (size_t i = 0; i < channels.size(); i++)
			{
				Client *clt = channels[i].getCliInChannel(preNick);
				if (clt)
					clt->setNick(msg);
				std::cout << "change nick in channel into: " << clt->getNick() << std::endl;////////////////
			}
			if (!preNick.empty() && preNick != msg)
			{
				if (preNick == "*" && !cl->getUserName().empty())
				{
					cl->setHasNick();
//					server->sendResp(RPL_CONNECTED(std::string(msg)), fd);
					server->sendResp(RPL_NICKCHANGE(std::string("*"), msg), fd);
				}
				else
					server->sendResp(RPL_NICKCHANGE(std::string(preNick), msg), fd);
			}
		}
		else if (cl && !cl->getHasNick())
		{
			cl->setNick(msg);
			cl->setHasNick();
			std::cout << "1st set a global nick: " << cl->getNick() << std::endl;////////////////
			server->sendResp(RPL_CONNECTED(std::string(msg)), fd);
//			server->sendResp(ERR_NOTREGISTERED(std::string(msg)), fd);
		}
		else
			std::cout << "cl is empty!!!!!!" << std::endl;////////////////
	}
	if (cl && cl->getHasNick() && !cl->getUserName().empty() && !cl->getNick().empty() && cl->getNick() != "*")
	{
		server->sendResp(RPL_CONNECTED(std::string(cl->getNick())), fd);
	}
}
