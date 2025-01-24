# [Marc Torres github](https://github.com/MarcTorresss/ft_irc/tree/main)

## Carpetas 

### [inc](https://github.com/MarcTorresss/ft_irc/tree/main/inc)

Clases : 

- Channel.hpp. Ha definido las siguientes variables: 
```c++
std::string				_channelName;
std::string				_channelPassword;
std::string				_channelTopic;
bool					_adminTopic;
bool					_inviteOnly;
unsigned long			_userLimit;

// 3 listas/arrays/vetores para tener 3 tipos de clientes
std::vector< std::string >	_clients;
std::vector< std::string >	_admins;
std::vector< std::string > 	_invites;
```

- Client.hpp. Ha definido las siguientes variables
```c++
std::string			_userName;
std::string			_nickName;
int		 		_fd;
int		 		_status;
std::string			_ipAdd; //-> client ip address
struct sockaddr_in	_clientAdd; // direccion puerto del cliente
std::string			_buffer;
std::string			_inbuffer;
``` 

- Server.hpp

	- *Variables privadas* :
	```c++
	int 					_serSocketFd;
	int 					_port;
	std::string 			_password; //pass del server o del cliente que te pasa
	
	std::vector<Client> 		_clients;
	std::vector<Channel> 		_channels;
	std::vector<struct pollfd> 	_fds;
	```

	- *Funciones Privadas*. Creo que coinciden con las instrucciones que se piden en el subject (\_handleCapabilities es necesaria para [capability negotiation](https://modern.ircdocs.horse/#capability-negotiation)  :
	```c++
	void	_handleCapabilities(Client *cli, std::vector<std::string> params);
	void	_authenticatePassword(Client *cli, std::vector<std::string> params);
	void	_setNickname(Client *cli, std::vector<std::string> params);
	void	_setUser(Client *cli, std::vector<std::string> params);
	void	_handleJoin(Client *cli, std::vector<std::string> params, bool UserChannel);
	void	_handlePrivmsg(Client *cli, std::vector<std::string> params);
	void	_handleKick(Client *cli, std::vector<std::string> params);
	void	_handleInvite(Client *cli, std::vector<std::string> params);
	void	_handleTopic(Client *cli, std::vector<std::string> params);
	void	_handleMode(Client *cli, std::vector<std::string> params);
	```
	- *Funciones Privadas*. Creo que son adicionales:
	```c++
	void	_handlePing(Client *cli, std::vector<std::string> params);
	void	_sendPing(Client *cli, std::vector<std::string> params);
	void	_handleQuit(Client *cli, std::vector<std::string> params);
	void	_handleWhoIs(Client *cli, std::vector<std::string> params);
	```
	- *Funciones publicas*. Aquí sólo hay alguna (ver repo):
		- `void		check_comand(Client *cli );`.  Chequea : "NICK", "USER", "JOIN", "PRIVMSG", "KICK", "INVITE", "TOPIC", "MODE", "PING", "PASS", "WHOIS", "QUIT" . Si no es uno de estos comandos lanza el error **ERR_UNKCMD421**.
Header:
- ircserv.hpp
	- define 9 ERR , 1 MEG y un END.
	- un ENUM denominado `_statusClient`
	- un par de funciones

### [src](https://github.com/MarcTorresss/ft_irc/tree/main/src)

- Channel.cpp
- Client.cpp
- Server.cpp
- commands.cpp
- main.cpp
- utils.cpp
