#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>

#include <init.h>

int request_socket () {
   // Instantiate the accept socket
   int req_sock;
   if ((req_sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
      perror("[HUGOTTP] Error during socket creation");
   }
   return req_sock;
}

int request_bind(int req_sock, struct sockaddr_in * addr, int port) {
   // Default or custom port
   if (port == 0)
      port = HUGOTTP_DEFAULT_PORT;
   // Setup the address
   memset((char *)addr, 0, sizeof(*addr));
   addr->sin_family = AF_INET;
   addr->sin_addr.s_addr = htonl(INADDR_ANY);
   addr->sin_port = htons(HUGOTTP_DEFAULT_PORT);

   // Bind socket to address
   if (bind(req_sock, (struct sockaddr *) addr, sizeof(*addr)) ) {
      perror("[HUGOTTP] Error during socket bind");
      return -1;
   }
   return 0;
}

int request_listen(int req_sock, int max) {
   // Default or custom max pending requests
   if (max == 0)
      max = HUGOTTP_DEFAULT_PENDING;
   // Setup the listening socket
   if (listen(req_sock, max) < 0) {
      perror("[HUGOTTP] Error during listen");
      return -1;
   }
   return 0;
}

int accept_connection(int req_sock, struct sockaddr_in * addr) {
   int resp_sock;
   socklen_t addrlen = sizeof(*addr);
   if ((resp_sock = accept(req_sock, (struct sockaddr*) addr, &addrlen)) < 0) {
      perror("[HUGOTTP] Error accepting connection");
   }
   return resp_sock;
}
