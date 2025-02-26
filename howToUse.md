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
```
#From the main room:


#From a channel:

```
## Send public messages (broadcast to everyone in a channel)
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

```
## Join into a channel
``` 
join #channelName
```
## Leaving a channel (without leaving it)
```

```

## Send private messages
```

```
## Send public messages(broadcast)
```

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
```

```
## MODE Change the channel’s mode:
```

```
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
### MODE o: Give/take channel operator privilege
```
mode #channelName +o(/-o) nickName
```
### MODE l: Set/remove the user limit to channel
```
mode #channelName +l 25
mode #channelName -l
```