/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Socket.cpp
 * Author: tommy
 * 
 * Created on February 16, 2017, 6:51 PM
 */

#include "Socket.h"
#include "socket_headers.h"
#include "data_conversion.h"

Socket::Socket(int sck) {
    this->sck = sck;
    pthread_mutex_init(&mutex, NULL);
}

Socket::Socket(const Socket& orig) {
}

Socket::~Socket() {
    close(sck);
}

char Socket::recvByte() {
    pthread_mutex_lock(this->getMutex());
    char byte;
    int len = recv(sck, &byte, sizeof (byte), MSG_WAITALL);

    if (len == 0)
        throw SocketClosedException();
    else if (len < 0)
        throw SocketErrorException();
    pthread_mutex_unlock(this->getMutex());
    return byte;
}

int Socket::recvInt() {
    pthread_mutex_lock(this->getMutex());
    char bytes[sizeof (int)];
    int len = recv(sck, bytes, sizeof (int), MSG_WAITALL);

    if (len == 0)
        throw SocketClosedException();
    else if (len < 0)
        throw SocketErrorException();
    int n = array_to_int(bytes);
    pthread_mutex_unlock(this->getMutex());
    return n;
}

int Socket::recvChunk(char *buf, int size) {
    pthread_mutex_lock(this->getMutex());
    if (size <= 0)
        throw TooShortMsgException();

    int len = recv(sck, buf, size, MSG_WAITALL);

    if (len == 0)
        throw SocketClosedException();
    else if (len < 0)
        throw SocketErrorException();
    else if (len != size)
        perror("Impossible! Too short message received");
    pthread_mutex_unlock(this->getMutex());
    return len;
}

int Socket::sendChunk(char *buf, int size) {
    pthread_mutex_lock(this->getMutex());
    if (size <= 0)
        throw TooShortMsgException();

    int len = send(sck, buf, size, 0);

    if (len == 0)
        throw SocketClosedException();
    else if (len < 0)
        throw SocketErrorException();
    else if (len != size)
        perror("Impossible! Too short message sent");
    pthread_mutex_unlock(this->getMutex());
    return len;
}

pthread_mutex_t *Socket::getMutex() {
    return &mutex;
}