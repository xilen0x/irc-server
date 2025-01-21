/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*													+:+ +:+		 +:+	 */
/*   By: apardo-m <apardo-m@student.42barcelon	  +#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2025/01/18 16:45:47 by apardo-m		  #+#	#+#			 */
/*   Updated: 2025/01/18 18:36:18 by apardo-m         ###   ########.fr       */
/*																			*/
/* ************************************************************************** */

#ifndef CLIENT_HPP
# define CLIENT_HPP

# include <iostream>

class Client
{
	private:
		int			_fdClient;//init ok
		std::string	_ipClient;//init ok

		std::string	_nick;
		std::string _userName;
		std::string _realName;

		std::string	_bufferInMessage;
		std::string	_bufferOutResponse;

		bool		_hasPass;
		bool		_hasNick;
		bool		_hasUser;
		bool		_hasAuth;	  // Athenticated user with  password, nick, USER
							   
//	tipo lista  _channelsOperator;
//	tipo lista  _channelsList;

	public:
		Client( void );
		Client( int fd, std::string ipClient );
		~Client( void );

		// int			getFdClient( void ) const;
		void		setFdClient( int fd );
		// std::string	getIpClient( void ) const;
		void		setIpClient( std::string ip );

		// std::string	getNick( void ) const;
		// void		setNick( std::string nick );
		// std::string getUserName( void ) const;
		// void		setUserName( std::string user );
		// std::string getRealName( void ) const;
		// void		setRealName( std::string real ) ;

		// std::string	getBufferInMessage( void ) const;
		// void		setBufferInMessage( std::string inMessage ) ;
		// std::string	getBufferOutResponse( void ) const;
		// void 		setBufferOutResponse( std::string outResponse ) ;

		// bool		getHasPass( void ) const;
		// bool		getHasNick( void ) const;
		// bool		gethasUser( void ) const;
		// bool		gethasAuth( void ) const;	
		// void		setHasPass( bool has );
		// void		setHasNick( bool has );
		// void		sethasUser( bool has );
		// void		sethasAuth( bool has );	

 
};

#endif
