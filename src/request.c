#include <stdlib.h>
#include <stdio.h>

#include <sys/socket.h>

int receive_request(int resp_sock, char ** buffer, int max_size) {
   return recv(resp_sock, *buffer, max_size, 0);
}

int handle_request(int resp_sock, char * request, int size) {
   // Get the request methode
   char * method = malloc(8*sizeof(char));
   sscanf(request, "%s", method);
   printf("[HUGOTTP] %s\n", method);
   return 0;
}
