# How to Use irc-server with IRSSI
## Connection & Authentication
```
irssi -c 127.0.0.1 -p 50000 -w password -n nickname -!
```
## Update the nickname
```
/NICK newNickname
```
## Join into a channel
``` 
/join #channelName
```
## Leaving a channel (without leaving it)
```
esc+RIGHTARROW
```

## Send private messages 

### to any client
```
#From the main room:


#From a channel:

```

### to a channel  (broadcast to everyone in a channel)
```
#From the main room:
/QUOTE PRIVMSG #channel : message

#From a channel:
message
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

```
## TOPIC - Change or view the channel topic
```

```
## MODE Change the channel’s mode:
```

```
### MODE i: Set/remove Invite-only channel
```

```
### MODE t: Set/remove the restrictions of the TOPIC command to channel operators
```

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

# How to Use irc-server with netcat (nc)
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
## Join into a channel
``` 
join #channelName
```
## Leaving a channel (without leaving it)

> apardo-m  Creo que en **nc** no existe esta posibilidad por que no hay cambios de pantalla

```

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
