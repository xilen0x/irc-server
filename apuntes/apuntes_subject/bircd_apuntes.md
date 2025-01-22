# bircd

Es un ejemplo de servidor web/irc para gestionar la conwexión de varios clientes. Su función es hacer *Broadcasting* de los mensajes enviados por los cientes conectados.

## Funciones C interesantes

- `getrlimit` (usado en *init_env.c*): The *getrlimit()* and *setrlimit()* system calls get and set resource limits.  Each resource has an associated soft and hard limit, as defined by the *rlimit* structure.
- `getprotobyname` (usado en *srv_create.c*) :  The  *getprotobyname()*  function returns a *protoent structure* for the entry from the database that matches the protocol name *name*.  A connection is opened to the database if necessary.

## Forma interesante de gestionar errores y terminar le programa 

El fichero `x.c` contiene dos funciones (ver más abajo el apartado *Funciones*)  para gestionar errores que pueden dar una función. El resultado de la funcióm  se pasa como parametro.

- `int res` y `void *res` son los resultados de la función
- `int err` y `void *err` son los tipos de errores que se han de comparar con el resultado de la función.

### Ejemplo de uso:

La definición de una función es :

```c
void    *x_void(void *err, void *res, char *str, char *file, int line)
```

Su uso :

```c
e->fds = (t_fd*)x_void(NULL, malloc(sizeof(*e->fds) * e->maxfd), "malloc",__FILE__,__LINE__);
```

Donde \_\_FILE\_\_ y \_\_LINE\_\_ son [macros predefinidas en C](https://gcc.gnu.org/onlinedocs/cpp/Standard-Predefined-Macros.html) que se pueden usar para reportar errores

En este caso :

- `void *err` es NULL . Es el error a comprobar
- `void *res` es el resultado de la función `malloc(sizeof(*e->fds) * e->maxfd)`

Es función devuelve `res` si `res != error` , en caso contrario hace un `exit(1)`

### Funciones

```c
include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bircd.h"
 
int x_int(int err, int res, char *str, char *file, int line) 
{ 
  if (res == err)
    {
      fprintf(stderr, "%s error (%s, %d): %s\n",     
          str, file, line, strerror(errno));
      exit (1);
    } 
  return (res);
}
 
void    *x_void(void *err, void *res, char *str, char *file, int line)
{
  if (res == err)
    {
      fprintf(stderr, "%s error (%s, %d): %s\n",     
          str, file, line, strerror(errno));
      exit (1);
  return (res);
}
```

## Definición de variables en bircd.h

**fd** : file descriptor.


```c
# define FD_FREE    0       	// Indica que un fd no esta siendo usado                                                                 
# define FD_SERV    1			// El fd es el servidor		
# define FD_CLIENT  2			// El fd es de un cliente
      
# define BUF_SIZE   4096
      
typedef struct  s_fd
{     
  int   type;

  void  (*fct_read)();			// se asocia a la funcion `srv_accept` ó `client_read`		
  void  (*fct_write)();			// se asocia a la función `client_write`
  char  buf_read[BUF_SIZE + 1];
  char  buf_write[BUF_SIZE + 1];
}       t_fd;					// structura de datos asociados a cada cliente
      
typedef struct  s_env
{     
  t_fd      *fds;				// Equivale a un array de t_fd
  int       port;
  int       maxfd;
  int       max;
  int       r;
  fd_set    fd_read;
  fd_set    fd_write;
}       t_env;					// Structura con todas las variables usadas por el servidor
```

## Algoritmo básico en main.c

`t_env e`: variable del tipo t_env.

Algoritmo:
- init_env(&e) : inicializa `e` con los valores a usar por el servidor. Usa `clean_fd.c` para inicializar cada uno de los *fd* contenido en `e.fds`
- get_opt(&e, ac, av):  if there are not two arguments then print error and exit . Else set port number (don´t check port number is right)
- srv_create(&e, e.port): Activa el servidor usando socket, bind, listen. Su función de lectura de `e.fds[fd as server].fct_read` es `srv_accept()` definida en *srv_accept.c*
- main_loop(&e): Ejecuta el servidor hasta que se pulsa *Ctrl+C*
	- init_fd(e) : para todos los fds que no sean FD_FREE activa `e.fd_read`. Si el *fd*  tiene algo en `e.fds[i].buf_write` activa `e.fd_write`. Las funciín para leer es `client_read`y para escribir `client_write`. 
	- do_select(e) : ejecuta **select** obteniendo el número de fds que han recibido datos.
	- check_fd(e) : para cada *fd* en *e.fds* y mientras no se hayan comprobado toda la cantidad  de *fd* devuelto por **select**,  comprueba si tiene que leer o escribir y ejecuta leer o escribir.
