/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Ping.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apardo-m <apardo-m@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 11:43:04 by apardo-m          #+#    #+#             */
/*   Updated: 2025/01/18 14:34:25 by apardo-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/commands/Ping.hpp"

Ping::~Ping( void ) {};

/* ------------------- PUBLIC MEMBER FUNCTIONS ------------------*/

void Ping::execute( void )
{
	std::cout << "PING => TODO" << std::endl;
}

void Ping::execute( std::string token )
{
	std::cout << "PING responde en la siguietne linea con:" << std::endl;
	std::cout << "PONG 127.0.0.1 " << token << std::endl;
}
