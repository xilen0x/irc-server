# [Anthonny and Phroms](https://github.com/Phroms/ft_irc/tree/main)

## Carpetas 

## [inc](https://github.com/Phroms/ft_irc/tree/main/inc)

Clases:

- [Channel.hpp](https://github.com/Phroms/ft_irc/blob/main/inc/Channel.hpp). Variables:
```c++
std::string			name;
std::string			key;
std::vector<Client>	admins;
std::vector<Client>	clients;

std::map<char, bool> 	modes;

std::vector<std::string>	invitedClients;  // Lista de clientes invitados
size_t			maxClients; // Límite máximo de usuarios en el canal
std::string			topic; // Tema del canal
bool				topicRestricted; // Indica si solo los operadores pueden cambiar el topic
bool				invitedOnly; // Flag para indicar si el canal es solo para invitados
```

- [Client.hpp](https://github.com/Phroms/ft_irc/blob/main/inc/Client.hpp). Variables:

```c++
private:
	int 				fd;
	std::string 		ip;
	std::string 		nickname;
	std::string			username;

	std::vector<std::string>	joinedChannels;  // Almacena los canales a los que el cliente se ha unido
public:
	bool				hasPass;
	bool				hasNick;
	bool				hasName;
	bool				handShake;
```

- [Server.hpp](https://github.com/Phroms/ft_irc/blob/main/inc/Server.hpp). 

	- Variables:

	```c++
	private:
		int						port; //port del servidor
		int						socketFd;
		static bool					signal;
		std::string					serverName;
		std::string					password;

		std::vector<Client>			clients;
		std::vector<struct pollfd>		fds; //Vector de pollfd
		std::vector<Channel *>			channels;
		std::map<std::string, Command *>	commands;

	public:
		Message					message;
	```

	- Función para procesar mensajes y ejecutarlo si es necesario:
	```c++
	void Server::processMessage(Client &cliente);
	```


- [Message.hpp](https://github.com/Phroms/ft_irc/blob/main/inc/Message.hpp). La define como struct con funciones  en lugar de clase:

```c++
struct Message
{
    std::string timeNow() const;
    std::string getMessage(int code, Client &client) const;
    std::string getMessage(int code, Client &client, std::string &cmd) const;
    void sendMessage(const Client &client, std::string message);
    void sendHandShake(Client &c);
};
```

Cabeceras:

- [utils.hpp](https://github.com/Phroms/ft_irc/blob/main/inc/Utils.hpp). Tiene la siguiente función:

```c++
std::string convertToCRLF(const std::string& input);
```


## [inc/commnands](https://github.com/Phroms/ft_irc/tree/main/inc/commands)


- [Command.hpp](https://github.com/Phroms/ft_irc/blob/main/inc/commands/Command.hpp). Es tipo virtual/Abstacta con una función virtual:
```c++
virtual void execute(Server &server, Client &c, std::vector<std::string> args) = 0;
```

- [ClassString.hpp](https://github.com/Phroms/ft_irc/blob/main/inc/commands/ClasString.hpp). Implementa una función:

```c++
std::vector<std::string> stringSplit(std::string str, std::string delimiter);
```

Lista de comandos (11 comandos) : invite, join. kick, mode. nick. part. pass. privmsg, quit. topic, who. Todos los commandos heredan de de **Command.hpp** y sobreescriben la función **execute**. Ademas cada comando puede tener funciones adicionales para poder cumplir la función del comando.

- [Invite.hpp](https://github.com/Phroms/ft_irc/blob/main/inc/commands/Invite.hpp)

```c++
void execute(Server &server, Client &c, std::vector<std::string> args);
```

- [Join.hpp](https://github.com/Phroms/ft_irc/blob/main/inc/commands/Join.hpp)

```c++
void createNewChannel(Client &user, Server &server, const std::string &channelName, const std::string &password);
void handleExistingChannel(Client &user, Server &server, Channel *channel, const std::string &channelName);
bool handleJoinChannel(Client &user, Server &server, const std::string &channelName, const std::string &password);
void execute(Server &server, Client &c, std::vector<std::string> args);
```

- [Kick.hpp](https://github.com/Phroms/ft_irc/blob/main/inc/commands/Kick.hpp)

```c++
std::vector<std::string> SplitUsers(const std::string &userList);
std::string FindReason(std::vector<std::string> &args);
std::vector<std::string> SplitChannels(const std::string &channelList);
void execute(Server &server, Client &c, std::vector<std::string> args);
```


- [Mode.hpp](https://github.com/Phroms/ft_irc/blob/main/inc/commands/Mode.hpp)

```c++
void execute(Server &server, Client &c, std::vector<std::string> args);
bool validModeRequest(Server &server, Client &c, std::vector<std::string> args, Channel *&channel);
void applyModeChange(Server &server, Client &c, Channel *channel, std::vector<std::string> args);
void handleInvitedOnly(Channel *channel, bool addMode, Server &server, Client &c);
void handleTopicMode(Channel *channel, bool addMode, Server &server, Client &c);
void handleKeyMode(Channel *channel, bool addMode, Server &server, Client &c, std::vector<std::string> &args, size_t &index);
void handleLimitMode(Channel*channel, bool addMode, Server &server, Client &c, std::vector<std::string> &args, size_t &index);
void handleOperatorMode(Channel *channel, bool addMode, Server &server, Client &c, std::vector<std::string> &args, size_t &index);
void broadcastModeChange(Server &server, Client &c, const std::string &channelName, const std::string &modeChange);
```

- [Nick.hpp](https://github.com/Phroms/ft_irc/blob/main/inc/commands/Nick.hpp)

```c++
void execute(Server &server, Client &c, std::vector<std::string> args);
```


- [Part.hpp](https://github.com/Phroms/ft_irc/blob/main/inc/commands/Part.hpp)

```c++
void execute(Server &server, Client &c, std::vector<std::string> args);
```

- [Pass.hpp](https://github.com/Phroms/ft_irc/blob/main/inc/commands/Pass.hpp)

```c++
void execute(Server &server, Client &c, std::vector<std::string> args);
```

- [Privmsg.hpp](https://github.com/Phroms/ft_irc/blob/main/inc/commands/Privmsg.hpp)

```c++
void execute(Server &server, Client &c, std::vector<std::string> args);
```

- [Quit.hpp](https://github.com/Phroms/ft_irc/blob/main/inc/commands/Quit.hpp)

```c++
void execute(Server &server, Client &c, std::vector<std::string> args);
```
- [Topic.hpp](https://github.com/Phroms/ft_irc/blob/main/inc/commands/Topic.hpp)

```c++
void execute(Server &server, Client &c, std::vector<std::string> args);
```

- [Who.hpp](https://github.com/Phroms/ft_irc/blob/main/inc/commands/Who.hpp)

```c++
void execute(Server &server, Client &c, std::vector<std::string> args);
```
