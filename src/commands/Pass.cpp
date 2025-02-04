
#include "Pass.hpp"
#include "Client.hpp"

// void Pass::execute( Server* server, std::string &msg , int fd)
// {
// 	std::vector<Client>clients = server->getClients();
// 	//print clients[0].getHasPass()
// 	size_t i = 0;
// 	std::cout << "Has passssss(before set): " << ": " << clients[i].getHasPass() << std::endl;//debug
// 	if (clients[i].getHasPass())//si ya tiene pass
// 	{
// 		server->sendResp(ERR_ALREADYREGISTERED(std::string("*")), fd);//462 //falta testear este msg cuando ya se ha registrado
// 		return;
// 	}
// 	if (msg.size() < 5)
// 	{
// 		server->sendResp(ERR_NEEDMOREPARAMS(std::string("*"), "PASS"), fd);//461
// 		return;
// 	}
// 	std::string password = msg.substr(5); //msg.substr(5) means from the 6th character to the end
// 	password.erase(std::remove(password.begin(), password.end(), '\r'), password.end());//move to a function
// 	password.erase(std::remove(password.begin(), password.end(), '\n'), password.end());//move to a function
// 	if (password == server->getPassword())
// 	{
// 		std::cout << YEL << "Correct password!" << RES << std::endl;
		
// 		// std::cout << "*********************** Client: " << i << std::endl;//debug
// 		// std::cout << "Has pass(before set): " << ": " << clients[i].getHasPass() << std::endl;//debug
// 		clients[i].setHasPass();
// 		// std::cout << "Has pass(after set): " << ": " << clients[i].getHasPass() << std::endl;//debug
// 	}
// 	else
// 	{
// 		server->sendResp(ERR_PASSWDMISMATCH(std::string("*")), fd);//464
// 	}
// }

void Pass::execute(Server* server, std::string &msg, int fd)
{
    // Obtener el cliente correcto
    Client* client = server->getClient(fd);
    if (!client) {
        std::cerr << "Error: Client not found for fd: " << fd << std::endl;
        return;
    }
    // std::cout << "Client FD: " << fd << " | Has pass (before set): " << client->getHasPass() << std::endl;

    // Si el cliente ya pasó la verificación de contraseña, enviar error 462
    if (client->getHasPass()) {
        server->sendResp(ERR_ALREADYREGISTERED(std::string("*")), fd);  // 462
        return;
    }
    // Validar que el mensaje tiene la estructura correcta
    if (msg.size() < 5) {
        server->sendResp(ERR_NEEDMOREPARAMS(std::string("*"), "PASS"), fd);  // 461
        return;
    }
    // Obtener la contraseña del mensaje eliminando el "PASS " inicial
    std::string password = msg.substr(5);

    // Limpiar caracteres CR y LF
    password.erase(std::remove(password.begin(), password.end(), '\r'), password.end());
    password.erase(std::remove(password.begin(), password.end(), '\n'), password.end());

    // Verificar si la contraseña ingresada es correcta
    if (password == server->getPassword()) {
        std::cout << YEL << "Correct password!" << RES << std::endl;
        client->setHasPass();
        // std::cout << "Client FD: " << fd << " | Has pass (after set): " << client->getHasPass() << std::endl;//debug
    } else {
        server->sendResp(ERR_PASSWDMISMATCH(std::string("*")), fd);  // 464
    }
}



Pass::~Pass( void ) {};
