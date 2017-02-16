
#include "User.h"
#include "ReadBuffer.h"
#include "WriteBuffer.h"
#include "socket_headers.h"
#include "socket_handling.h"
#include "Socket.h"

#include <map>
#include <string>
#include <iostream>

static const int BUFFSIZE = 4096;

static const char SERV_AUTHENTICATE = 1;
static const char SERV_SEND_CONTACTS = 2;
static const char SERV_PASS_MSG = 3;

std::map<std::string, User*> users();

void *client_loop(void *arg) {

    Socket sck(*((int*)arg));
    User user(&sck);
    ReadBuffer inBuffer(BUFFSIZE);
    WriteBuffer outBuffer(BUFFSIZE);

    char msg_type;
    bool out = false;

    try {
        while (!out) {
            msg_type = sck.recvByte();
            switch (msg_type) {
                case SERV_AUTHENTICATE:
                    break;
                case SERV_SEND_CONTACTS:
                    break;
                case SERV_PASS_MSG:
                    break;
                default:
                    break;
            }

        }
    }
    catch(SocketClosedException &e) {
        std::cout << std::cerr << e.what() << endl;
    }    
    pthread_exit(NULL);
}


