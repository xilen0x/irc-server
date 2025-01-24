/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Ping.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apardo-m <apardo-m@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 11:35:21 by apardo-m          #+#    #+#             */
/*   Updated: 2025/01/18 14:25:31 by apardo-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PING_HPP
# define PING_HPP

# include <iostream>
# include "ICommand.hpp"

class Ping : public ICommand
{
	public:
		~Ping( void );

		void execute( void ); 		
		void execute( std::string );
};

#endif

