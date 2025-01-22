# Functions

## C Functions

See the next structs:  [sockaddr, sockaddr_storage, sockaddr_in, sockaddr_in6, sockaddr_un, socklen_t, in_addr, in6_addr, in_addr_t, in_port_t, socket address](https://man7.org/linux/man-pages/man3/sockaddr.3type.html)

Function | C Header
------------------ | --------
[fcntl](https://man7.org/linux/man-pages/man2/fcntl.2.html) **Only valid: fcntl(fd, F_SETFL, O_NONBLOCK)** | `#include <fcntl.h>`
[htons](https://man7.org/linux/man-pages/man3/htonl.3p.html) | `#include <arpa/inet.h>`
[htonl](https://man7.org/linux/man-pages/man3/htonl.3p.html) | `#include <arpa/inet.h>`
[ntohs](https://man7.org/linux/man-pages/man3/htonl.3p.html) | `#include <arpa/inet.h>` 
[ntohl](https://man7.org/linux/man-pages/man3/htonl.3p.html) | `#include <arpa/inet.h>` 
[gethostbyname](https://man7.org/linux/man-pages/man3/gethostbyname.3.html) | `#include <netdb.h>` 
[getprotobyname](https://man7.org/linux/man-pages/man3/getprotobyname.3.html) | `#include <netdb.h>`
[poll](https://man7.org/linux/man-pages/man2/poll.2.html) (or equivalent) | `#include <poll.h>`
[signal](https://man7.org/linux/man-pages/man2/signal.2.html) | `#include <signal.h>`
[sigaction](https://man7.org/linux/man-pages/man2/sigaction.2.html) | `#include <signal.h>`
[accept](https://man7.org/linux/man-pages/man2/accept.2.html) | `#include <sys/socket.h>`
[connect](https://man7.org/linux/man-pages/man2/connect.2.html) | `#include <sys/socket.h>`
[bind](https://man7.org/linux/man-pages/man2/bind.2.html) | `#include <sys/socket.h>`
[getsockname](https://man7.org/linux/man-pages/man2/getsockname.2.html) | `#include <sys/socket.h>`
[listen](https://man7.org/linux/man-pages/man2/listen.2.html) | `#include <sys/socket.h>`
[recv](https://man7.org/linux/man-pages/man2/recv.2.html) | `#include <sys/socket.h>`
[send](https://man7.org/linux/man-pages/man2/sendmsg.2.html) | `#include <sys/socket.h>`
[setsockopt](https://man7.org/linux/man-pages/man3/setsockopt.3p.html) | `#include <sys/socket.h>` 
[socket](https://man7.org/linux/man-pages/man2/socket.2.html) | `#include <sys/socket.h>` 
[fstat](https://man7.org/linux/man-pages/man2/stat.2.html) | `#include <sys/stat.h>`
[close](https://man7.org/linux/man-pages/man2/close.2.html) | `#include <unistd.h>`
[lseek](https://man7.org/linux/man-pages/man2/lseek.2.html) | `#include <unistd.h>`
[freeaddrinfo](https://man7.org/linux/man-pages/man3/getaddrinfo.3.html) | `#include <sys/types.h>`, `#include <sys/socket.h>`, `#include <netdb.h>`
[getaddrinfo](https://man7.org/linux/man-pages/man3/getaddrinfo.3.html) | `#include <sys/types.h>`, `#include <sys/socket.h>`, `#include <netdb.h>`
[inet_addr](https://man7.org/linux/man-pages/man3/inet_aton.3.html) | `#include <sys/socket.h>`, `#include <netinet/in.h>`, `#include <arpa/inet.h>`
[inet_ntoa](https://man7.org/linux/man-pages/man3/inet_aton.3.html) | `#include <sys/socket.h>`, `#include <netinet/in.h>`, `#include <arpa/inet.h>`


Alternatives :
- [write](https://man7.org/linux/man-pages/man2/write.2.html), [read](https://man7.org/linux/man-pages/man2/read.2.html)
- **poll** equivalents: [select](https://man7.org/linux/man-pages/man2/select.2.html), [kqueue](https://people.freebsd.org/~jmg/kqueue.historic.man.html), or [epoll](https://man7.org/linux/man-pages/man7/epoll.7.html).

