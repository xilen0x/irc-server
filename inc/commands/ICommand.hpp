/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ICommand.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apardo-m <apardo-m@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 16:58:32 by apardo-m          #+#    #+#             */
/*   Updated: 2025/01/18 14:20:25 by apardo-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef ICOMMAND_HPP
# define ICOMMAND_HPP

class ICommand
{
	public:
		virtual	~ICommand( void ) {};

		virtual void execute( void ) = 0;
		virtual void execute( std::string ) = 0;
};

#endif
