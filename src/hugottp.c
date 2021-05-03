#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <netinet/in.h>


#include <init.h>
#include <request.h>

int req_sock;

void signal_hander(int sig) {
   close(req_sock);
}

int main(int argc, char ** argv) {
   // Handle signal SIGINT
   signal(SIGINT, signal_hander);
   // Request and response socket
   int resp_sock;
   // Forked process PID
   int pid;
   // Internet server address
   struct sockaddr_in addr;

   // Init the server
   if ((req_sock = request_socket()) < 0)
      return req_sock;
   printf("[HUGOTTP] TCP socket created\n");
   if (request_bind(req_sock, &addr, 0) < 0)
      return -1;
   printf("[HUGOTTP] Socket binded\n");
   if (request_listen(req_sock, 0) < 0)
      return -1;

   // Wait for incomming request
   printf("[HUGOTTP] Ready\n");
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
            int size = receive_request(resp_sock, &buffer, 8000);

            // Handle request
            handle_request(resp_sock, buffer, size);

            close(resp_sock);
            return 0;
            break;
         default:
            // Parent process
            // Closing response socket
            close(resp_sock);
            break;
      }
   }
   close(req_sock);
   return 0;
}
