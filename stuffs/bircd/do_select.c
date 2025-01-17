
#include <stdlib.h>
#include "bircd.h"

/*
do_select: Llama a select para esperar eventos en los descriptores:

    Modifica fd_read y fd_write para reflejar los descriptores listos.
*/
void	do_select(t_env *e)
{
  e->r = select(e->max + 1, &e->fd_read, &e->fd_write, NULL, NULL);
}
