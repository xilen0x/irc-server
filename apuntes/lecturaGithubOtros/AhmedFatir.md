# [AhmedFatir in Gihub](https://github.com/AhmedFatir/ft_irc/tree/master)

## Carpetas

### [inc](https://github.com/AhmedFatir/ft_irc/tree/master/INC)  

- Clases Mandatory:

	- [Channel.hpp](https://github.com/AhmedFatir/ft_irc/blob/master/INC/Channel.hpp), variables:
	```c++
	int				invit_only;
	int				topic;
	int				key;
	int				limit;
	bool				topic_restriction;
	std::string			name;
	std::string			time_creation;
	std::string			password;
	std::string			created_at;
	std::string			topic_name;
	std::vector<Client>	clients;
	std::vector<Client>	admins;
	std::vector<std::pair<char, bool> >	modes;
	```
	- [Client.hpp](https://github.com/AhmedFatir/ft_irc/blob/master/INC/Client.hpp) , variables:
	```c++
	int						fd;
	bool					isOperator;
	bool					registered;
	std::string				nickname;
	bool					logedin;
	std::string				username;
	std::string				buffer;
	std::string				ipadd;
	std::vector<std::string>	ChannelsInvite;
	```
	- [Server.hpp](https://github.com/AhmedFatir/ft_irc/blob/master/INC/Server.hpp).
		- Variables:
		```c++
		int					port;
		int					server_fdsocket;
		static bool				Signal;
		std::string				password;
		std::vector<Client>		clients;
		std::vector<Channel>		channels;
		std::vector<struct pollfd>	fds;
		struct sockaddr_in		add;
		struct sockaddr_in		cliadd;
		struct pollfd			new_cli;
		```
		- Comandos implementados (Ver carpeta [CMD](https://github.com/AhmedFatir/ft_irc/tree/master/CMD) : INVITE, JOIN, KICK, MODE, PART, PRIVMSGM, QUIT, TOPIC
	- [replies.hpp](https://github.com/AhmedFatir/ft_irc/blob/master/INC/replies.hpp)
		- Define 10 RPL , 15 ERR y CRLF="\r\n" 

- Clases Bonus:
	- [Bot.hpp](https://github.com/AhmedFatir/ft_irc/blob/master/INC/Bot.hpp)
	- [Player.hpp](https://github.com/AhmedFatir/ft_irc/blob/master/INC/Player.hpp)

### [src](https://github.com/AhmedFatir/ft_irc/tree/master/SRC)

