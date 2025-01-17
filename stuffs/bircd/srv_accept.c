
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "bircd.h"


/*Acepta una conexión entrante (accept).
Limpia el descriptor del cliente y lo registra como FD_CLIENT.
Asigna funciones de lectura (client_read) y escritura (client_write) para el cliente.*/
void			srv_accept(t_env *e, int s)
{
  int			cs;
  struct sockaddr_in	csin;
  socklen_t		csin_len;

  csin_len = sizeof(csin);
  cs = X(-1, accept(s, (struct sockaddr*)&csin, &csin_len), "accept");
  printf("New client #%d from %s:%d\n", cs,
	 inet_ntoa(csin.sin_addr), ntohs(csin.sin_port));
  clean_fd(&e->fds[cs]);
  e->fds[cs].type = FD_CLIENT;
  e->fds[cs].fct_read = client_read;
  e->fds[cs].fct_write = client_write;
}
