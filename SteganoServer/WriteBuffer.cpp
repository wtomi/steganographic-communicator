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

WriteBuffer::WriteBuffer(unsigned int capacity) : Buffer(capacity) {
}

WriteBuffer::WriteBuffer(const WriteBuffer& orig) : Buffer(orig) {
}

WriteBuffer::~WriteBuffer() {
}

void WriteBuffer::putInt(int n) {
    if (this->remaining() < sizeof (n))
        throw BufferOverflowException();
    int_to_bytes(n, this->buffer + this->position);
    this->previousPosition = this->position;
    this->position += sizeof (n);
}

unsigned int WriteBuffer::shiftPosition(unsigned int n) {
    if (this->remaining() < n)
        throw BufferOverflowException();
    this->previousPosition = this->position;
    this->position += n;
    return this->previousPosition;
}

void WriteBuffer::overrideByte(char byte, unsigned int position) {
    if (this->limit - position < 1)
        throw BufferOverflowException();
    this->buffer[position] = byte;
}

void WriteBuffer::overrideInt(int n,unsigned int position) {
    if ((this->limit - position) < sizeof(int))
        throw BufferOverflowException(); 
    int_to_bytes(n, this->buffer + position);
}

void WriteBuffer::putByte(char byte) {
    if (this->remaining() < sizeof (byte))
        throw BufferOverflowException();
    this->buffer[this->position] = byte;
    this->previousPosition = this->position;
    this->position++;
}

unsigned int WriteBuffer::putCstring(const char *cString) {
    unsigned int len = strlen(cString) + 1;
    if (len > this->remaining())
        throw BufferOverflowException();
    strcpy(this->buffer + this->position, cString);
    this->previousPosition = this->position;
    this->position += len;
    return len;
}

void WriteBuffer::putChunk(char *chunk, unsigned int chunkSize) {
    if (chunkSize > this->remaining())
        throw BufferOverflowException();
    memcpy(this->buffer + this->position, chunk, chunkSize);
    this->previousPosition = this->position;
    position += chunkSize;
}
