/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   User.h
 * Author: tommy
 *
 * Created on February 15, 2017, 6:14 PM
 */

#ifndef USER_H
#define USER_H

#include <string>
#include <pthread.h>
using namespace std;

class User {
public:
    User(int socket);
    User(const User& orig);
    virtual ~User();
    int GetSocket() const;
    string *GetName() const;
    void SetMutex_socket(pthread_mutex_t mutex_socket);
    void SetName(string *name);
    void SetUser_added(bool user_added);
    bool IsUser_added() const;
    pthread_mutex_t *GetRefMutex_socket();
private:
    string *name;
    int socket;
    pthread_mutex_t mutex_socket;
    bool user_added;
};

#endif /* USER_H */

