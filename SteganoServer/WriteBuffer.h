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
    WriteBuffer(int capacity);
    WriteBuffer(const WriteBuffer& orig);
    virtual ~WriteBuffer();
    
    void putInt(int n);
    void putByte(char byte);
    int putCstring(char *cString);
    void putChunk(char *chunk, unsigned int chunkSize);
private:
};

#endif /* WRITEBUFFOR_H */

