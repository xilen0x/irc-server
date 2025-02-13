
#include "Kick.hpp"
#include "Messageprocessing.hpp"

Kick::~Kick( void ) {};

// int	kickParsingIsCorrect(std::string &msg, Server* server, int fd)
// {
//     Client*             client;
//     Messageprocessing   parameters;
//     std::string         nick;
// 	Channel				*channel;

//     msg = trimLeft(msg);
//     msg = msg.substr(4);
//     msg = trimLeft(msg);
// 	client = server->getClient(fd);
// 	nick = client->getNick();
// 	// for (size_t i = 0; i < count; i++)
// 	// {
// 	// 	/* code */
// 	// }
	
// 	channel = server->getChannelsByNumPosInVector(0);
//     if (client->getHasAuth() && channel->isOpe(nick))
//     {
//         if (!msg.empty() && msg[0] == ':')
//             msg = msg.substr(1);

//         if (msg.empty()) {
//             server->sendResp(ERR_NEEDMOREPARAMS(std::string("*"), "KICK2"), fd);  // 461
//             return (0);
//         }
// 		std::vector<std::string> params = parameters.split_msg(msg);
// 		if (params.size() < 2) {
// 			server->sendResp(ERR_NEEDMOREPARAMS(std::string("*"), "KICK3"), fd);  // 461
// 			return (0);
// 		}
// 	}
// 	else
// 	{
// 		server->sendResp(ERR_NOTREGISTERED(std::string("*")), fd);  // 451
// 		return (0);
// 	}
// 	return (1);
// }


// /* Syntax KICK message: 
// 	KICK <channel> <KICK> *( "," <KICK> ) [<comment>]*/
// void Kick::execute( Server* server, std::string &msg , int fd)
// {
// 	if (isAuthenticated(server->getClient(fd), server, fd))
// 	{
// 		//CHECK PARAMETERS(parsing)
// 		if (!kickParsingIsCorrect(msg, server, fd))
// 		{
// 			server->sendResp(ERR_NEEDMOREPARAMS(std::string("*"), "KICK1"), fd);  // 461
// 			return;
// 		}
// std::cout << "KICK after kickParsingIsCorrect" << std::endl;
// 		// 0.1 Check if the channel exists
// 		// 0.2 Check if the KICK exists
// 		// 1. Check if the KICK is in the channel
// 		//IF (PERMISO)// 2. Check if the user(OPERATOR) has the permission to kick
// 			// 3. Kick the user from the channel
// 			// 4. Send the message to the channel
// 			// 5. Send the message to the user

// 		//ELSE(NO PERMISO)
// 			// 6. Send ERR_CHANOPRIVSNEEDED //482
// 	}
// }

int kickParsingIsCorrect(std::string &msg, Server* server, int fd)
{
    if (!server)
        return (0);

    Client* client = server->getClient(fd);
    if (!client)
        return (0);

    msg = trimLeft(msg);  // Eliminar espacios al inicio
    if (msg.size() < 4)
        return (0); // Mensaje demasiado corto para ser un KICK válido

    msg = msg.substr(4); // Eliminar "KICK"
    msg = trimLeft(msg);

    std::string nick = client->getNick();
    Channel* channel = server->getChannelsByNumPosInVector(0);
    
    if (!channel) {
        server->sendResp(ERR_NOSUCHCHANNEL(std::string("*"), "UNKNOWN_CHANNEL"), fd);  // 403
        return (0);
    }

    // Verificar si el cliente está autenticado y es operador en el canal
    if (client->getHasAuth() && channel->isOpe(nick))
    {
        if (msg.empty()) {
            server->sendResp(ERR_NEEDMOREPARAMS(std::string("*"), "KICK"), fd);  // 461
            return (0);
        }

        if (msg[0] == ':')
            msg = msg.substr(1); // Eliminar ":" si está presente

        if (msg.empty()) {
            server->sendResp(ERR_NEEDMOREPARAMS(std::string("*"), "KICK"), fd);  // 461
            return (0);
        }

        Messageprocessing parameters;
        std::vector<std::string> params = parameters.split_msg(msg);

        if (params.size() < 2) {
            server->sendResp(ERR_NEEDMOREPARAMS(std::string("*"), "KICK"), fd);  // 461
            return (0);
        }
    }
    else
    {
        server->sendResp(ERR_NOTREGISTERED(std::string("*")), fd);  // 451
        return (0);
    }

    return (1);
}

/* Syntax del mensaje KICK: 
   KICK <channel> <user> *( "," <user> ) [<comment>] */

void Kick::execute(Server* server, std::string &msg, int fd)
{
    if (!server || !server->getClient(fd)) {
        server->sendResp(ERR_NOTREGISTERED(std::string("*")), fd);  // 451
        return;
    }

    // Verificar si el usuario está autenticado
    if (!isAuthenticated(server->getClient(fd), server, fd)) {
        server->sendResp(ERR_NOTREGISTERED(std::string("*")), fd);  // 451
        return;
    }

    // Verificar si la sintaxis del KICK es correcta
    if (!kickParsingIsCorrect(msg, server, fd)) {
        server->sendResp(ERR_NEEDMOREPARAMS(std::string("*"), "KICK"), fd);  // 461
        return;
    }

    std::cout << "KICK after kickParsingIsCorrect" << std::endl;

    // TODO: Implementar la lógica para manejar el KICK correctamente
    // 0.1 Verificar si el canal existe
    // 0.2 Verificar si el usuario a ser expulsado existe
    // 1. Verificar si el usuario está en el canal
    // 2. Verificar si el usuario que ejecuta el comando tiene permisos de operador
    // 3. Expulsar al usuario del canal
    // 4. Notificar al canal y al usuario expulsado
    // 5. Si el usuario no tiene permisos, enviar ERR_CHANOPRIVSNEEDED (482)
}


/*
Numeric Replies:
• ERR_NEEDMOREPARAMS (461)
• ERR_NOSUCHCHANNEL (403)
• ERR_CHANOPRIVSNEEDED (482)
• ERR_USERNOTINCHANNEL (441)
• ERR_NOTONCHANNEL (442)
*/