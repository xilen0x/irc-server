## https://reactive.so/post/42-a-comprehensive-guide-to-ft_irc/

## https://irc.dalexhd.dev/index.html

### COMMANDS DOCS [List of IRC commands](https://en.wikipedia.org/wiki/List_of_Internet_Relay_Chat_commands)
- pass -> Sets a connection password.This command must be sent before the NICK/USER registration combination
	- ex "pass <password>"

- nick -> Allows a client to change their IRC nickname
	- ex "/nick <nickname>"

- privmsg -> Sends message to msgtarget, which is usually a user or channel.
	- ex: "/privmsg msgtarget :message"

- ping -> Lets you determine the network distance between your computer and other users
	- ex: "/ping <nickname>"

- names -> Returns a list of who is on the comma-separated list of <channels>, by channel name.
	- ex: "/names <channel>"

- join -> Makes the client join the channels in the comma-separated list, specifying the passwords, if needed
	- ex: "/join <channels> <keys>"

- part -> Causes a user to leave the channels in the comma-separated list .
	- ex: "/part <channel>"

- topic -> Allows the client to query or set the channel topic on channel
	- ex: "/topic <channel>"

- list -> Lists all channels on the server
	- ex: "/list"

- invites -> Invites nickname to the channel channel
	- ex: "/invites <nickname> <channel>"

- kick -> Forcibly removes client from channel
	- ex: "/kick <client> <channel>"


### Message Format

### [NUMERIC REPLIES](https://modern.ircdocs.horse/#numerics)

Los ha agrupado:

- sin nombre
- ADMIN
- LUSERS
- AWAY
- WHO
- LIST
- NAMES
- INFO


## https://github.com/jdomingu98/ft_irc

Han implementado los siguientes 15 comandos:

### For Mandatory 

Command | Description
 --- | ---
PASS | Set a ‘connection password’. If set, the password must be set before any attempt to register the connection is made.
NICK | Give the client a nickname or change the previous one.
USER | Used at the beginning of a connection to specify the username and realname of a new user.
JOIN | The client wants to join the given channel(s), using the given key (if necessary) for it.
PART | Removes the client from the given channel(s).
PRIVMSG | Send private messages between users, as well as to send messages to channels.
NOTICE | Send notices between users, as well as to send messages to channels.
QUIT | Terminates a client’s connection to the server.
WHO | Used to retrieve information about users on a channel or the entire network.

#### specific to channel operators

Command | Description
 --- | ---
KICK | Request the forced removal of a user from a channel.
INVITE | Invite a user to a invite-only channel.
TOPIC | Change or view the topic of the given channel.
MODE | Set or remove options (or modes) from a given target. Our channels modes: i,t,k,o,l  (este ultimo no es necesario)

### Bonus

Command | Description
 --- | ---
UP | Uploads a file to a channel.
DOWN | Downloads a file from a channel.



## [List of IRC commands](https://en.wikipedia.org/wiki/List_of_IRC_commands) 

Hay 56 comandos :

- ADMIN
- AWAY
- CNOTICE
- CPRIVMSG
- CONNECT
- DIE
- ENCAP
- ERROR
- HELP
- INFO
- INVITE
- ISON
- JOIN
- KICK
- KILL
- KNOCK
- LINKS
- LIST
- LUSERS
- MODE
- MOTD
- NAMES
- NICK
- NOTICE
- OPER
- PART
- PASS
- PING
- PONG
- PRIVMSG
- QUIT
- QUOTE
- REHASH
- RULES
- SERVER
- SERVICE
- SERVLIST
- SQUERY
- SQUIT
- SETNAME
- SILENCE
- STATS
- SUMMON
- TIME
- TOPIC
- TRACE
- USER
- USERHOST
- USERIP
- USERS
- VERSION
- WALLOPS
- WATCH
- WHO
- WHOIS
- WHOWAS
