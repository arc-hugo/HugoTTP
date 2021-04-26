#ifndef INIT_H__
#define INIT_H__

/* Internet Protocol family */
#include <netinet/in.h>

// Instantiate and return the accept socket
// Return -1 if error
int accept_socket();
// Bind accept socket to default address and port
// Return -1 if error
int accept_bind(int accept_sock, struct sockaddr_in * addr, socklen_t addr_len, int port);
// Listen for *max* connections on the accept socket
// Return -1 if error
int accept_listen(int accept_sock, int max);

#endif
