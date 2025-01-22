# ft_irc concepts

## Server

The server works in *Passive Open Operations*. So , the server uses Pasive sockets.

### Server basic pseudocode

1. Configure how stop server program
	- Activate [signal](https://man7.org/linux/man-pages/man2/signal.2.html) or [sigaction](https://man7.org/linux/man-pages/man2/sigaction.2.html) to manage **CTRL+C** and **CTRL+\\.**

2. Configure server with sockets
	- [socket](https://man7.org/linux/man-pages/man2/socket.2.html)
	- [setsockopt](https://man7.org/linux/man-pages/man3/setsockopt.3p.html) to set options to `socket`
	- [fcntl](https://man7.org/linux/man-pages/man2/fcntl.2.html) **Only valid: fcntl(fd, F_SETFL, O_NONBLOCK)** for **non-blocking** mode.i It's uses for each *fd* acepted
	- [bind](https://man7.org/linux/man-pages/man2/bind.2.html) to assign a specific address and port to a socket.
	- [listen](https://man7.org/linux/man-pages/man2/listen.2.html) for passive sockets. So server can do *Passive Open Operations*.

3. While server is not stop, manage Server communication
	-  (Must use only once in the code) [poll](https://man7.org/linux/man-pages/man2/poll.2.html) (or equivalent) expects events from **fd list** in *timeout* limited time . Returns:
    	- **0** for no events in *timeout* 
		- **-1** for error . **errno** value is activated.
		- The total number of *fd* with events.
	- For each **fd** in a **fd list** 
		- if (fd.revents && POLLIN)  //  See [poll](https://man7.org/linux/man-pages/man2/poll.2.html)
			- [accept](https://man7.org/linux/man-pages/man2/accept.2.html) for new clients and returns:
    			- a new file descriptor representing the client socket
				- **-1** as error.
			- Put new *fd* in **fd list**	
		- else
			- [recv](https://man7.org/linux/man-pages/man2/recv.2.html) to receive data from actual **fd** in a *buffer*
				- **-1** and errno is set to **EAGAIN** or **EWOULDBLOCK** (here client is disconnected
				- number of recived bytes in the *buffer*
			- if *bytes* > 0 gestionar *buffer*
			- else Close conecction

