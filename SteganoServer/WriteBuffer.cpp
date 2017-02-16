/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   WriteBuffor.cpp
 * Author: tommy
 * 
 * Created on February 16, 2017, 12:56 AM
 */

#include "WriteBuffer.h"
#include "Buffer.h"
#include "data_conversion.h"
#include <cstring>

WriteBuffer::WriteBuffer(int capacity): Buffer(capacity){
}

WriteBuffer::WriteBuffer(const WriteBuffer& orig) :Buffer(orig){
}

WriteBuffer::~WriteBuffer() {
    delete[] buffer;
}

void WriteBuffer::putInt(int n) {
    if(this->remaining() < sizeof(n))
        throw BufferOverflowException();
    int_to_bytes(n, this->buffer + this->position);
    this->position += sizeof(n);
}

void WriteBuffer::putByte(char byte) {
    if(this->remaining() < sizeof(byte))
        throw BufferOverflowException();
    this->buffer[this->position] = byte;
    this->buffer++;
}

int WriteBuffer::putCstring(char *cString) {
    unsigned int len = strlen(cString);
    if(len > this->remaining())
        throw BufferOverflowException();
    strcpy(this->buffer + this->position, cString);
    this->position += len;
    return len;
}

void WriteBuffer::putChunk(char *chunk, unsigned int chunkSize) {
    if(chunkSize > this->remaining())
        throw BufferOverflowException();
    memcpy(this->buffer + this->position, chunk, chunkSize);
    position += chunkSize;
}
