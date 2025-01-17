
#include <stdlib.h>
#include "bircd.h"

//Resetea un descriptor: lo marca como libre y borra sus punteros de función.
void	clean_fd(t_fd *fd)
{
  fd->type = FD_FREE;
  fd->fct_read = NULL;
  fd->fct_write = NULL;
}
