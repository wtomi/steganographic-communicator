/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   client_loop.h
 * Author: tommy
 *
 * Created on February 15, 2017, 6:15 PM
 */

#ifndef CLIENT_LOOP_H
#define CLIENT_LOOP_H

#include <exception>

void *client_loop(void *arg);

class UnauthenticatedUserException : public std::exception {
public:

    const char* what() const throw () {
        return "Request from unauthenticated user";
    }
};

class TooBigMessageException: public std::exception {
    public:

    const char* what() const throw () {
        return "Size of the message is greater than buffor size";
    }
};

#endif /* CLIENT_LOOP_H */

