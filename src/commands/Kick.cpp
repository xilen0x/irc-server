
#include "Kick.hpp"
#include "Messageprocessing.hpp"

Kick::~Kick( void ) {};

/*
Casos cuando el usuario NO está en ningún canal
Situación	Código IRC	Mensaje
KICK sin parámetros	461	KICK :Not enough parameters
KICK con solo canal	461	KICK :Not enough parameters
KICK con solo usuario	461	KICK :Not enough parameters
KICK con canal y usuario (pero el usuario que lo ejecuta no está en el canal)	442	#general :You're not on that channel
KICK con canal inexistente	403	#general :No such channel

🔹 Casos cuando el usuario YA está en un canal
Situación	Código IRC	Mensaje
KICK sin parámetros	461	KICK :Not enough parameters
KICK con solo canal	461	KICK :Not enough parameters
KICK con solo usuario (sin especificar canal)	461	KICK :Not enough parameters
KICK con canal inexistente	403	#general :No such channel
KICK con canal y usuario inexistente	441	JohnDoe #general :They aren't on that channel
KICK con canal y usuario, pero quien lo ejecuta no está en el canal	442	#general :You're not on that channel
KICK con canal y usuario, pero quien lo ejecuta no es operador	482	#general :You're not channel operator
KICK con canal y usuario válido, ejecutado correctamente	No error	Usuario es expulsado y se notifica a todos en el canal

🔹 Otros casos especiales
Situación	Código IRC	Mensaje
KICK con varios usuarios separados por , (ejemplo: KICK #general JohnDoe,JaneDoe)	Mensajes separados por usuario	KICK #general JohnDoe :Reason + KICK #general JaneDoe :Reason
KICK a un operador del canal (si el servidor no lo permite)	482	#general :You're not channel operator (o un error personalizado)
KICK a sí mismo (si el servidor no lo permite)	Opcional	Algunas implementaciones pueden bloquearlo con 482
*/
/* Syntax del mensaje KICK: 
   KICK <channel> <user> *( "," <user> ) [<comment>] */
int kickParsingIsCorrect(std::string &msg, Server* server, int fd)
{
    msg = trimLeft(msg);
    msg = msg.substr(4);
    msg = trimLeft(msg);
    
    if (!msg.empty() && msg[0] == ':')
        msg = msg.substr(1);
    if (msg.empty())
    {
        server->sendResp(ERR_NEEDMOREPARAMS(std::string("*"), "KICK sin argumentos"), fd);  // 461 //modificar mensaje luego
        return (0);
    }
    if (msg.size() < 4)
    {
        std::cout << "msg.size: " << msg.size() << std::endl;//debug
        server->sendResp(ERR_NEEDMOREPARAMS(std::string("*"), "KICK con argumentos insuficientes"), fd);  // 461 //modificar mensaje luego
        return (0);
    }
    // 0.1 Verificar si el canal existe
    // obtener channel: 






    
    // if (!channel) {
    //     // server->sendResp(ERR_NOSUCHCHANNEL(std::string("*"), "UNKNOWN_CHANNEL"), fd);  // 403
    //     server->sendResp(ERR_NEEDMOREPARAMS(std::string("*"), "KICK 1"), fd);  // 461
    //     return (0);
    // }



    // if (!server)
    //     return (0);

    // Client* client = server->getClient(fd);
    // if (!client)
    //     return (0);

    // msg = trimLeft(msg);  // Eliminar espacios al inicio
    // msg = msg.substr(4);
    // std::cout << "AFTER msg.substr(4): " << msg << std::endl;
    // msg = trimLeft(msg);
    // std::cout << "AFTER trimLeft: " << msg << std::endl;
    // std::string nick = client->getNick();

    // Verificar si el cliente está autenticado y es operador en el canal
    // if (client->getHasAuth() && channel->isOpe(nick))
    // {
    //     if (msg.empty()) {
    //         server->sendResp(ERR_NEEDMOREPARAMS(std::string("*"), "KICK 2"), fd);  // 461
    //         return (0);
    //     }

    //     if (msg[0] == ':')
    //         msg = msg.substr(1); // Eliminar ":" si está presente

    //     Messageprocessing parameters;
    //     std::vector<std::string> params = parameters.split_msg(msg);

    //     if (params.size() < 2) {
    //         server->sendResp(ERR_NEEDMOREPARAMS(std::string("*"), "KICK 3"), fd);  // 461
    //         return (0);
    //     }
    // }
    // else
    // {
    //     server->sendResp(ERR_NOTREGISTERED(std::string("* 1")), fd);  // 451
    //     return (0);
    // }

    return (1);
}


void Kick::execute(Server* server, std::string &msg, int fd)
{
    if (isAuthenticated(server->getClient(fd), server, fd)) 
    {
        // Verificar si la sintaxis del KICK es correcta
        if (kickParsingIsCorrect(msg, server, fd)) {
            std::cout << "kickParsingIsCorrect INSIDE" << std::endl;//debug
            return;
        }
        //si esta en un canal
        // if (!server->getChannels().size()) {//
        //     server->sendResp(ERR_NOSUCHCHANNEL(std::string("*"), "UNKNOWN_CHANNEL"), fd);  // 403
        //     return;
        // }
        // if (!server || !server->getClient(fd)) {
        //     server->sendResp(ERR_NOTREGISTERED(std::string("* 2")), fd);  // 451
        //     return;
        // }

        // Verificar si el usuario está autenticado
        // std::cout << "after kickParsingIsCorrect INSIDE" << std::endl;//debug
    }
    std::cout << "after kickParsingIsCorrect OUTSIDE" << std::endl;//debug

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