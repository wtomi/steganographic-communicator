/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Socket.h
 * Author: tommy
 *
 * Created on February 16, 2017, 6:51 PM
 */

#ifndef SOCKET_H
#define SOCKET_H

#include <exception>
#include <pthread.h>

class Socket {
public:
    Socket(int sck);
    Socket(const Socket& orig);
    virtual ~Socket();

    char recvByte();
    int recvInt();
    int recvChunk(char *buf, int size);
    int sendChunk(char *buf, int size);
    pthread_mutex_t *getMutex();

    class TooShortMsgException : public std::exception {
    public:

        const char* what() const throw () {
            return "To short message";
        }
    };

private:
    int sck;
    pthread_mutex_t mutex;
};

#endif /* SOCKET_H */

