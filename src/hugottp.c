#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <netinet/in.h>

#include <init.h>

int main(int argc, char ** argv) {
   // Request and response socket
   int req_sock, resp_sock;
   // Forked process PID
   int pid;
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
   printf("[HUGOTTP] Ready for new connections :\n");
   while (1) {
      if ((resp_sock = accept_connection(req_sock, &addr)) < 0)
         return resp_sock;
      // Fork process to process request
      switch (pid = fork()) {
         case -1:
            perror("Error during fork");
            return -1;
            break;
         case 0:
            // Forked process
            // Closing request socket
            close(req_sock);
            // Request message buffer
            char * buffer = malloc(8000*sizeof(char));
            // Read socket and display message
            if (read(resp_sock, buffer, 8000) < 0) {
               perror("Error reading request");
               return -1;
            }
            printf("%s\n",buffer);

            break;
         default:
            // Parent process
            // Closing response socket
            close(resp_sock);

            break;
      }
   }

   return 0;
}
