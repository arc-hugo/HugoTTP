#ifndef INIT_H__
#define INIT_H__

/* Internet Protocol family */
#include <netinet/in.h>

// Default server port
#define HUGOTTP_DEFAULT_PORT 8008
// Default number of maximum pending connections accepted
#define HUGOTTP_DEFAULT_PENDING 1000

// Instantiate and return the request socket
// Return -1 if error
int request_socket();
// Bind request socket to default address and chosen port
// Set HUGOTTP_DEFAULT_PORT if port = 0
// Return -1 if error
int request_bind(int req_sock, struct sockaddr_in * addr, int port);
// Listen for max connections on the accept socket
// Set HUGOTTP_DEFAULT_PENDING if max = 0
// Return -1 if error
int request_listen(int req_sock, int max);
// Accept pending connection and return corresponding socket
// Return -1 if error
int accept_connection(int accept_sock, struct sockaddr_in * addr); 

#endif
