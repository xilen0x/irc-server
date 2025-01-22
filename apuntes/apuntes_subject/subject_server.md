# Subject

This document is a part of the subject


## Info that doesn´t appears in subjec

- The file **bircd.tar.gz** is provided with the subject. It's a *server* write in c that accept connections from several clients and make messages broadcast . Must be compiled to be used.

- clients installed on 42Barcelona:
	- [Hexchat](https://hexchat.github.io/)
	- [irssi](https://irssi.org/)

## Mandatory

> You **mustn’t** develop a client.

> You **mustn’t** handle server-to-server communication.

Your executable will be run as follows: `./ircserv <port> <password>`

Where:
- **port**: The port number on which your IRC server will be listening to for incoming IRC connections.
- **password**: The connection password. It will be needed by any IRC client that tries to connect to your server.

### Requirements

- The server must be capable of handling multiple clients at the same time and never
hang.
- Forking is not allowed. All I/O operations must be **non-blocking**.
- Only **1 poll()** (or equivalent : `select()`, `kqueue()`, or `epoll()` ) can be used for handling all these operations (read,write, but also listen, and so forth). Because you have to use non-blocking file descriptors, it is possible to use read/recv or write/send functions with no poll() (or equivalent), and your server wouldn’t be blocking. But it would consume more system resources. Thus, if you try to read/recv or write/send in any file descriptor without using poll() (or equivalent), your grade will be 0.
- Several IRC clients exist. You have to choose one of them as a reference. Your
reference client will be used during the evaluation process.
- Your reference client must be able to connect to your server without encountering
any error.
- Communication between client and server has to be done via **TCP/IP** (v4 or v6).
- Using your reference client with your server must be similar to using it with any official IRC server. However, you only have to implement the following features:
    - You must be able to authenticate, set a nickname, a username, join a channel, send and receive private messages using your reference client.
    - All the messages sent from one client to a channel have to be forwarded to every other client that joined the channel.
    - You must have operators and regular users.
		- **operators** or [Operador](https://es.wikipedia.org/wiki/Internet_Relay_Chat) : es un usuario con privilegios de administrador en un canal en específico. Suele tener una @ antes del nick.
    - Then, you have to implement the commands that are specific to channel operators:
        - **KICK** - Eject a client from the channel
        - **INVITE** - Invite a client to a channel
        - **TOPIC** - Change or view the channel topic
        - **MODE** - Change the channel’s mode:
            - **i**: Set/remove Invite-only channel
            - **t**: Set/remove the restrictions of the TOPIC command to channel operators
            - **k**: Set/remove the channel key (password)
            - **o**: Give/take channel operator privilege
			- **l**: Set/remove the user limit to channel
### Test Example

Verify absolutely every possible error and issue (receiving partial data, low bandwidth, and so forth).

To ensure that your server correctly processes everything that you send to it, the following simple test using nc can be done:

```sh
\$> nc 127.0.0.1 6667
com^Dman^Dd
\$>
```

Use **ctrl+D** to send the command in several parts: `’com’`, then `’man’`, then `’d\n’`.

In order to process a command, you have to first aggregate the received packets in order to rebuild it.


> **Parts** : `’com’`, then  **ctrl+D**, then `’man’`, then **ctrl+D** and finally `’d\n’`. 

 **Example received on server** (using a miniserver):

> `Client <4> Data: `**com**`Client <4> Data: `**man**`Client <4> Data: `**d**.

## BONUS

- Handle file transfer
- A bot
