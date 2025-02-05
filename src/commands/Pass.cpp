
#include "Pass.hpp"
#include "Client.hpp"

// void Pass::execute(Server* server, std::string &msg, int fd)
// {
//     Client* client = server->getClient(fd);
//     // std::cout << "Client FD: " << fd << " | Has pass (before set): " << client->getHasPass() << std::endl;//debug
// 	msg = trimLeft(msg);
// 	msg = msg.substr(4);
// 	msg = trimLeft(msg);
// 	if (!msg.empty() && msg[0] == ':')
// 		msg = msg.substr(1);
// 	if (msg.empty())
// 	{
//         server->sendResp(ERR_NEEDMOREPARAMS(std::string("*"), "PASS"), fd);  // 461
//         return;
//     }
//     // Si el cliente ya pasó la verificación de contraseña, enviar error 462
//     if (client->getHasPass()) {
//         server->sendResp(ERR_ALREADYREGISTERED(std::string("*")), fd);  // 462
//         return; 
//     }
//     // Obtener la contraseña del mensaje eliminando el "PASS " inicial
//     // std::string password = msg.substr(5);
//     std::string password = msg;
//     // std::cout << "Passwordxxxxxxxxxxxxx: " << password << std::endl;
//     // std::cout << "msg:" << msg << std::endl;
//     // std::cout << "Server password: " << server->getPassword() << std::endl;
//     // Limpiar caracteres CR y LF
//     password.erase(std::remove(password.begin(), password.end(), '\r'), password.end());
//     password.erase(std::remove(password.begin(), password.end(), '\n'), password.end());

//     // Verificar si la contraseña ingresada es correcta
//     if (password == server->getPassword()) {
//         std::cout << YEL << "Correct password!" << RES << std::endl;
//         if (client->getHasNick() && client->getHasUser())
//         {
//             client->setHasPass();
//             server->sendResp(RPL_WELCOME(server->getServerName(), client->getNick()), fd);  // 001
//             server->sendResp(RPL_YOURHOST(server->getServerName()), fd);  // 002
//             server->sendResp(RPL_CREATED(server->getServerName()), fd);  // 003

//         }
//         // std::cout << "Client FD: " << fd << " | Has pass (after set): " << client->getHasPass() << std::endl;//debug
//     } else {
//         server->sendResp(ERR_PASSWDMISMATCH(std::string("*")), fd);  // 464
//     }
// }

void Pass::execute(Server* server, std::string &msg, int fd)
{
    Client* client = server->getClient(fd);

    msg = trimLeft(msg);
    msg = msg.substr(4);
    msg = trimLeft(msg);
    
    if (!msg.empty() && msg[0] == ':')
        msg = msg.substr(1);
    
    if (msg.empty())
    {
        server->sendResp(ERR_NEEDMOREPARAMS(std::string("*"), "PASS"), fd);  // 461
        return;
    }

    if (client->getHasPass()) {
        server->sendResp(ERR_ALREADYREGISTERED(std::string("*")), fd);  // 462
        return; 
    }

    // Limpiar caracteres CR y LF
    msg.erase(std::remove(msg.begin(), msg.end(), '\r'), msg.end());
    msg.erase(std::remove(msg.begin(), msg.end(), '\n'), msg.end());

    if (msg == server->getPassword()) {
        std::cout << YEL << "Correct password!" << RES << std::endl;
        client->setHasPass();

        // if (client->getHasNick() && client->getHasUser()) {
        //     server->sendResp(RPL_WELCOME(server->getServerName(), client->getNick()), fd);  // 001
        //     server->sendResp(RPL_YOURHOST(server->getServerName()), fd);  // 002
        //     server->sendResp(RPL_CREATED(server->getServerName()), fd);  // 003
        // }
    } 
    else {
        server->sendResp(ERR_PASSWDMISMATCH(std::string("*")), fd);  // 464
    }
}



Pass::~Pass( void ) {};
