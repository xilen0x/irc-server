# DUDAS

## 250111

1. Creo se que puede hacer una **Connection Registration** sin necesidad de que el servidor tenga capacidad de negociación . Ver ejemplo en [Assignment 2: Supporting Multiple Clients](https://chi.cs.uchicago.edu/chirc/assignment2.html#connection-registration)

- **Respuesta**: Tras mirar el código de [AhmedFatir](https://github.com/AhmedFatir/ft_irc)	y [Marc Torres](https://github.com/MarcTorresss/ft_irc). Se ha de gestionar **PASS**, **NICK** y **USER**. Ellso no usan **CAP : Capacidad de Negociación**

2. ¿Se puede inicializar un **server** sin tener ningún **Channel** (no hay usuarios creados) o ha de tener algún **Channel** por defecto ya creado?

- **Respuesta** : [Marc Torres](https://github.com/MarcTorresss/ft_irc) usa el cliente **irssi**. Al usar **irssi**, cuando se conecta el cliente por promera vez, se ha de crear un **Channel** asociado con el con este cliente. iEl servidor informa al cliente **irssi** se ha de creado el **Channel** . Entodes **irssi** envia **MODE +i** para pasarlo a privado.

3. ¿Se han de guardar la información del los **Channel** y **Clients** en algún archivo para que el servidor los carge en cada vez que se reinicie (simulando una BD)? 

## 250112

1. Durante la vida/ejecución del servidor , un cliente dado se puede conectar y desconectar varias veces. ¿Cómo se gestionan sus datos? No se deberian borrar para que el servidor lo recuerde cada vez que este cliente se conecte.

2. ¿Qué hacer si con uno o varios clientes conectados , el servidor se aparga/se vuelve a encender/reinicializar? ¿Se han de repetir el proceso de conexión por parte de los clientes o el servidor ha de ser capaz de reconectar a los clientes?

3. *Channel Operators vs Channel Creator(en un channnel con prefijo `!`*)  ¿Se ipueden crean los dos o con solo el *operator* es suficiente? ( Creo que el subject no comenta nada sobre el *Creator*)

4. ¿Qué pasa si el *Channel Operator* se da de baja/elimina como cliente?

5. ¿Cómo se gestiona el cliente o clientes que están conectados pero no forman parte de ningun *channnel*? 
	- ¿Sólo se pueden comunicar entre ellos?
	- ¿Cómo saben si hay otro cliente conectado en el servidor i/o en un channnel?

## 250114

- En el proceso de **Connection Registration** , una vez el cliente ha enviado los datos requeridos, el servidor ha de enviar unos mensajes de conformación. En [ircdocs](https://modern.ircdocs.horse/#connection-registration) se indican varios mensaes de respuesta. 
	- Mirando el programa de :
		- [AhmedFatir](https://github.com/AhmedFatir/ft_irc) sólo ha imlementado el **001**
		- [Marc Torres](https://github.com/MarcTorresss/ft_irc) ha implementado : **001** y **002**
	- **¿Cómo lo haremos nosotros?**

## 250115

1. Como funciona el *AltParam 0* en [JOIN](https://modern.ircdocs.horse/#join-message)

2. **Irssi** se desconecta y se conecta cada 5 minutos. Se ha detectado que pone un mensaje en pantalla : `Irssi: No PONG reply from server 127.0.0.1 in 301 seconds, disconnecting`

- **Respuesta** : Se de implementar el comando [PING](https://modern.ircdocs.horse/#pong-message) y enviar la respuesta [PONG](https://modern.ircdocs.horse/#pong-message) [PONG](https://modern.ircdocs.horse/#pong-message) 
