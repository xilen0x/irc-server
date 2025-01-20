# Comandos IRC a Implementar

## Subject mandatory

Según mandatory ¿9 comandos?:

> **20250110** Los apartados **Reply** y **Error** se han de ver si se implementan todos o no.

> Los datos para **Reply** y **Error** he mirado [Assignment 2: Supporting Multiple Clients](https://chi.cs.uchicago.edu/chirc/assignment2.html). No se si haran falta más.

### how execute IRC server
Your executable will be run as follows: `./ircserv <port> <password>`

Where:
- **port**: The port number on which your IRC server will be listening to for incoming IRC connections.
- **password**: The connection password. It will be needed by any IRC client that tries to connect to your server.

### commands

- You must be able to authenticate, set a nickname, a username, join a channel, send and receive private messages using your reference client.
	- [Connection Messages](https://modern.ircdocs.horse/#connection-messages) is associated to **password**.
		- [PASS message](https://modern.ircdocs.horse/#pass-message)
			- Reply
				- **A DEFINIR**
			- Error:
				- **A DEFINIR**
		- [NICK message](https://modern.ircdocs.horse/#nick-message). See example in [Logging into an IRC server](https://chi.cs.uchicago.edu/chirc/irc_examples.html#logging-into-an-irc-server)
			- Reply
				- **A DEFINIR**
			- Error:
				- **A DEFINIR**
		- [USER message](https://modern.ircdocs.horse/#user-message). See example in [Logging into an IRC server](https://chi.cs.uchicago.edu/chirc/irc_examples.html#logging-into-an-irc-server)
			- Reply
				- **A DEFINIR**
			- Error:
				- [ERR_ALREADYREGISTERED (462)](https://modern.ircdocs.horse/#erralreadyregistered-462)

	- [Channel Operations](https://modern.ircdocs.horse/#channel-operations)
		- [JOIN message](https://modern.ircdocs.horse/#join-message). See [Joining, talking in, and leaving a channel](https://chi.cs.uchicago.edu/chirc/irc_examples.html#joining-talking-in-and-leaving-a-channel)
			- Reply
				- **A DEFINIR**
			- Error:
				- **A DEFINIR**
	- [Sending Messages](https://modern.ircdocs.horse/#sending-messages)
		- [PRIVMSG message](https://modern.ircdocs.horse/#privmsg-message). 
			- Talk when users are not in any channel . See [Messaging between users](https://chi.cs.uchicago.edu/chirc/irc_examples.html#messaging-between-users).
			- Talk whe user are in same channel [Joining, talking in, and leaving a channel](https://chi.cs.uchicago.edu/chirc/irc_examples.html#joining-talking-in-and-leaving-a-channel)
			- Reply
				- **A DEFINIR**
			- Error:
				- **A DEFINIR**

- specific to channel operators
	- [Channel Operations](https://modern.ircdocs.horse/#channel-operations)
		- [KICK](https://modern.ircdocs.horse/#kick-message): Eject a client from the channel
			- Reply
				- [RPL_WHOISREGNICK (307)](https://modern.ircdocs.horse/#rplwhoisregnick-307)
			- Errors
				- [ERR_NOSUCHNICK (401)](https://modern.ircdocs.horse/#errnosuchnick-401)
				- [ERR_WASNOSUCHNICK (406)](https://modern.ircdocs.horse/#errwasnosuchnick-406)
				- [ERR_NONICKNAMEGIVEN (431)](https://modern.ircdocs.horse/#errnonicknamegiven-431)
				- [ERR_ERRONEUSNICKNAME (432)](https://modern.ircdocs.horse/#errerroneusnickname-432)
				- [ERR_NICKNAMEINUSE (433)](https://modern.ircdocs.horse/#errnicknameinuse-433)
				- [ERR_NICKCOLLISION (436)](https://modern.ircdocs.horse/#errnickcollision-436)
		- [INVITE](https://modern.ircdocs.horse/#invite-message): Invite a client to an invite-only channel (mode +i)
			- Reply
				- **A DEFINIR**
			- Error:
				- **A DEFINIR**
		- [TOPIC](https://modern.ircdocs.horse/#topic-message): Change the channel topic in a mode +t channel
			- Reply
				- **A DEFINIR**
			- Error:
				- **A DEFINIR**
	- [Server Queries and Commands](https://modern.ircdocs.horse/#server-queries-and-commands)
		- [MODE](https://modern.ircdocs.horse/#mode-message): Change the channel’s modes
			- **i**: Set/remove Invite-only channel
	    	- **t**: Set/remove the restrictions of the TOPIC command to channel operators
    		- **k**: Set/remove the channel key (password)
       		- **o**: Give/take channel operator privilege
			- **l**: Set/remove the user limit to channel
			- Reply
				- **A DEFINIR**
			- Error:
				- **A DEFINIR**

Otros errores que se pueden usar :
- [ERR_NEEDMOREPARAMS (461)](https://modern.ircdocs.horse/#errneedmoreparams-461)

## Comandos adicionales no indicados en el mandatory

- [Connection Messages](https://modern.ircdocs.horse/#connection-messages) 
	- [CAP message](https://modern.ircdocs.horse/#cap-message) enviado por un programa cliente tipo *irssi* al iniciar la comunicación. Posibilidades:
		- Si es el primer comando enviado por el cliente:
			- Se puede Ignorar Por que no se hace NEGOCIACION.
		-Si aparece en cualquier otro momento tras la autentificación se puede optar por una de estas dos opciones:
			1. Enviar un error de que no está soportado
			2. Ignorarlo

	- [QUIT message](https://modern.ircdocs.horse/#quit-message) para cerrar una sesión como alternativa a **Ctrl+C**.

## Para que IRSSI no se desconecte en 301 seconds

- [PING](https://modern.ircdocs.horse/#pong-message)
- [PONG](https://modern.ircdocs.horse/#pong-message)

## ¿Se Necesitan?

- [Channel Operations](https://modern.ircdocs.horse/#channel-operations)
	- [PART message](https://modern.ircdocs.horse/#part-message). For leaving a channel. See [Joining, talking in, and leaving a channel](https://chi.cs.uchicago.edu/chirc/irc_examples.html#joining-talking-in-and-leaving-a-channel)

## COMMAND format

> Consult each command link

### General

COMMAND | Format | Client Example
 -----  |  ----  | -------  
[CAP](https://modern.ircdocs.horse/#cap-message)   | CAP \<subcommand\> [:\<capabilities\>] | CAP LS 302
[PASS](https://modern.ircdocs.horse/#pass-message) | PASS \<password\> | PASS hola 
[NICK](https://modern.ircdocs.horse/#nick-message) | NICK \<nickname\> | NICK Wiz
[USER](https://modern.ircdocs.horse/#user-message) | USER \<username\> 0 * \<realname\> | USER guest 0 * :Ronnie Reagan
[JOIN](https://modern.ircdocs.horse/#join-message) | JOIN \<channel\>{,\<channel\>} [\<key\>{,\<key\>}] | JOIN #foo,#bar fubar,foobar 
[JOIN](https://modern.ircdocs.horse/#join-message) |  *AltParam* 0 | What means 0 as *AltParam*?
[PRIVMSG](https://modern.ircdocs.horse/#privmsg-message) | PRIVMSG \<target\>{,\<target\>} \<text to be sent\> | PRIVMSG Angel :yes I'm receiving it !

Where :
- [key](https://modern.ircdocs.horse/#key-channel-mode) password for a channel
- \<text to be sent\> for a string message this \<text to be sent\> must be start with `:`

### channel operators commands

COMMAND | Format | Client Example | Description
 -----  |  ---   | -------------- | ----
[KICK](https://modern.ircdocs.horse/#kick-message) | KICK Parameters: \<channel\> \<user\> \*( "," \<user\> ) [\<comment\>] | KICK #Finnish John :Speaking English
[INVITE](https://modern.ircdocs.horse/#invite-message) | INVITE \<nickname\> \<channel\> | INVITE Wiz #foo_bar 
[TOPIC](https://modern.ircdocs.horse/#topic-message) | TOPIC \<channel\> [\<topic\>] | TOPIC #test :New topic | Setting the topic on "#test" to  "New topic".
[TOPIC](https://modern.ircdocs.horse/#topic-message) | |  TOPIC #test : | Clearing the topic on "#test"
[TOPIC](https://modern.ircdocs.horse/#topic-message) | |  TOPIC #test   | Checking the topic for "#test"
[MODE](https://modern.ircdocs.horse/#mode-message) |  MODE \<target\> [\<modestring\> [\<mode arguments\>...]] | MODE dan +i | Setting the "invisible" user mode on dan

Where :
- \<comment\> for a string message this \<comment\> must be start with `:`

### To avoid irssi desconnection/connection


COMMAND | Format | Client Example | Description
 -----  |  ---   | -------------- | ----
[PING](https://modern.ircdocs.horse/#pong-message) | PING \<token\> | PING myIRC |
[PONG](https://modern.ircdocs.horse/#pong-message) | PONG [\<serve\r>] \<token\> | PONG 127.0.0.1 myIRC
