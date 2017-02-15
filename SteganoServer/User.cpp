/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   User.cpp
 * Author: tommy
 * 
 * Created on February 15, 2017, 6:14 PM
 */

#include "User.h"

User::User(int socket) {
    this->name = NULL;
    this->socket = socket;
    this->user_added = false;
    pthread_mutex_init(&this->mutex_socket, NULL);
}

User::User(const User& orig) {
}

User::~User() {
}

int User::GetSocket() const {
    return socket;
}

string *User::GetName() const {
    return name;
}

void User::SetMutex_socket(pthread_mutex_t mutex_socket) {
    this->mutex_socket = mutex_socket;
}

void User::SetName(string *name) {
    this->name = name;
}

void User::SetUser_added(bool user_added) {
    this->user_added = user_added;
}

bool User::IsUser_added() const {
    return user_added;
}

pthread_mutex_t *User::GetRefMutex_socket() {
    return &mutex_socket;
}

