# IRC Server (Internet Relay Chat)

## Description

The IRC Server project is part of the 42 School educational program, aimed at providing students with a deep understanding of network protocols and the development of chat servers. This project involves implementing an IRC server based on the RFC 1459 protocol, allowing students to handle multiple simultaneous connections and apply advanced network programming concepts.

![screenshot](https://github.com/xilen0x/xilen0x/blob/master/images_x_repos/ourIRCServer.png?raw=true)

## Objectives

Understand the functionality of the IRC protocol and its implementation in a server.

Learn how to manage sockets and I/O multiplexing using select.

Develop skills in network programming and concurrency management.

Improve error handling and security in servers.

## Languages & Technologies

C++98

TCP/IP Sockets

I/O Multiplexing (select)

IRC Protocol (RFC 1459)

Makefile

## Features

Server based on TCP/IP sockets.

Support for multiple simultaneous connections.

Compatible with traditional IRC clients.

Implementation of key IRC protocol commands:

/NICK - Change user nickname.

/USER - Identify the user on the server.

/JOIN - Join a channel.

/PRIVMSG - Send private messages.

/KICK - Remove users from a channel.

/MODE - Modify user and channel modes.

/TOPIC - Set the channel topic.

/QUIT - Disconnect from the server.

## Installation & Execution

Clone this repository:

```
git clone https://github.com/xilen0x/irc-server.git
cd irc-server
```
Compile the project:

```
make
```
Run the server with the required parameters:

```./ircserv <port> <password>```

In another terminal, connect using an IRC client such as irssi.

/server localhost <port> -p <password>
```
irssi -c 127.0.0.1 -p 50000 -w password -n nickname -!
```
## Programming Area

Network Programming

Systems and Servers

Concurrency Management

Security and Error Handling

## Authors

- [albertpardo](https://github.com/albertpardo)
- [Hazeliny](https://github.com/Hazeliny)
- [xilen0x](https://github.com/xilen0x)

## Resources

[About IRC‐Server](https://github.com/xilen0x/irc-server/wiki/About-IRC%E2%80%90Server)

[Usage of Commands](https://github.com/xilen0x/irc-server/wiki/Usage-of-Commands)

