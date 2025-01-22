# Basic algorithm

1. Start server with port number and put in listen mode.
2. Start client with port number.
3. *Socket level*: Create connetion.
	1. Client ask connection using *socket*
	2. Server accept connection using *socket*
4. Server in listen mode.
5. IRC client-server connection/comunication:
	1. **Connection Registration**:
		1. Client ask for *IRC Registration*
		2. Server:
			- If (not format error or not repeat nickname) then server send OK to client (Accept connection in **IRC level**)
			- else send Error and go to **4**.		
	2. **IRC Commands**:
		- **Ctrl+C** or **QUIT**(not required by subject) from client to server. Server clean client info at **IRC level**
6. Server clean client info at **socket level**
