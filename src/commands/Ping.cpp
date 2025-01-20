/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Ping.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apardo-m <apardo-m@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 11:43:04 by apardo-m          #+#    #+#             */
/*   Updated: 2025/01/18 14:55:55 by apardo-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Ping.hpp"

Ping::~Ping( void ) {};

/* ------------------- PUBLIC MEMBER FUNCTIONS ------------------*/

void Ping::execute( void )
{
	std::cout << "PING => TODO" << std::endl;
}

void Ping::execute( std::string token )
{
	std::cout << "    ----" << std::endl;
	std::cout << "PING responde en la siguiente linea con:" << std::endl;
	std::cout << PONG(token) << std::endl;
	std::cout << "    ----" << std::endl;
}
