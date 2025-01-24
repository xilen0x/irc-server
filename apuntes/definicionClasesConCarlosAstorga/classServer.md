# Class Server

```c++
private:
	std::string _serverName;
	int			_port;
	std::string	_password;
	int			_fdServer;

	static bool _Signal;

	std::vector<struct pollfd> 	_fdsClients;
	tipo lista	_clients;

	tipo lista	_channels; 
```
