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
#include <string.h>
#include "Buffer.h"

Buffer::Buffer(unsigned int capacity): buffer(new char[capacity]){
        this->capacity = capacity;
        this->reset();
}

Buffer::Buffer(const Buffer& orig): buffer(new char[orig.capacity]){
    memcpy(this->buffer, orig.buffer, orig.capacity);
    this->capacity = orig.capacity;
    this->position = orig.position;
    this->limit = orig.limit;
    this->previousPosition = orig.previousPosition;
}

Buffer::~Buffer() {
    delete[] buffer;
}

void Buffer::reset() {
    this->position = 0;
    this->previousPosition = 0;
    this->limit = this->capacity;
}

void Buffer::reset(unsigned int len) {
    if(len > this->capacity)
        throw BufferOverflowException();
    this->position = 0;
    this->previousPosition = 0;
    this->limit = len;
}

unsigned int Buffer::remaining() {
    return this->limit - this->position;
}

unsigned int Buffer::lastOperationLen() {
    return this->position - this->previousPosition;
}

unsigned int Buffer::GetCapacity() const {
    return capacity;
}

void Buffer::SetLimit(unsigned int limit) {
    this->limit = limit;
}

unsigned int Buffer::GetLimit() const {
    return limit;
}

void Buffer::SetPosition(unsigned int position) {
    this->position = position;
}

unsigned int Buffer::GetPosition() const {
    return position;
}

char* Buffer::GetBuffer() const {
    return buffer;
}

