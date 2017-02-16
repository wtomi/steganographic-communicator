/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Buffor.cpp
 * Author: tommy
 * 
 * Created on February 16, 2017, 12:56 AM
 */
#include <exception>
#include <new>
#include <iostream>
#include "Buffer.h"

Buffer::Buffer(int capacity) {
    try {
        buffer = new char[capacity];
        this->capacity = capacity;
        this->reset();
    } catch (std::bad_alloc& ba) {
        std::cerr << "bad_alloc caught: " << ba.what() << '\n';
    }
}

Buffer::Buffer(const Buffer& orig) {
}

Buffer::~Buffer() {
    delete[] buffer;
}

void Buffer::reset() {
    this->position = 0;
    this->limit = this->capacity;
}

void Buffer::reset(int len) {
    if(len > this->capacity)
        throw BufferOverflowException();
    this->position = 0;
    this->limit = len;
}

unsigned int Buffer::remaining() {
    return this->limit - this->position;
}

int Buffer::GetCapacity() const {
    return capacity;
}

void Buffer::SetLimit(int limit) {
    this->limit = limit;
}

int Buffer::GetLimit() const {
    return limit;
}

void Buffer::SetPosition(int position) {
    this->position = position;
}

int Buffer::GetPosition() const {
    return position;
}

char* Buffer::GetBuffor() const {
    return buffer;
}

