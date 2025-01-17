
#include "bircd.h"

/*
check_fd: Procesa los descriptores listos:

    Itera sobre todos los descriptores hasta e->maxfd.
    Si un descriptor está listo para lectura o escritura, 
      llama a su función correspondiente (fct_read o fct_write).
*/
void	check_fd(t_env *e)
{
  int	i;

  i = 0;
  while ((i < e->maxfd) && (e->r > 0))
    {
      if (FD_ISSET(i, &e->fd_read))
	e->fds[i].fct_read(e, i);
      if (FD_ISSET(i, &e->fd_write))
	e->fds[i].fct_write(e, i);
      if (FD_ISSET(i, &e->fd_read) ||
	  FD_ISSET(i, &e->fd_write))
	e->r--;
      i++;
    }
}
