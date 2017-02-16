/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   socket_headers.h
 * Author: tommy
 *
 * Created on February 15, 2017, 6:12 PM
 */

#ifndef SOCKET_HEADERS_H
#define SOCKET_HEADERS_H

#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <time.h>
#include <pthread.h>
#include <exception>

class SocketClosedException: public std::exception {
    const char* what() const throw() {
        return "Socked closed";
    }
};

class SocketErrorException: public std::exception {
    const char* what() const throw() {
        return "Socked eroor";
    }
};

#endif /* SOCKET_HEADERS_H */

