#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>

#include <get.h>
#include <sys/socket.h>

int ok(int resp_sock, FILE * f, char * extension) {
   // Get file length
   fseek(f, 0L, SEEK_END);
   int file_size = ftell(f);
   fseek(f, 0L, SEEK_SET);

   // Get file content
   char * body = malloc(file_size);
   fread(body, file_size, 1, f);

   // Construct response
   char * first_line = "HTTP/1.1 200 OK\n";
   char * server = "Server: HugoTTP\n";
   
   char * content_type = malloc(500);
   sprintf(content_type, "Content-Type: text/%s; charset=utf-8\n", extension);
   content_type = realloc(content_type, strlen(content_type)+1);
   
   char * content_length = malloc(500);
   sprintf(content_length, "Content-Length: %d\n", file_size);
   content_length = realloc(content_length, strlen(content_length)+1);

   int resp_size = strlen(first_line)+strlen(server)+strlen(content_type)+strlen(content_length)+file_size+2;
   char * response = malloc(resp_size);
   sprintf(response, "%s%s%s%s\n%s", first_line, server, content_type, content_length, body);

   if (send(resp_sock, response, resp_size, 0) < 0) {
      return -1;
   }

   return 0;
}

int not_found();

int get(int resp_sock, char * path, Headers_Queue * queue) {
   char * name = malloc(1024);
   char * value = malloc(1024);

   if (strcmp(path, "/") == 0) {
      FILE * f = fopen("index.html", "r");
      if (f != NULL) {
         return ok(resp_sock, f, "html");
      }
   } else {

   }
   return 0;
}
