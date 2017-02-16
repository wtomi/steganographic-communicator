
#include "User.h"
#include "ReadBuffer.h"
#include "WriteBuffer.h"
#include "socket_headers.h"

static const int BUFFSIZE = 4096;

void *client_loop(void *arg) {
    
    int sck = *((int *)arg);
    User user(sck);
    
    
    pthread_exit(NULL);
}


