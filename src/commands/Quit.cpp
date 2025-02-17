
#include "Quit.hpp"

/* ------------------- PRIVATE FUNCTIONS ------------------*/
/*
void Quit::_selectMemberAsOperator( Server* server, Channel* actualChannel)
{
	if (actualChannel->sizeOpe() == 0)
	{
		if ( actualChannel->sizeMem() != 0 )
		{
			std::cout << " Set a member as operator" << std::endl;
			std::string	nick;
			Client	*cl = actualChannel->getFirstMem();

			actualChannel->addOpe(cl);
			nick = cl->getNick();
			actualChannel->deleteMem(nick);
			actualChannel->printChannelVars();
			server->sendResp(MSG_QUIT_CHANGE_OPERATOR(nick, actualChannel->getChannelName()), cl->getFdClient());
// Start debug
			cl = actualChannel->getFirstOpe();
			std::cout << "---- Test acces new operator : " << cl->getNick() << std::endl;
			cl->printClientVars();
// end debug
		}
		else
			server->deleteChannel(actualChannel->getChannelName());
	}
}
*/

void Quit::_selectMemberAsOperator( Server* server, Channel* actualChannel)
{
	if (actualChannel->sizeOpe() == 0)
	{
		if ( actualChannel->sizeMem() != 0 )
		{
			std::string	nick;
			Client		*cl;

			std::cout << " Set a member as operator" << std::endl;
			nick = actualChannel->getFirstMemNick();
			cl = server->getClientByNick(nick);
			actualChannel->addOpe(cl);
			actualChannel->deleteMem(nick);
			actualChannel->printChannelVars();
			server->sendResp(MSG_QUIT_CHANGE_OPERATOR(nick, actualChannel->getChannelName()), cl->getFdClient());
// Start debug
			cl = actualChannel->getFirstOpe();
			std::cout << "---- Test acces new operator : " << cl->getNick() << std::endl;
			cl->printClientVars();
// end debug
		}
//		else
//			server->deleteChannel(actualChannel->getChannelName());
	}
}

Quit::~Quit( void ) {};

/* ------------------- PUBLIC MEMBER FUNCTIONS ------------------*/

/*
 * Para cada canal: (Puede que el cliente no este en ningún canal)
 *
 *   si esta en _operators o en _memberClients
 *		envia un broadcast al resto de miembres del canal
 * 		si esta en _operators
 *			borrar el nick del cliente de _operators
 *			si _operators se queda vacio
 *				si _memberClients no esta vacio
 *					tomar el primer nick de _memberClients y pasarlo a _operators
 *					informar al primer nick que ahora será _operator
 *					??? Duda que pasa conel resto de miembros  
 *				else si _memberClients esta vacio
 *		 			Borrar el canal
 *			salir del bucle de recorrer canales	
 *  	else Si esta en _memberClients
 *			borrar el  nick de _memberClients
 *			si _memberClients esta vacio y _operators se queda vacio
 *				Borrar el canal
 *			salir del bucle de recorrer canales
 */	

void Quit::execute( Server* server, std::string &msg , int fd)
{
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

	std::cout << "    ----" << std::endl;
	std::cout << "QUIT  => TODO test bad format" << std::endl;
	deleteRN(msg);
	splitedStrVect = splitByDoublePoint(msg);
	server->sendResp(ERR_QUIT_MSG, fd);

	std::cout << "Delete nick client from any channel. Number of Channels : " << channelsSize << std::endl;
	for( size_t i = 0; i < channelsSize; i++)
	{
		std::cout << " - Start Channel number : " << i << std::endl;
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
				std::cout << " Deleted as operator " << std::endl;
				actualChannel->printChannelVars();
		//		std::cout << " - End Channel number : " << i << std::endl;
			//	break;
			}
			else if (actualChannel->isMem(nick))
			{
				actualChannel->deleteMem(nick);
	//			if (actualChannel->sizeOpe() == 0 && actualChannel->sizeMem() == 0 )
	//				server->deleteChannel(actualChannel->getChannelName());
				std::cout << " Deleted as member" << std::endl;
				actualChannel->printChannelVars();
		//		std::cout << " - End Channel number : " << i << std::endl;
			//	break;
			}
		}
		else
			std::cout << nick << " no found in Channel[" << i << "] = " << actualChannel->getChannelName() << std::endl;
		std::cout << " - End Channel number : " << i << std::endl;
	}
	std::cout << "    ----" << std::endl;
	server->deleteEmptyChannels();	
	//Delete client  from server->clients ,  server->_fdclients and close client's fd
	server->clearClientFromClientsAndChanels(fd, " client has QUIT from server !!!");
}
