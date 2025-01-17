
#include "bircd.h"

void	main_loop(t_env *e)
{
  while (1)
    {
      init_fd(e);       // Configura los conjuntos de descriptores.
      do_select(e);     // Espera eventos en los descriptores.
      check_fd(e);      // Procesa los descriptores listos.
    }
}
