
#include "bircd.h"

/*
  Programa q implementa un servidor de chat básico:
    Crea un socket para aceptar conexiones.
    Usa select para manejar múltiples clientes simultáneamente sin bloqueo.
    Permite a los clientes enviar mensajes que se retransmiten a todos los demás clientes conectados.
*/
int	main(int ac, char **av)
{
  t_env	e;

  init_env(&e);         // Inicializa la estructura global del entorno.
  get_opt(&e, ac, av);  // Procesa los argumentos de entrada, obtiene el puerto.
  srv_create(&e, e.port); // Crea el socket del servidor y lo configura.
  main_loop(&e);        // Inicia el bucle principal que maneja los eventos.
  return (0);
}

/*
init_env: Inicializa la estructura t_env:

    Obtiene el límite de descriptores (getrlimit).
    Reserva memoria para los descriptores de archivo (malloc).
    Inicializa cada descriptor como FD_FREE usando clean_fd.

get_opt: Procesa los argumentos de la línea de comandos:

    Verifica que haya exactamente dos argumentos (programa y puerto).
    Convierte el puerto en entero (atoi) y lo almacena en e->port.

srv_create: Configura el servidor:

    Crea un socket (socket).
    Configura su dirección (bind) para aceptar conexiones en cualquier IP y el puerto dado.
    Lo pone en modo escucha (listen).
    Registra el socket en la estructura t_fd con tipo FD_SERV y asigna srv_accept como función de lectura.

main_loop: Inicia el bucle infinito que:

    Configura los conjuntos de descriptores activos (init_fd).
    Espera eventos con select (do_select).
    Procesa los descriptores listos (check_fd).
*/