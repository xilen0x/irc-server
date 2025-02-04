
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
// Parte A : Estas 4 lineaas se han de cambiar por la parte B
	if (splitedStrVect.size() == 2)
		server->sendBroad(MSG_QUIT_CHANNEL_REASON(nick, user, splitedStrVect[1]), fd);
	else
		server->sendBroad(MSG_QUIT_CHANNEL_NO_REASON(nick, user), fd);
//Parte B ( esto cambia la parte A)			
// Para cada canal: (Puede que el cliente no este en ningún canal)
//
//   si esta en _operators
//		envia un broadcast al resto de miembres del canal
//		borrar el cliente de _operators
//		si _operators se queda vacio
//			si _memberClients no esta vacio
//				tomar el primer nick de _memberClients y pasarlo a _operators
//				informar al nick que ahora será _operator
//			si _memberClients esta vacio
//				Borrar el canal
//		salir del bucle de recorrer canales	
//   else Si esta en _memberClients
//		envia un broadcast al resto de miembres del canal
//		borrar el  nick de _memberClients
//		si _memberClients esta vacio
//			Borrar el canal
//		salir del bucle de recorrer canales	
	std::cout << "    ----" << std::endl;
	
	//Borrar cliente de server->clients , de server->_fdclients y cerrar el canal de cliente
	std::cout << "Delete client : " << fd << std::endl;
	server->deleteClientFromAnyChannel(fd);
	server->clearClients(fd, "A client has QUIT from server !!!");
}
