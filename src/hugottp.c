#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <netinet/in.h>

#include "../include/init.h"

int main(int argc, char ** argv) {
   // Request and response socket
   int req_sock, resp_sock;
   // Internet server address
   struct sockaddr_in addr;

   // Init the server
   if ((req_sock = request_socket()) < 0)
      return req_sock;
   if (request_bind(req_sock, &addr, 0) < 0)
      return -1;
   if (request_listen(req_sock, 0) < 0)
      return -1;

   // Wait for incomming request
   while (1) {
      if ((resp_sock = accept_connection(req_sock, &addr)) < 0)
         return resp_sock;
      // Fork process to process request
   }

   return 0;
}
