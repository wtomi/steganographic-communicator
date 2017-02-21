
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

static const char *SERVER_PASSWORD = "password";
static const int USER_NAME_MAX_SIZE = 30;
static const int BUFFSIZE = 8192;

static const char SERV_AUTHENTICATE = 1;
static const char SERV_SEND_CONTACTS = 2;
static const char SERV_PASS_MSG = 3;
//subtypes
static const char SERV_PASS_MSG_INFO = 1;
static const char SERV_PASS_MSG_PART = 2;
static const char SERV_PASS_MSG_ALL = 3;
//end subtypes

static const char USER_AUTH = 1;
//subtypes
static const char USER_AUTH_SUCCESS = 1;
static const char USER_AUTH_FAILURE = 2;
//end subtypes
static const char USER_SEND_CONTACTS = 2;
//subtypes
static const char USER_SEND_CONTACTS_PART = 1;
static const char USER_SEND_CONTACTS_ALL = 2;
//end subtypes
static const char USER_PASS_MSG = 3;
//subtypes
static const char USER_PASS_MSG_INFO = 1;
static const char USER_PASS_MSG_PART = 2;
static const char USER_PASS_MSG_ALL = 3;
//end subtypes

typedef std::map<std::string, User*> mapusers;
mapusers users;
pthread_mutex_t mutex_users;

/******************************************************************************/

void init_client_loop();
void put_msg_into_buf(Socket *sck, ReadBuffer *inBuffer);
bool add_user(User *user);
bool delete_user(User *user);
bool authenticate(User *user, ReadBuffer *inBuffer, WriteBuffer * outBuffer);
void free_resources(User *user);
void send_contacts(User *user, ReadBuffer *inBuffer, WriteBuffer *outBuffer);
void pass_message(User *user, ReadBuffer *inBuffer, WriteBuffer *outBuffer);

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
            pthread_mutex_lock(user.GetRefMutex_socket());
            switch (msg_type) {
                case SERV_AUTHENTICATE:
                    authenticate(&user, &inBuffer, &outBuffer);
                    break;
                case SERV_SEND_CONTACTS:
                    send_contacts(&user, &inBuffer, &outBuffer);
                    break;
                case SERV_PASS_MSG:
                    pass_message(&user, &inBuffer, &outBuffer);
                    break;
                default:
                    break;
            }
            pthread_mutex_unlock(user.GetRefMutex_socket());
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
        std::cout << "Other exception" << std::endl;
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
    unsigned int size = sck->recvInt();
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
    pthread_mutex_unlock(&mutex_users);
    return user->IsUser_added();
}

bool delete_user(User *user) {
    bool result;
    pthread_mutex_lock(&mutex_users);
    int del = users.erase(*user->GetName());
    if (del == 1)
        result = true;
    else if (del == 0)
        result = false;
    else {
        std::cout << std::cerr << "map.erase returned " << del << std::endl;
        result = false;
    }
    pthread_mutex_unlock(&mutex_users);
    return result;
}

bool authenticate(User *user, ReadBuffer *inBuffer, WriteBuffer * outBuffer) {
    bool result = false;

    outBuffer->reset();
    outBuffer->putByte(USER_AUTH);

    put_msg_into_buf(user->GetSocket(), inBuffer);
    char *password = inBuffer->getCstringPtr();
    if (!strcmp(password, SERVER_PASSWORD)) {
        char *name = inBuffer->getCstringPtr();
        int name_len = inBuffer->lastOperationLen();
        if (name_len < USER_NAME_MAX_SIZE) {
            user->SetName(new string(name));
            if (add_user(user) == true) {
                printf("User %s authenticated sucessfully; user added\n", name);
                outBuffer->putByte(USER_AUTH_SUCCESS);
                int position = outBuffer->shiftPosition((unsigned int) sizeof (int));
                int len = outBuffer->putCstring("Password and name correct");
                outBuffer->overrideInt(len, position);
                result = true;
            } else {
                printf("User with name: %s already exists; authentication failure\n", name);
                outBuffer->putByte(USER_AUTH_FAILURE);
                int position = outBuffer->shiftPosition(sizeof (int));
                int len = outBuffer->putCstring("User already exists");
                outBuffer->overrideInt(len, position);
            }
        } else {
            printf("Name: %s is too long; authentication failure\n", name);
            outBuffer->putByte(USER_AUTH_FAILURE);
            int position = outBuffer->shiftPosition(sizeof (int));
            int len = outBuffer->putCstring("Name is too long");
            outBuffer->overrideInt(len, position);
        }
    } else {
        printf("Incorrect password\n");
        outBuffer->putByte(USER_AUTH_FAILURE);
        int position = outBuffer->shiftPosition(sizeof (int));
        int len = outBuffer->putCstring("Incorrect password");
        outBuffer->overrideInt(len, position);
    }
    user->GetSocket()->sendChunk(outBuffer->GetBuffer(), outBuffer->GetPosition());
    return result;
}

void send_contacts(User *user, ReadBuffer *inBuffer, WriteBuffer *outBuffer) {
    if (user->IsUser_added()) {
        outBuffer->reset();
        outBuffer->putByte(USER_SEND_CONTACTS);
        int bytePosition = outBuffer->shiftPosition(1);
        int intPosition = outBuffer->shiftPosition(sizeof (int));
        int positionBeforeMessage = outBuffer->GetPosition();
        pthread_mutex_lock(&mutex_users);
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
        }
        pthread_mutex_unlock(&mutex_users);
        //send last message (maybe the only)
        outBuffer->overrideByte(USER_SEND_CONTACTS_ALL, bytePosition);
        int msg_size = outBuffer->GetPosition() - positionBeforeMessage;
        outBuffer->overrideInt(msg_size, intPosition);
        user->GetSocket()->sendChunk(outBuffer->GetBuffer(), outBuffer->GetPosition());
    } else {
        throw UnauthenticatedUserException();
    }
}

void pass_message(User *user, ReadBuffer *inBuffer, WriteBuffer *outBuffer) {
    if (user->IsUser_added() == false)
        throw UnauthenticatedUserException();
    char subtype = user->GetSocket()->recvByte();
    if (subtype != SERV_PASS_MSG_INFO)
        throw WrongMessageTypeException();
    //get info from message
    int recipientNameLen = user->GetSocket()->recvInt();
    user->GetSocket()->recvChunk(inBuffer->GetBuffer(), recipientNameLen);
    inBuffer->reset(recipientNameLen);
    char *recepientName = inBuffer->getCstringPtr();
    int imgWidth = user->GetSocket()->recvInt();
    int imgHeight = user->GetSocket()->recvInt();
    //find recipient
    pthread_mutex_lock(&mutex_users);
    string recipientStr(recepientName);
    mapusers::iterator it = users.find(recipientStr);
    if (it == users.end())
        throw NoSuchUserException();
    User *recipient = it->second;
    pthread_mutex_unlock(&mutex_users);
    pthread_mutex_lock(recipient->GetRefMutex_socket());
    //prepare info message for recipient
    outBuffer->reset();
    outBuffer->putByte(USER_PASS_MSG);
    outBuffer->putByte(USER_PASS_MSG_INFO);
    outBuffer->putInt(user->GetName()->length() + 1); //+1 for null \0
    outBuffer->putCstring(user->GetName()->c_str());
    outBuffer->putInt(imgWidth);
    outBuffer->putInt(imgHeight);
    recipient->GetSocket()->sendChunk(outBuffer->GetBuffer(), outBuffer->GetPosition());
    do {
        char type = user->GetSocket()->recvByte();
        subtype = user->GetSocket()->recvByte();
        if (type != SERV_PASS_MSG || (subtype != SERV_PASS_MSG_PART && subtype != SERV_PASS_MSG_ALL))
            throw WrongMessageTypeException();
        int msgLen = user->GetSocket()->recvInt();
        user->GetSocket()->recvChunk(inBuffer->GetBuffer(), msgLen);
        outBuffer->reset();
        outBuffer->putByte(USER_PASS_MSG);
        if (subtype == SERV_PASS_MSG_PART)
            outBuffer->putByte(USER_PASS_MSG_PART);
        else
            outBuffer->putByte(USER_PASS_MSG_ALL);
        outBuffer->putInt(msgLen);
        recipient->GetSocket()->sendChunk(outBuffer->GetBuffer(), outBuffer->GetPosition());
        recipient->GetSocket()->sendChunk(inBuffer->GetBuffer(), msgLen);
    } while (subtype != SERV_PASS_MSG_ALL);
    pthread_mutex_unlock(recipient->GetRefMutex_socket());
}

void free_resources(User * user) {
    if (user->IsUser_added()) {
        delete_user(user);
        std::cout << "User " << *user->GetName() << " deleted" << std::endl;
    }
    pthread_exit(NULL);
}



