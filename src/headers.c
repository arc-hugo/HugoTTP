#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <headers.h>

Headers_Queue init_header_queue() {
   Headers_Queue queue;
   queue.begin = NULL;
   queue.size = 0;
   return queue;
}

int add_header(Headers_Queue *queue, char *name, char *value) {
   // Creating header
   Header * header = malloc(sizeof(Header));
   header->name = malloc((strlen(name)+1));
   header->value = malloc((strlen(value)+1));
   memmove(header->name, name, (strlen(name)+1));
   memmove(header->value, value, (strlen(value)+1));

   // Place header
   if (queue->size == 0) {
      queue->begin = header;
   } else if (queue->size == 1) {
      queue->begin->next = header;
   } else {
      Header * aux = queue->begin;
      while (aux->next != NULL)
         aux = aux->next;
      aux->next = header;
   }

   // Increase size
   queue->size++;
   return 0;
}

int remove_first_header(Headers_Queue * queue, char ** name, char ** value) {
   if (queue->size == 0) {
      return -1;
   } else {
      Header * aux = queue->begin;
      queue->begin = aux->next;
      queue->size--;

      memmove(*name, aux->name, strlen(aux->name)+1);
      memmove(*value, aux->value, strlen(aux->value)+1);
      free(aux);
   }
   return 0;
}

void display(Headers_Queue queue) {
   Header * header = queue.begin;
   while (header != NULL) {
      printf("%s -> ", header->name);
      header = header->next;
   }
   printf("\n");
}
