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
}

Socket::Socket(const Socket& orig) {
}

Socket::~Socket() {
    close(sck);
}

char Socket::recvByte() {
    char byte;
    int len = recv(sck, &byte, sizeof (byte), MSG_WAITALL);

    if (len == 0)
        throw SocketClosedException();
    else if (len < 0)
        throw SocketErrorException();
    return byte;
}

int Socket::recvInt() {
    char bytes[sizeof (int)];
    int len = recv(sck, bytes, sizeof (int), MSG_WAITALL);

    if (len == 0)
        throw SocketClosedException();
    else if (len < 0)
        throw SocketErrorException();
    int n = array_to_int(bytes);
    return n;
}

int Socket::recvChunk(char *buf, int size) {
    if (size <= 0)
        throw TooShortMsgException();

    int len = recv(sck, buf, size, MSG_WAITALL);

    if (len == 0)
        throw SocketClosedException();
    else if (len < 0)
        throw SocketErrorException();
    else if (len != size)
        perror("Impossible! Too short message received");
    return len;
}

int Socket::sendChunk(char *buf, int size) {
    if (size <= 0)
        throw TooShortMsgException();

    int len = send(sck, buf, size, 0);

    if (len == 0)
        throw SocketClosedException();
    else if (len < 0)
        throw SocketErrorException();
    else if (len != size)
        perror("Impossible! Too short message sent");
    return len;
}