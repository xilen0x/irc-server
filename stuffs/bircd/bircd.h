#ifndef BIRCD_H_
# define BIRCD_H_

# include <sys/select.h>

# define FD_FREE	  0
# define FD_SERV	  1
# define FD_CLIENT	2

# define BUF_SIZE	  4096

//Las macros X y Xv verifican el resultado de operaciones críticas (e.g., socket, bind) y
// manejan errores de forma uniforme mostrando un mensaje y terminando el programa.
# define Xv(err,res,str)	(x_void(err,res,str,__FILE__,__LINE__))
# define X(err,res,str)		(x_int(err,res,str,__FILE__,__LINE__))

# define MAX(a,b)	((a > b) ? a : b)

# define USAGE		"Usage: %s port\n"

typedef struct	s_fd
{
  int	  type;//FD_FREE, FD_SERV, FD_CLIENT
  void	(*fct_read)();//function pointer para leer de un socket
  void	(*fct_write)();//function pointer para escribir en un socket
  char	buf_read[BUF_SIZE + 1];//buffer que se usa para leer de un socket
  char	buf_write[BUF_SIZE + 1];
}		t_fd;

typedef struct	s_env
{
      t_fd    *fds;
      int     port;
      int		  maxfd;//numero maximo de fd
      int		  max;//numero maximo de sockets
      int		  r;//variable que se usa para saber cuantos sockets se estan leyendo
      fd_set	fd_read;//set de sockets que se estan leyendo
      fd_set	fd_write;//set de sockets que se estan escribiendo
}		t_env;

void	init_env(t_env *e);
void	get_opt(t_env *e, int ac, char **av);
void	main_loop(t_env *e);
void	srv_create(t_env *e, int port);
void	srv_accept(t_env *e, int s);
void	client_read(t_env *e, int cs);
void	client_write(t_env *e, int cs);
void	clean_fd(t_fd *fd);
int	x_int(int err, int res, char *str, char *file, int line);
void	*x_void(void *err, void *res, char *str, char *file, int line);
void	init_fd(t_env *e);
void	do_select(t_env *e);
void	check_fd(t_env *e);

#endif /* !BIRCD_H_ */
