
#include "Nick.hpp"
#include "User.hpp"
#include "irc.hpp"

/* ------------------- PUBLIC MEMBER FUNCTIONS ------------------*/

Nick::Nick( void ) : welcomeMsgNick(false) {};

void Nick::execute( Server* server, std::string &msg , int fd)
{
	User	user;

	msg = trimLeft(msg);
	msg = msg.substr(4);
	msg = trimLeft(msg);
	std::vector<Client> clients = server->getClients();
	Client *cl = server->getClient(fd);
	if (cl->getHasPass())
    {
		if (!msg.empty() && msg[0] == ':')
			msg = msg.substr(1);
		if (msg.empty())
		{
			server->sendResp(ERR_NEEDMOREPARAMS(std::string("*"), "NICK"), fd);
			std::cout << "input nick is empty, new nick is *" << std::endl;//debug
			return ;
		}
		msg.erase(std::remove(msg.begin(), msg.end(), '\r'), msg.end());
    	msg.erase(std::remove(msg.begin(), msg.end(), '\n'), msg.end());
    	msg = trimRight(msg);
		if (checkNickInUse(clients, msg) && cl->getNick() != msg)
		{
			if (cl->getNick().empty())
				cl->setNick("*");
			std::cout << "input nick is in use, different from old one" << std::endl;//debug
			server->sendResp(ERR_NICKINUSE(std::string(msg)), fd);
			return ;
		}
		else if (checkNickInUse(clients, msg) && cl->getNick() == msg)
		{
			std::cout << "[LOG] [WARNING] Nickname is already in use!" << std::endl;//debug
			server->sendResp(ERR_NICKINUSE(std::string(msg)), fd);//433
			return ;
		}
		if (!validateNick(msg))
		{
			std::cout << "input nick is invalid" << std::endl;
			server->sendResp(ERR_ERRONEUSNICKNAME(std::string(msg)), fd);
			return ;
		}
		else
		{
			if (cl && cl->getHasNick() && cl->getHasAuth())
			{
				Channel	*ch;
				std::string preNick = cl->getNick();
				cl->setNick(msg);
				std::cout << "change global nick into: " << cl->getNick() << std::endl;
			 	std::cout << "channels size =" << server->getChannels().size() << ", " << server->getChannelsSize() << std::endl;				
				for (size_t i = 0; i < server->getChannelsSize(); i++)
				{
					ch = server->getChannelsByNumPosInVector(i);
					if ( ch->isOpe(preNick) )
					{
						std::cout << "-- isOpe" << std::endl;
						ch->deleteOpe(preNick);
						ch->addOpe(cl);
					}
					else if ( ch->isMem(preNick) )
					{
						std::cout << "-- isMem" << std::endl;
						ch->deleteMem(preNick);
						ch->addMem(cl);
					}
					else if ( ch->isInv(preNick) )
					{
						std::cout << "-- isInv" << std::endl;
						ch->deleteInv(preNick);
						ch->addInv(cl);
					}
					else
						std::cout << "-- not found (" << preNick << ")" << std::endl;
					ch->printChannelVars();
				}
				if (!preNick.empty() && preNick != msg)
				{
					if (preNick == "*" && !cl->getUserName().empty())
					{
						cl->setHasNick();
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
				std::cout << "[LOG][INFO] Correct nick format!" << std::endl;//debug
				if ( cl->getHasUser() && cl->getHasNick())
				{
					server->sendResp(RPL_WELCOME(server->getServerName(), cl->getNick()), fd);  // 001
					server->sendResp(RPL_YOURHOST(server->getServerName()), fd);  // 002
					server->sendResp(RPL_CREATED(server->getServerName()), fd);  // 003
					cl->setHasAuth();
				}
				return ;
			}
			else if (cl->getHasNick())
			{
				server->sendResp(ERR_NOTREGISTERED(std::string("*")), fd);//451
				std::cout << "[LOG] [WARNING] Client " << cl->getNick() << " has set a nickname but is not authenticated." << std::endl;
			}
			else//debug
				std::cout << "cl is empty or getHasNick() is not empty" << std::endl;//debug
		}
	}
	else
	{
		server->sendResp(ERR_NOTREGISTERED(std::string("*")), fd);//451
	}
}

Nick::~Nick( void ) {};
