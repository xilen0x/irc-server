# Ejemplos de uso

> No tiene implementado **CAP**. El servidor envia el error `: 451 * :You have not registered!`

## arranque servidor en un terminal

`./ircserv 4444 hola`

## cliente 1

- arranque *cliente 1* en otro terminal : `nc localhost 4444`
- Comunicación con el servidor :
	```txt
	pass hola
	nick ama
	user amy * * :Amy Pond
	: 001 ama : Welcome to the IRC *server*!
	nick amo
	:ama NICK amo
	nick Pipa
	:amo NICK Pipa
	privmsg car : Hola 
	```
Descripción de los mensajes:
- Enviado por *cliente 1*( proceso autentificación):
	```txt
	pass hola
	nick ama
	user amy * * :Amy Pond
	```
- Enviado por el *server*(confima autentificación):
	```txt
	: 001 ama : Welcome to the IRC *server*!
	```
- Cambio de *NICK* por parte del *cliente 1*:
	```txt
	nick amo
	```
- El *server* confirma al *cliente 1* el cambio de nick:
	```txt
	:ama NICK amo
	```
- Nuevo cambio de *NICK* por parte del *cliente 1*:
	```txt
	nick Pipa
	```
- El *server* confirma al *cliente 1* el cambio de nick:
	```txt
	:amo NICK Pipa
	```
- El *cliente 1* envia un mensaje provado al *nickname* **car**.
	```txt
	privmsg car : Hola 
	```
## cliente 2

- arranque cliente 2 en otro terminal : `nc localhost 4444`
- Comunicación con el servidor :
	```txt
	pass hola
	nick car
	user caro * * :Caro Pond
	: 001 car : Welcome to the IRC server!
	:Pipa!~amy@localhost PRIVMSG car : Hola
	```

Descripción de los mensajes:
- Enviado por *cliente 2*( proceso autentificación):
	```txt
	pass hola
	nick car
	user caro * * :Caro Pond
	```
- Enviado por el *server*(confima autentificación):
	```txt
	: 001 car : Welcome to the IRC server!
	```
- Recepción por parte de *cliente 2* el mensaje privado enviado por el *nick* **Pipa**
	```txt
	:Pipa!~amy@localhost PRIVMSG car : Hola
	```

> *NOTA* : El server no comunica al resto ce clientes cuando un cliente ha 

## Unirse a un *channel* 
### No existe el *channel*
- En el terminal de cliente:
	```txt
	join #uno
	:ama!amy@127.0.0.1 JOIN #uno
	: 353 ama @ #uno :@ama
	: 366 ama #uno :END of /NAMES list
	```
Descripción de los mensajes:
- El cliente se une a un channel denomindo **#uno**:
	```txt
	join #uno
	```
- El servidor le responde con:
	```txt
	:ama!amy@127.0.0.1 JOIN #uno
	: 353 ama @ #uno :@ama
	: 366 ama #uno :END of /NAMES list
	```
> **/NAMES** no está implementado en el servidor

### El *channel existe*

- Cliente que se une:
	```txt
	JOIN #uno
	:car!caro@127.0.0.1 JOIN #uno
	: 353 car @ #uno :@ama car
	: 366 car #uno :END of /NAMES list
	nick ama
	```
En este caso el *server* envía un broadcast al resto de clientes unidos en el *channel*. Ejemplo : `:car!caro@127.0.0.1 JOIN #uno`

## QUIT

Cuando un cliente se desconecta. el server parece enviar un broadcast al resto de clientes.
