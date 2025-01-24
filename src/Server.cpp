/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apardo-m <apardo-m@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 15:46:31 by apardo-m          #+#    #+#             */
/*   Updated: 2025/01/24 11:25:03 by apardo-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

Server::Server(std::string serverName, std::string password, int port) :_serverName(serverName), _password(password), _port(port), _fdServer(-1)
{
	std::cout << "Server() => Set initial values" << std::endl;
}

Server::~Server( void )
{
	// TODO : Close connections if are open 
	
	std::cout << "------ ~Server() => Clear _fdServer, _clients, _channels" << std::endl;
	this->_fdsClients.clear();
	this->_clients.clear();
	this->_channels.clear();
	std::cout << "------ ~Server() => End Clear _fdServer, _clients, _channels" << std::endl;
}

std::string	Server::getServerName( void ) const { return (this->_serverName); }
std::string	Server::getPassword( void ) const { return (this->_password); }
int 		Server::getPort( void ) const { return (this->_port); };
int			Server::getFdServer( void ) const { return (this->_fdServer); };

void 		Server::addClient( Client newClient ) { this->_clients.push_back(newClient); }
void 		Server::addChannel( Channel newChannel ){ this->_channels.push_back(newChannel); }
