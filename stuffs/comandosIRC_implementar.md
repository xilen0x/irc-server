# Comandos IRC a Implementar

## Subject manatory

Según mandatory ¿9 comandos?:

- You must be able to authenticate, set a nickname, a username, join a channel, send and receive private messages using your reference client.
	- [Connection Messages](https://modern.ircdocs.horse/#connection-messages)
		- [AUTHENTICATE message](https://modern.ircdocs.horse/#authenticate-message)
		- [NICK message](https://modern.ircdocs.horse/#nick-message)
		- [USER message](https://modern.ircdocs.horse/#user-message)
	- [Channel Operations](https://modern.ircdocs.horse/#channel-operations)
		- [JOIN message](https://modern.ircdocs.horse/#join-message)
	- [Sending Messages](https://modern.ircdocs.horse/#sending-messages)
		- [PRIVMSG message](https://modern.ircdocs.horse/#privmsg-message)
- specific to channel operators
	- [Channel Operations](https://modern.ircdocs.horse/#channel-operations)
		- [KICK](https://modern.ircdocs.horse/#kick-message): Eject a client from the channel
		- [INVITE](https://modern.ircdocs.horse/#invite-message): Invite a client to an invite-only channel (mode +i)
		- [TOPIC](https://modern.ircdocs.horse/#topic-message): Change the channel topic in a mode +t channel
	- [Server Queries and Commands](https://modern.ircdocs.horse/#server-queries-and-commands)
		- [MODE](https://modern.ircdocs.horse/#mode-message): Change the channel’s modes
			- **i**: Set/remove Invite-only channel
	    	- **t**: Set/remove the restrictions of the TOPIC command to channel operators
    		- **k**: Set/remove the channel key (password)
       		- **o**: Give/take channel operator privilege
			- **l**: Set/remove the user limit to channel

## Comandos adicionales no indicados en el manatory

- [Connection Messages](https://modern.ircdocs.horse/#connection-messages) 
	- [CAP message](https://modern.ircdocs.horse/#cap-message) enviado por el cliente al iniciar la comunicación.
	- [QUIT message](https://modern.ircdocs.horse/#quit-message) para cerrar una sesión como alternativa a **Ctrl+C**.
