
#include "User.h"
#include "ReadBuffer.h"
#include "WriteBuffer.h"
#include "socket_headers.h"

static const int BUFFSIZE = 4096;

void *client_loop(void *arg) {
    
    int sck = *((int *)arg);
    User user(sck);
    ReadBuffer inBuffer(BUFFSIZE);
    WriteBuffer outBuffer(BUFFSIZE);
    
    char msg_type;
    
    while(recv(sck, &msg_type, sizeof(msg_type), 0) == sizeof(msg_type)) {
        
        switch(msg_type) {
            case 0:
                break;
            default:
                break;
        }
        
    }
    
    
    
    pthread_exit(NULL);
}


