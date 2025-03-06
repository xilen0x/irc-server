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

Ctrl+n   pasar a la siguiente sala
Ctrl+p	pasar sala anterior
```

## Send private messages 

### to any client
```
#OPTION 1: From the main room
/QUOTE PRIVMSG nickname : message

#OPTION 2: From a channel room

/QUOTE PRIVMSG nickname : message

```

### to a channel  (broadcast to everyone in a channel)
```
#From the main room:
/QUOTE PRIVMSG #channel : message

#From a channel:
message

/QUOTE PRIVMSG #otherChannel : message

## cuando se esta en una sala se puede enviar mensaje sin formato IRC  a todos los del canal
message            
```
## KICK - Eject a client from the channel
```
#From the main room:
/KICK #channel nick

#From a channel room:
/KICK nick
```
## INVITE - Invite a client to a channel
```
#From the main room:
/INVITE nickname #channel

#From a channel room:
/INVITE nickname
```
## TOPIC - Change or view the channel topic

### From the main room:

- View actual topic : `/topic #channel`
- Change topic : `/topic #channel newTopic`   
- Empty topic: `/quote topic #channel :`   Se necesita **quote** para que lo deje *empty*

Si se entra a un *channel room* y luego se vuelve a la *main room*, los mensajes el **topic** no aparecen en la *main room* sino en el *channel room*

### From a channel room:

- View actual topic : `/topic`
- Change topic : `/topic newTopic`
- Empty topic: `/quote topic #channel :` Se necesita **quote** para que lo deje *empty*

## MODE Change the channel’s mode:

### MODE i: Set/remove Invite-only channel
```
#From the main room:
/mode #channelName +i(/-i)

#From a channel room:
/mode +i(/-i)
```
### MODE t: Set/remove the restrictions of the TOPIC command to channel operators
```
#From the main room:
/mode #channelName +t(/-t)

#From a channel room:
/mode +t(/-t)
```
### MODE k: Set/remove the channel key (password)
```
#From the main room:
/mode #channelName +k(/-k) channelKey

#From a channel room:
/mode +k(/-k) channelKey
```
### MODE o: Give/take channel operator privilege
```
#From the main room:
/mode #channel +o(/-o) nickname

#From a channel room:
/mode +o(/-o) nickname
```
### MODE l: Set/remove the user limit to channel
```
#From the main room:
/mode #channelName +l numLimit   
/mode #channelName -l

#From a channel:
/mode #channelName +l numLimit   
/mode #channel -l
```

## Send file

It's better to have all files to send in a folder . Exmaple : `/home/apardo-m/origen`

On client UNO:

```
/DCC SEND DOS origen/FileName
```

On Client DOS (the file is saved in folder `/home/apardo-m` )

```
/DCC GET UNO FileName
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
