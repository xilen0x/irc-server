# ▉▉▉ How to Use irc-server with IRSSI ▉▉▉
## Connection & Authentication
The range of accepted ports are: 49152–65535
```
irssi -c 127.0.0.1 -p 50000 -w password -n nickname -!
```
## Update the nickname
```
#OPTION 1:
/NICK newNickname

#OPTION 2:
/QUOTE NICK newNickname
```
## Join into a channel
> NOTE: You must to choose one method only.
``` 
#OPTION 1: From the main room and entering the channel:
/JOIN #channelName

#OPTION 2: From the main room and without leaving it:
/QUOTE JOIN #channelName
```
## Leaving a channel (without leaving it)
```
esc+RIGHTARROW
```

## Send private messages 

### to any client
```
#OPTION 1: From the main room
/QUOTE PRIVMSG nickname : message

#OPTION 2: From a channel
/QUOTE PRIVMSG nickname : message
```

### to a channel  (broadcast to everyone in a channel)
```
#From the main room:
/QUOTE PRIVMSG #channel : message

#From a channel:
message

/QUOTE PRIVMSG #otherChannel : message
```
## KICK - Eject a client from the channel
```
#From the main room:
/KICK #channel nick

#From a channel:
/KICK nick
```
## INVITE - Invite a client to a channel
```
#From the main room:
/INVITE nickname #channel

#From a channel:
/INVITE nickname
```
## TOPIC - Change or view the channel topic

### From the main room:

- View actual topic : `/topic #channel`
- View actual topic : `/quote topic #channel`
- Change topic : `/topic #channel newTopic`   
- Change topic : `/quote topic #channel :newTopic`
- Empty topic: `/quote topic #channel :`

Si se entra a un *channel* y luego se vuelve a la *main room*, los mensajes el **topic** no aparecen en la *main room* sino en el *channel*

### From a channel:

- View actual topic : `/topic`
- Change topic : `/topic newTopic`
- Empty topic: `/quote topic #channel :`

## MODE Change the channel’s mode:

### MODE i: Set/remove Invite-only channel
```
#From the main room:
/mode #channelName +i(/-i)

#From a channel:
/mode +i(/-i)
```
### MODE t: Set/remove the restrictions of the TOPIC command to channel operators
```
#From the main room:
/mode #channelName +t(/-t)

#From a channel:
/mode +t(/-t)
```
### MODE k: Set/remove the channel key (password)
```

```
### MODE o: Give/take channel operator privilege
```
#From the main room:
/mode #3 +o tres

#From a channel:
/mode +o dos
```
### MODE l: Set/remove the user limit to channel
```

```
<br>

# ▉▉▉ How to Use irc-server with netcat (nc) ▉▉▉
## Connection
```
nc -C localhost 50000
```
## Authentication
```
pass password
nick nickname
user nickname 0 * : Full Name 
```

## Update the nickname
```
nick NewNickname
```
## JOIN into a channel
``` 
JOIN #channelName
```

## Send private messages

### to any client

```
privmsg nickname :message
```

### to a channel  (broadcast to everyone in a channel)

```
privmsg #channel :message
```
## KICK - Eject a client from the channel
```
kick #channelName nickName
```
## INVITE - Invite a client to a channel
```
invite nickname #channelName
```
## TOPIC - Change or view the channel topic

- View actual topic : `topic #channel`
- Change topic : `topic #channel :newTopic`
- Empty topic: `topic #channel :`

## MODE Change the channel’s mode:

There are 5 modes: i, t, k, o, l

### MODE i: Set/remove Invite-only channel
```
mode #channelName +i(/-i)
```

### MODE t: Set/remove the restrictions of the TOPIC command to channel operators
```
mode #channelName +t(/-t)
```
### MODE k: Set/remove the channel key (password)
```
mode #channelName +k(/-k) channelKey
```
### MODE o: Give/remove channel operator privilege

> Si solo hay un operador y se hace un autoremove como operador, el canal queda sin operador. Ningun miembro puede usar *MODE*.

```
mode #channelName +o(/-o) nickName
```
### MODE l: Set/remove the user limit to channel

> En el server se ha definido un valor máximo de 100 clientes por canal. El operador puede activar un limite entre 1 y 100.

```
mode #channelName +l numLimit   
mode #channelName -l
```
