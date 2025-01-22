# [Connection Registration](https://modern.ircdocs.horse/#connection-registration)

 > **IMPORTANTE!!!!!!!** Si durante **5 minutos** no se interactua con **irssi**, se desconecta del servidor y se vuelve a conectar.
 > **250114** Buscar una manera de evitar la desconexión automatica de **irssi**.

## Connection Registration sin [capability negotiation](https://modern.ircdocs.horse/#capability-negotiation)

1. [CAP message](https://modern.ircdocs.horse/#cap-message) enviado por el cliente tipo **irssi** al iniciar la comunicación y el servidor lo ignora.
2. [PASS](https://modern.ircdocs.horse/#pass-message)			// Password. Es introducido al ejecutar el servidor. Debe enviarse antes de NICK y USER.
	- Mensajes de Error:
		- [ERR_NEEDMOREPARAMS (461)](https://modern.ircdocs.horse/#errneedmoreparams-461)
    	- [ERR_ALREADYREGISTERED (462)](https://modern.ircdocs.horse/#erralreadyregistered-462)
    	- [ERR_PASSWDMISMATCH (464)](https://modern.ircdocs.horse/#errpasswdmismatch-464). In this case. server MAY then close the connection with [ERROR](https://modern.ircdocs.horse/#error-message)
3. [NICK](https://modern.ircdocs.horse/#nick-message) and [USER](https://modern.ircdocs.horse/#user-message). The order that client send **NICK** and **USER** don't import. 
	- Where **NICK** is *nickname* and **USER** is *real name*.
	- Mensaje de error si no se ha se ha enviado previamente **PASS** desde el cliente:
		- [ERR_NOTREGISTERED (451)](https://modern.ircdocs.horse/#errnotregistered-451)
	- Mensajes de errores para **NICK** :
		- [ERR_NONICKNAMEGIVEN (431)](https://modern.ircdocs.horse/#errnonicknamegiven-431)
		- [ERR_ERRONEUSNICKNAME (432)](https://modern.ircdocs.horse/#errerroneusnickname-432)
		- [ERR_NICKNAMEINUSE (433)](https://modern.ircdocs.horse/#errnicknameinuse-433)
	- Mensajes de errore para **USER**:
		- [ERR_NEEDMOREPARAMS (461)](https://modern.ircdocs.horse/#errneedmoreparams-461)
		- [ERR_ALREADYREGISTRED (462)](https://modern.ircdocs.horse/#erralreadyregistered-462)

> Servers **SHOULD** set a reasonable timeout for waiting to complete a lookup of client information (such as hostname or ident for a username) during registration.  

> Additionally, some servers also send a [PING](https://modern.ircdocs.horse/#ping-message) and require a matching [PONG](https://modern.ircdocs.horse/#pong-message) from the client before continuing. This exchange may happen immediately on connection and at any time during connection registration, so clients **MUST** respond correctly to it.

To complete the registration process, server **MUST** send : ( message examples extrated from [chirc by UChicago](https://chi.cs.uchicago.edu/chirc/irc_examples.html)
1. `001` in [RPL_WELCOME](https://modern.ircdocs.horse/#rplwelcome-001) format. Command example : `:bar.example.com 001 amy :Welcome to the Internet Relay Network amy!amy@foo.example.com`
2. `002` in [RPL_YOURHOST](https://modern.ircdocs.horse/#rplyourhost-002) format.
3. `003` in [RPL_CREATED](https://modern.ircdocs.horse/#rplcreated-003) format.
4. `004` in [RPL_MYINFO](https://modern.ircdocs.horse/#rplmyinfo-004) format.
	- the user modes are `ao` and the channel modes are `mtov` from[Connection Registration](https://chi.cs.uchicago.edu/chirc/assignment2.html#connection-registration)
5. At least one `005` in [RPL_ISUPPORT](https://modern.ircdocs.horse/#rplisupport-005) format.
	- this command is designed to advertise many different IRC features, limits, and protocol options that clients should be aware of. See [Feature Advertisement](https://modern.ircdocs.horse/#motd-message)
	- when is necessary to send more than one, the consecutive **RPL_ISUPPORT** numerics **SHOULD** be sent adjacent to each other.
	- A list of **RPL_ISUPPORT** parameters is available in the [RPL_ISUPPORT Parameters](https://modern.ircdocs.horse/#rplisupport-parameters) section.
6. The server **MAY** then send other numerics and messages.
7. The server **SHOULD** then respond as though the client sent the [LUSERS](https://modern.ircdocs.horse/#lusers-message) command and return the appropriate numerics.
8. The server MUST then respond with one of these options:
	- sucessful Message of the Day numerics
	- [ERR_NOMOTD (422)](https://modern.ircdocs.horse/#errnomotd-422). 

