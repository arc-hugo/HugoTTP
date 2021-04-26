#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>

#include "../include/init.h"

// Default server port
#define HUGOTTP_DEFAULT_PORT 8080
// Default number of maximum pending connections accepted
#define HUGOTTP_DEFAULT_PENDING 1000

int accept_socket () {
   // Instantia the accept socket
   int accept_sock;
   if ((accept_sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
      perror("Error during socket creation");
      return -1;
   }
   return accept_sock;
}

int accept_bind(int accept_sock, struct sockaddr_in * addr, socklen_t addr_len, int port) {
   // Default or custom port
   if (port == 0)
      port = HUGOTTP_DEFAULT_PORT;
   // Setup the address
   memset((char *)addr, 0, sizeof(*addr));
   addr->sin_family = AF_INET;
   addr->sin_addr.s_addr = htonl(INADDR_ANY);
   addr->sin_port = htons(HUGOTTP_DEFAULT_PORT);

   // Bind socket to address
   if (bind(accept_sock, (struct sockaddr *) addr, sizeof(*addr)) ) {
      perror("Error during socket bind");
      return -1;
   }
   return 0;
}

int accept_listen(int accept_sock, int max) {
   // Default or custom max pending connection
   if (max == 0)
      max = HUGOTTP_DEFAULT_PENDING;
   // Setup the listening socket 
   if (listen(accept_sock, max) < 0) {
      perror("Error during listen");
      return -1;
   }
   return 0;
}
