/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Buffer.h
 * Author: tommy
 *
 * Created on February 15, 2017, 8:04 PM
 */

#ifndef BUFFER_H
#define BUFFER_H

#include <exception>

#include "Buffer.h"

class ReadBuffer: public Buffer {
public:
    ReadBuffer(int capacity);
    ReadBuffer(const ReadBuffer& orig);
    virtual ~ReadBuffer();
    
    char getByte();
    int getInt();  
    char *getChunkPtr(unsigned int size);
    char *getCstringPtr();
private:
};

#endif /* BUFFER_H */

