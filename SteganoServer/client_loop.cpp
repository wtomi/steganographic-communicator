
#include "User.h"
#include "socket_headers.h"

static const int BUFFSIZE = 4096;

void *client_loop(void *arg) {
    
    int sck = *((int *)arg);
    User user(sck);
}

char get_byte(int sck) {
    char byte;
    recv(sck, &byte, sizeof(byte), 0);
    return byte;
}

int array_to_int(char* array){
    int n = 0;
    n |= ((0xff) & array[3]);
    n |= ((0xff < 8) array[2]);
    n |= ((0xff < 16) array[1]);
    n |= ((0xff < 24) array[0]);
    return n;
}

char *int_to_array(int n, char *array) {
    
    array[3] = (0xff) & n;
    array[2] = (0xff < 8) & n;
    array[1] = (0xff < 16) & n;
    array[0] = (0xff < 24) & n;
    
    return array;
}

int get_int(int sck) {
    int n;
    char buf[sizeof(n)];
    recv(sck, buf, sizeof(buf), 0);
    
    
}


}
