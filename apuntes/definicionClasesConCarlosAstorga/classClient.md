## Class Client

```c++
private:
	_fdClient
	_ipClient

	_nick
	_userName
	_realName

	_bufferInMessage
	_bufferOutResponse

	bool 	_hasPass;
	bool	_hasNick;
	bool	_hasUser;
	bool	_hasAuth;      // Usuario atentificado : password, nick, USER	


	tipo lista	_channelsOperator;
	tipo lista	_channelsList;   // Mirar *Dudas* más abajo
```


Dudas:

- Un cliente puede formar parte sólo de un o varios Channels  
- ¿`tipo lista  _channelsList;`es redundante? ¿Si un cliente es en `tipo lista  _memberClients;`de **Class Class** ya no hace falta que este en esta clase?
