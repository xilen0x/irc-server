# Connection Registration

 > **IMPORTANTE!!!!!!!** Si durante **5 minutos** no se interactua con **irssi**, se desconecta del servidor y se vuelve a conectar.
 > **250114** Buscar una manera de evitar la desconexión automatica de **irssi**.

## [Client Capability Negotiation](https://ircv3.net/specs/extensions/capability-negotiation)

Is optional in server. There is a example where the server doesn’t support capability negotiationThere is a example. 

## Connection Registration según [ircdocs.horse](https://modern.ircdocs.horse/#connection-registration)


The recommended order of commands during registration is as follows:

1. CAP LS 302    // client supports [version 302](https://ircv3.net/specs/extensions/capability-negotiation.html#cap-ls-version) of client capability negotiation
2. [PASS](https://modern.ircdocs.horse/#pass-message)			// Password. Es introducido al ejecutar el servidor. Debe enviarse antes de NICK y USER.
	- Where **NICK** is *nickname* and **USER** is *real name*.
	- Mensajes de Error:
		- [ERR_NEEDMOREPARAMS (461)](https://modern.ircdocs.horse/#errneedmoreparams-461)
    	- [ERR_ALREADYREGISTERED (462)](https://modern.ircdocs.horse/#erralreadyregistered-462)
    	- [ERR_PASSWDMISMATCH (464)](https://modern.ircdocs.horse/#errpasswdmismatch-464). In this case. server MAY then close the connection with [ERROR](https://modern.ircdocs.horse/#error-message)
3. [NICK](https://modern.ircdocs.horse/#nick-message) and [USER](https://modern.ircdocs.horse/#user-message)
	- Mensajes de errores para **NICK** :
		- [ERR_NONICKNAMEGIVEN (431)](https://modern.ircdocs.horse/#errnonicknamegiven-431)
		- [ERR_NICKNAMEINUSE (433)](https://modern.ircdocs.horse/#errnicknameinuse-433)
	- Mensajes de errore para **USER**:
		- [ERR_NEEDMOREPARAMS (461)](https://modern.ircdocs.horse/#errneedmoreparams-461)
		- [ERR_ALREADYREGISTRED (462)](https://modern.ircdocs.horse/#erralreadyregistered-462)
4. [Capability Negotiation](https://modern.ircdocs.horse/#capability-negotiation) .The client should request advertised capabilities it wishes to enable here.
5. SASL (if negotiated)  // If the client supports [SASL authentication](https://modern.ircdocs.horse/#authenticate-message) and wishes to authenticate with the server, it should attempt this after a successful [CAP ACK](https://modern.ircdocs.horse/#cap-message) of the sasl capability is received and while registration is suspended.
6. [CAP END](https://modern.ircdocs.horse/#cap-message)       //The registration process is resumed

> Servers **SHOULD** set a reasonable timeout for waiting to complete a lookup of client information (such as hostname or ident for a username) during registration.  

> Additionally, some servers also send a [PING](https://modern.ircdocs.horse/#ping-message) and require a matching [PONG](https://modern.ircdocs.horse/#pong-message) from the client before continuing. This exchange may happen immediately on connection and at any time during connection registration, so clients **MUST** respond correctly to it.

To complete the registration process, server **MUST** send : ( message examples extrated from [chirc by UChicago](https://chi.cs.uchicago.edu/chirc/irc_examples.html)
1. `001` in [RPL_WELCOME](https://modern.ircdocs.horse/#rplwelcome-001) format. Command example : `:bar.example.com 001 amy :Welcome to the Internet Relay Network amy!amy@foo.example.com`
2. `002` in [RPL_YOURHOST](https://modern.ircdocs.horse/#rplyourhost-002) format.
3. `003` in [RPL_CREATED](https://modern.ircdocs.horse/#rplcreated-003) format.
4. `004` in [RPL_MYINFO](https://modern.ircdocs.horse/#rplmyinfo-004) format.
5. At least one `005` in [RPL_ISUPPORT](https://modern.ircdocs.horse/#rplisupport-005) format.
	- this command is designed to advertise many different IRC features, limits, and protocol options that clients should be aware of. See [Feature Advertisement](https://modern.ircdocs.horse/#motd-message)
	- when is necessary to send more than one , the consecutive **RPL_ISUPPORT** numerics **SHOULD** be sent adjacent to each other.
	- A list of **RPL_ISUPPORT** parameters is available in the [RPL_ISUPPORT Parameters](https://modern.ircdocs.horse/#rplisupport-parameters) section.
6. The server **MAY** then send other numerics and messages.
7. The server **SHOULD** then respond as though the client sent the [LUSERS](https://modern.ircdocs.horse/#lusers-message) command and return the appropriate numerics.
8. The server MUST then respond with one of these options:
	- sucessful Message of the Day numerics
	- [ERR_NOMOTD](https://modern.ircdocs.horse/#errnomotd-422) (422) numeric. 

## Connection Registration a probar para evitar [capability negotiation](https://modern.ircdocs.horse/#capability-negotiation)

Idea obtenida de [Assignment 2: Supporting Multiple Clients](https://chi.cs.uchicago.edu/chirc/assignment2.html#connection-registration). Pero no hace referencia a **CAP** e indica que no se implemente **PASS** entre otra indicaciones entre otra indicacioness
ras  
1. [CAP message](https://modern.ircdocs.horse/#cap-message) enviado por el cliente al iniciar la comunicación.
2. [PASS](https://modern.ircdocs.horse/#pass-message)           // **Solicitado en la parte mandatory**
	- Mensajes de Error:
		- [ERR_NEEDMOREPARAMS (461)](https://modern.ircdocs.horse/#errneedmoreparams-461)
    	- [ERR_ALREADYREGISTERED (462)](https://modern.ircdocs.horse/#erralreadyregistered-462)
    	- [ERR_PASSWDMISMATCH (464)](https://modern.ircdocs.horse/#errpasswdmismatch-464). In this case. server MAY then close the connection with [ERROR](https://modern.ircdocs.horse/#error-message)
	
3. [NICK](https://modern.ircdocs.horse/#nick-message) and [USER](https://modern.ircdocs.horse/#user-message)
	- Mensajes de errores para **NICK** :
		- [ERR_NONICKNAMEGIVEN (431)](https://modern.ircdocs.horse/#errnonicknamegiven-431)
		- [ERR_NICKNAMEINUSE (433)](https://modern.ircdocs.horse/#errnicknameinuse-433)
	- Mensajes de errore para **USER**:
		- [ERR_NEEDMOREPARAMS (461)](https://modern.ircdocs.horse/#errneedmoreparams-461)
		- [ERR_ALREADYREGISTRED (462)](https://modern.ircdocs.horse/#erralreadyregistered-462)

El servidor ha de responder con:
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

