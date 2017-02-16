/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Buffer.cpp
 * Author: tommy
 * 
 * Created on February 15, 2017, 8:04 PM
 */

#include <new>
#include <iostream>
#include <cstring>
#include <string.h>
#include "ReadBuffer.h"
#include "data_conversion.h"
#include "Buffer.h"
#include "socket_headers.h"

ReadBuffer::ReadBuffer(int capacity): Buffer(capacity) {
    
}

ReadBuffer::ReadBuffer(const ReadBuffer& orig): Buffer(orig) {
    
}

ReadBuffer::~ReadBuffer(){
    delete[] buffer;
}

char ReadBuffer::getByte() {
    if(this->remaining() < sizeof(char))
        throw BufferOverflowException();
    char byte = this->buffer[this->position-1];
    this->position++;
    return  byte;
}

int ReadBuffer::getInt() {
    if(this->remaining() < sizeof(int))
        throw BufferOverflowException();
    int n = array_to_int(buffer + position - 1);    
    this->position += sizeof(int);
    return n;
}

char* ReadBuffer::getChunkPtr(unsigned int size){
    if(size > this->remaining())
        throw BufferOverflowException();
    char *chunkStart = this->buffer + this->position;
    this->position += size;
    return chunkStart;
}

char *ReadBuffer::getCstringPtr() {
    unsigned int rem = this->remaining();
    if(rem <= 0)
        throw BufferOverflowException();
    char *cStrngPointer = this->buffer + this->position;
    unsigned int len = strlen(cStrngPointer);
    if(len > rem)
        throw BufferOverflowException();
    position += len;   
    return cStrngPointer;
}




