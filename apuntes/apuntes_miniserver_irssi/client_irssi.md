# IRSSI

La ventaja de **irssi** es que se ejecuta en el terminal. Lo que permite ejectar varios clientes en el mismo ordenador sin que se interfietan

> **IMPORTANTE!!!!!!!** Si durante **5 minutos** se se intercatua con **irssi**, se desconecta del servidor y se vuelve a conectar.
> **250114** Buscar una manera de evitar la desconexión automatica de **irssi**.

Mensaje al ejecutarlo por primera vez

```sh
17:48 -!-  ___           _
17:48 -!- |_ _|_ _ _____(_)
17:48 -!-  | || '_(_-<_-< |
17:48 -!- |___|_| /__/__/_|
17:48 -!- Irssi v1.2.3-1ubuntu4 - https://irssi.org
17:48 -!- - - - - - - - - - - - - - - - - - - - - - - - - - - - -
17:48 -!- Hi there! If this is your first time using Irssi, you
17:48 -!- might want to go to our website and read the startup
17:48 -!- documentation to get you going.
17:48 -!-
17:48 -!- Our community and staff are available to assist you or
17:48 -!- to answer any questions you may have.
17:48 -!-
17:48 -!- Use the /HELP command to get detailed information about
17:48 -!- the available commands.
17:48 -!-
17:48 -!- For Ubuntu specific help type "/connect liberachat" and
17:48 -!- "/join #ubuntu" (without the quotes) and ask your
17:48 -!- question.
17:48 -!- - - - - - - - - - - - - - - - - - - - - - - - - - - - -
17:48 -!- Irssi: The following settings were initialized
17:48                        real_name Alberto Pardo Marti
17:48                        user_name apardo-m
17:48                             nick apardo-m
```
Crea un fichero de configuración : `/home/.irssi/config`. En este fichero aparecen, entre otros datos, mis datos extraidos del ordenador.

Pruebo ejecutarlo frente a un server (small_server) que funciona en el puerto 4444. 
Orden de ejecución : `irssi -c 127.0.0.1 -p 4444`
En el *small_server* tras confirmar en pantalla que se ha conectado un cliente,el server recibe:
```txt
Client <4> Data: CAP LS
NICK apardo-m
USER apardo-m apardo-m 127.0.0.1 :Alberto Pardo Marti
```

**Nota** : El texto **Client <4> Data:** no forma parte del mensaje. Lo imprime el server cada vez que recibe información.

> Si irssi no interactua con el server durante 5 minutos, se desconecta y se vuelve a conectar.

Ejemplo de desconexión y conexión :
```txt 
Client <4> Data: CAP LS
NICK apardo-m
USER apardo-m apardo-m 127.0.0.1 :Alberto Pardo Marti
Client <4> Disconnected
Client <4> Connected
Client <4> Data: CAP LS
Client <4> Data: NICK apardo-m
USER apardo-m apardo-m 127.0.0.1 :Alberto Pardo Marti
Client <4> Disconnected
Client <4> Connected
Client <4> Data: CAP LS
NICK apardo-m
Client <4> Data: USER apardo-m apardo-m 127.0.0.1 :Alberto Pardo Marti
Client <4> Disconnected
Client <4> Connected
Client <4> Data: CAP LS
Client <4> Data: NICK apardo-m
USER apardo-m apardo-m 127.0.0.1 :Alberto Pardo Marti
```

## Instrucciones irssi

- /exit : termina el programa y vuelve al terminal

