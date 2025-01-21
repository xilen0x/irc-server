/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.tpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apardo-m <apardo-m@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 14:13:45 by apardo-m          #+#    #+#             */
/*   Updated: 2025/01/21 15:03:01 by apardo-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHANNEL_TPP
# define CHANNEL_TPP

# include "Channel.hpp"

template <typename T>
std::vector<std::string>::iterator	Channel::_findStringInVector(const std::string  findString,  T &t )
{
	return (find(t. begin(), t.end(), findString));
} 

template <typename T>
bool	Channel::_isInVector(T &t, std::string nickClient )
{
	std::vector<std::string>::iterator it;
	
	it = this->_findStringInVector(nickClient, t);
	if (it != this->_operators.end())
		return (true);
	return (false);
}

template <typename T>
bool	Channel::_addInVector(T &t, std::string nickClient )
{
	if (this->_isInVector(t, nickClient))
		return (false);
	t.push_back(nickClient);
	return (true);
}

template <typename T>
void	Channel::_deleteInVector(T &t, std::string nickClient )
{
	std::vector<std::string>::iterator	it;
	
	it = this->_findStringInVector(nickClient, t);
	if (it != this->_operators.end())
		this->_operators.erase(it);
}	

#endif
