
#include "Quit.hpp"

Quit::~Quit( void ) {};

/* ------------------- PUBLIC MEMBER FUNCTIONS ------------------*/

void Quit::execute( Server* server, std::string &msg , int fd)
{
	std::vector<std::string> splitedStrVect;

	std::string nick;
	std::string user;
//	(void)fd;
//	(void)server;

	Client*	client;

	client = server->getClientByFD(fd);
	nick = client->getNick();
	user = client->getUserName();


	std::cout << "    ----" << std::endl;
	std::cout << "QUIT  => TODO test bad format" << std::endl;
	deleteRN(msg);
	splitedStrVect = splitByDoublePoint(msg);
	server->sendResp(ERR_QUIT_MSG, fd);
// Parte A : Estas 4 lineas se han de cambiar por la parte B
/*
	if (splitedStrVect.size() == 2)
		server->sendBroad(MSG_QUIT_CHANNEL_REASON(nick, user, splitedStrVect[1]), fd);
	else
		server->sendBroad(MSG_QUIT_CHANNEL_NO_REASON(nick, user), fd);
*/
	std::cout << "Delete nick client from any channel" << std::endl;
//Parte B ( esto cambia la parte A)			
// Para cada canal: (Puede que el cliente no este en ningún canal)
//
//   si esta en _operators o en _memberClients
//		envia un broadcast al resto de miembres del canal
// 		si esta en _operators
//			borrar el nick del cliente de _operators
//			si _operators se queda vacio
//				si _memberClients no esta vacio
//					tomar el primer nick de _memberClients y pasarlo a _operators
//					informar al primer nick que ahora será _operator
//					??? Duda que pasa conel resto de miembros  
//				else si _memberClients esta vacio
//		 			Borrar el canal
//			salir del bucle de recorrer canales	
//  	else Si esta en _memberClients
//			borrar el  nick de _memberClients
//			si _memberClients esta vacio y _operators se queda vacio
//				Borrar el canal
//			salir del bucle de recorrer canales	

	size_t channelsSize = server->getChannelsSize();
	Channel *actualChannel;

	std::cout << "Number of Channels : " << channelsSize << std::endl;
	for( size_t i = 0; i < channelsSize; i++)
	{
		actualChannel = server->getChannelsByNumPosInVector(i);
		if (actualChannel->isOperator(nick) || actualChannel->isMember(nick))
		{
			std::cout << nick << " TODO  send chanelBroadcast to " << actualChannel->getChannelName() << std::endl;
			if (splitedStrVect.size() == 2)
				server->sendBroad(MSG_QUIT_CHANNEL_REASON(nick, user, splitedStrVect[1]), fd);
			else
				server->sendBroad(MSG_QUIT_CHANNEL_NO_REASON(nick, user), fd);
			if (actualChannel->isOperator(nick))
			{
				actualChannel->deleteOperator(nick);
				if (actualChannel->sizeOperators() == 0)
				{
					if ( actualChannel->sizeMemberClients() != 0 )
						std::cout << " TODO : Set a member as operator" << std::endl;
					else
						server->deleteChannel(actualChannel->getChannelName());
				}
				break;
			}
			else if (actualChannel->isMember(nick))
			{
				actualChannel->deleteMember(nick);
				if ( actualChannel->sizeMemberClients() == 0 )
					server->deleteChannel(actualChannel->getChannelName());
				break;
			}
		}
		else
			std::cout << nick << "no found in Channel[" << i << "] = " << actualChannel->getChannelName() << std::endl;
	}
	std::cout << "    ----" << std::endl;
	
	//Borrar cliente de server->clients , de server->_fdclients y cerrar el canal de cliente
	std::cout << "Delete client : " << fd << std::endl;
	server->clearClientFromClientsAndChanels(fd, " client has QUIT from server !!!");
}
