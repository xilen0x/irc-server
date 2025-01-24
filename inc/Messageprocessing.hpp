/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Messageprocessing.hpp                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apardo-m <apardo-m@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 12:01:03 by apardo-m          #+#    #+#             */
/*   Updated: 2025/01/18 14:00:02 by apardo-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MESSAGEPROCESSING_HPP
# define MESSAGEPROCESSING_HPP

# include <iostream>
# include <map>
# include "ICommand.hpp"
# include "Ping.hpp"

class Messageprocessing
{
	private:
		std::map<std::string, ICommand *>	_commands;

	public:
		Messageprocessing( void );
		~Messageprocessing( void );

		void	processMessage(std::string message); 
};

#endif
