
#include "User.h"
#include "Buffer.h"
#include "ReadBuffer.h"
#include "WriteBuffer.h"
#include "socket_headers.h"
#include "Socket.h"
#include "client_loop.h"

#include <map>
#include <string>
#include <iostream>
#include <pthread.h>
#include <exception>

static const char *SERVER_PASSWORD = "1234";
static const int USER_NAME_MAX_SIZE = 30;
static const int BUFFSIZE = 4096;

static const char SERV_AUTHENTICATE = 1;
static const char SERV_SEND_CONTACTS = 2;
static const char SERV_PASS_MSG = 3;

static const char USER_AUTH = 1;
//subtypes
static const char USER_AUTH_SUCCESS = 1;
static const char USER_AUTH_FAILURE = 2;
//end subtypes
static const char USER_SEND_CONTACTS = 2;
//subtypes
static const char USER_SEND_CONTACTS_PART = 1;
static const char USER_SEND_CONTACTS_ALL = 1;
//end subtypes

typedef std::map<std::string, User*> mapusers;
mapusers users;
pthread_mutex_t mutex_users;

/******************************************************************************/

void init_client_loop();
void put_msg_into_buf(Socket *sck, ReadBuffer *inBuffer);
bool add_user(User *user);
bool delete_user(User *user);
void authenticate(User *user, ReadBuffer *inBuffer, WriteBuffer * outBuffer);
void free_resources(User *user);

/******************************************************************************/

void *client_loop(void *arg) {

    Socket sck(*((int*) arg));
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
                    authenticate(&user, &inBuffer, &outBuffer);
                    break;
                case SERV_SEND_CONTACTS:
                    break;
                case SERV_PASS_MSG:
                    break;
                default:
                    break;
            }

        }
    } catch (SocketClosedException &e) {
        std::cout << "Socket closed" << std::endl;
        //std::cout << std::cerr << e.what() << std::endl;
        free_resources(&user);
    } catch (SocketErrorException &e) {
        std::cout << "Socket error" << std::endl;
        //std::cout << std::cerr << e.what() << std::endl;
        free_resources(&user);
    } catch (...) {
        std::cout << "Socket other exception" << std::endl;
        //std::cout << std::cerr << "Some other exception" << std::endl;
        free_resources(&user);
    }
    free_resources(&user);
    pthread_exit(NULL);
}

void init_client_loop() {
    pthread_mutex_init(&mutex_users, NULL);
}

void put_msg_into_buf(Socket *sck, ReadBuffer *inBuffer) {
    //read into buffer a message wich begins with int indicating its size
    //server reject messages of size greater then buffer length
    int size = sck->recvInt();
    if (size > inBuffer->GetCapacity())
        throw TooBigMessageException();
    int len = sck->recvChunk(inBuffer->GetBuffer(), size); //len sould be equal to size anyway
    inBuffer->reset(len); //set buffer position to 0 and bufer limit to len
}

bool add_user(User *user) {
    pthread_mutex_lock(&mutex_users);
    mapusers::iterator it = users.find(*user->GetName());
    if (it == users.end()) {
        users[*user->GetName()] = user;
        user->SetUser_added(true);
    } else {
        user->SetUser_added(false);
    }
    return user->IsUser_added();
}

bool delete_user(User *user) {
    pthread_mutex_lock(&mutex_users);
    int del = users.erase(*user->GetName());
    if (del == 1)
        return true;
    else if (del == 0)
        return false;
    else {
        std::cout << std::cerr << "map.erase returned " << del << std::endl;
        return false;
    }
    pthread_mutex_unlock(&mutex_users);
}

void authenticate(User *user, ReadBuffer *inBuffer, WriteBuffer * outBuffer) {
    outBuffer->reset();
    outBuffer->putByte(USER_AUTH);

    put_msg_into_buf(user->GetSocket(), inBuffer);
    char *password = inBuffer->getCstringPtr();
    if (!strcmp(password, SERVER_PASSWORD)) {
        char *name = inBuffer->getCstringPtr();
        char name_len = inBuffer->lastOperationLen();
        if (name_len < USER_NAME_MAX_SIZE) {
            user->SetName(new string(name));
            if (add_user(user)) {
                printf("User %s authenticated sucessfully; user added\n", name);
                outBuffer->putByte(USER_AUTH_SUCCESS);
                int position = outBuffer->shiftPosition((unsigned int) sizeof (int));
                int len = outBuffer->putCstring("Password and name correct");
                outBuffer->overrideInt(len, position);
            } else {
                printf("User with name: %s already exists\n", name);
                outBuffer->putByte(USER_AUTH_FAILURE);
                int position = outBuffer->shiftPosition(sizeof (int));
                int len = outBuffer->putCstring("User already exists");
                outBuffer->overrideInt(len, position);
            }
        } else {
            printf("Name: %s is too long\n", name);
            outBuffer->putByte(USER_AUTH_FAILURE);
            int position = outBuffer->shiftPosition(sizeof (int));
            int len = outBuffer->putCstring("Name is too long");
            outBuffer->overrideInt(len, position);
        }
    } else {
        printf("Incorrect password\n");
        outBuffer->putByte(USER_AUTH_FAILURE);
        int len = outBuffer->putCstring("Incorrect password");
        int position = outBuffer->shiftPosition(sizeof (int));
        outBuffer->overrideInt(len, position);
    }
    user->GetSocket()->sendChunk(outBuffer->GetBuffer(), outBuffer->GetPosition());
}

void send_contacts(User *user, ReadBuffer *inBuffer, WriteBuffer *outBuffer) {
    if (user->IsUser_added()) {
        outBuffer->reset();
        outBuffer->putByte(USER_SEND_CONTACTS);
        int bytePosition = outBuffer->shiftPosition(sizeof (int));
        int intPosition = outBuffer->shiftPosition(sizeof (int));
        int positionBeforeMessage = outBuffer->GetPosition();
        for (map<string, User*>::iterator it = users.begin(); it != users.end(); it++) {
            try {
                if (*user->GetName() != it->first) {
                    outBuffer->putCstring(it->first.c_str());
                }
            } catch (Buffer::BufferOverflowException &e) {
                //if there is too much data too send it all in single message
                //split it into several messages
                outBuffer->overrideByte(USER_SEND_CONTACTS_PART, bytePosition); //overriding doens't affect Buffer's position
                int msg_size = outBuffer->GetPosition() - positionBeforeMessage; //count the length of the actual message
                outBuffer->overrideInt(msg_size, intPosition);
                user->GetSocket()->sendChunk(outBuffer->GetBuffer(), outBuffer->GetPosition());

                outBuffer->reset();
                outBuffer->putByte(USER_SEND_CONTACTS);
                bytePosition = outBuffer->shiftPosition(sizeof (int));
                intPosition = outBuffer->shiftPosition(sizeof (int));
                positionBeforeMessage = outBuffer->GetPosition();
                msg_size = 0;
            }
            //send last message (maybe the only)
            outBuffer->overrideByte(USER_SEND_CONTACTS_ALL, bytePosition);
            int msg_size = outBuffer->GetPosition() - positionBeforeMessage;
            outBuffer->overrideInt(msg_size, intPosition);
            user->GetSocket()->sendChunk(outBuffer->GetBuffer(), outBuffer->GetPosition());
        }
    } else {
        throw UnauthenticatedUserException();
    }
}

void free_resources(User * user) {
    if (user->IsUser_added()) {
        delete_user(user);
        std::cout << "User " << user->GetName() << " deleted" << std::endl;
    }
    pthread_exit(NULL);
}



