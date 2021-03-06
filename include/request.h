#ifndef REQUEST_H__
#define REQUEST_H__

// Hash codes for each methods
#define HUGOTTP_GET 224

// Return effective buffer size or -1 if error
int receive_request(int resp_sock, char ** buffer, int max_size);
// Return -1 if error
int handle_request(int resp_sock, char * request, int size);

#endif
