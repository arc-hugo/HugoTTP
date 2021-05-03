#ifndef GET_H__
#define GET_H__

#include <headers.h>

// Response to GET request
int get(int resp_sock, char * path, Headers_Queue * queue);

#endif
