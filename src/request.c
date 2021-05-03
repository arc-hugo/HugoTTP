#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>

#include <request.h>
#include <headers.h>
#include <get.h>

// Simple hash function for switch on method
int simple_hash (char * word, int max){
   int hash = 0;
   int c = 0, i = 0;
   while ((c = *(word+i)) != 0 && i < max) {
      hash += c;
      i++;
   }
   return hash;
}

// Fetch all request headers in an Headers_List
void fetch_headers(char * req_new_line, Headers_Queue * queue) {
   char * header_name;
   char * header_value;
   while (*(req_new_line+1) != '\n')  {
      header_name = malloc(1024);
      header_value = malloc(1024);

      sscanf(req_new_line, "%[^:]: %[^\n]\n", header_name, header_value);
      req_new_line = req_new_line + strcspn(req_new_line, "\n") + 1;

      header_name = realloc(header_name, (strlen(header_name)+1));
      header_value = realloc(header_value, (strlen(header_value)+1));
      add_header(queue, header_name, header_value);
   }
}

int receive_request(int resp_sock, char ** buffer, int max_size) {
   return recv(resp_sock, *buffer, max_size, 0);
}

int handle_request(int resp_sock, char * request, int size) {
   // Get the request method, path and version
   char * method = malloc(8);
   char * path = malloc(1024);
   char * version = malloc(20);
   sscanf(request, "%s %s %s\n", method, path, version);

   // Resize and print strings
   method = realloc(method, (strlen(method)+1));
   path = realloc(path, (strlen(path)+1));
   version = realloc(version, (strlen(version)+1));
   printf("[HUGOTTP] %s %s %s\n", method, path, version);

   // Remove request first line
   char * req_new_line = request + strcspn(request, "\n") + 1;

   // Fetch all headers in queue
   Headers_Queue queue = init_header_queue();
   fetch_headers(req_new_line, &queue);

   // Hash request method to select the good response
   int hash = simple_hash(method, 8);
   switch (hash) {
      case HUGOTTP_GET:
         return get(resp_sock, path, &queue);
         break;
      default:
         return -1;
   }

   return 0;
}
