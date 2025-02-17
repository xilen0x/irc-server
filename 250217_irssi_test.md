
Al conectarse un cliente irssi al server :

```sh
New client connected
Received data: CAP LS
PASS hola
NICK dos
USER apardo-m apardo-m 127.0.0.1 :Alberto Pardo Marti

Correct password!
Correct nick format!
1st set a global nick: DOS
Correct user format!
Received data: CAP END
MODE  +i
WHOIS dos

    ----
MODE  => TODO with message MODE  +i
    ----
```

Despues de authenticarse irssi envia :

```txt
CAP END
MODE  +i
WHOIS dos
```

> No se que implica **MODE +i y WHOIS dos**

> Lo curioso es que si desde Irssi se envia un quit. irssi vuelve a conectar , se ha de usar **/RMRECONNS** para que no lo haga

> Usar `irssi -c 127.0.0.1 -p 50000 -w hola -n uno -!` para que no haga una autoreconexión
> usar los comandos con /COMANDO  (borra la pantalla y atiende al comando actual)
