## Class Channel

```c++
private:
	std::string		_channelName;
	bool 			_inviteOnly;

	std::string		_topic; // Tema del canal
	bool			_topicRestricted; // Indica si solo los operadores pueden cambiar el topic

	std::string		_channelKey;

	bool			_hasUserLimit;
	unsigned long	_userLimit;

	tipo lista	_operators;
	tipo lista	_memberClients;
	tipo lista	_invitedClients;

```
Duda :

> **Mirar**:  Channel Mode `o: Give/take channel operator privilege`
