#ifndef HEADERS_H__
#define HEADERS_H__

// Elements of queue
typedef struct Header {
   char * name;
   char * value;
   struct Header * next;
}Header;

// Queue of headers
typedef struct Headers_Queue {
   int size;
   Header * begin;
}Headers_Queue;

// Manipulation methods
Headers_Queue init_header_queue();
int add_header(Headers_Queue * list, char * name, char * value);
int remove_first_header(Headers_Queue * queue, char ** name, char ** value);
void display(Headers_Queue queue);
#endif
