/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   WriteBuffor.h
 * Author: tommy
 *
 * Created on February 16, 2017, 12:56 AM
 */

#ifndef WRITEBUFFOR_H
#define WRITEBUFFOR_H

#include "Buffer.h"

class WriteBuffer: public Buffer{
public:
    WriteBuffer(unsigned int capacity);
    WriteBuffer(const WriteBuffer& orig);
    virtual ~WriteBuffer();
    
    void putInt(int n);
    unsigned int shiftPosition(unsigned int n);
    void overrideInt(int n, unsigned int position);
    void overrideByte(char byte, unsigned int position);
    void putByte(char byte);
    unsigned int putCstring(const char *cString);
    void putChunk(char *chunk, unsigned int chunkSize);
private:
};

#endif /* WRITEBUFFOR_H */

