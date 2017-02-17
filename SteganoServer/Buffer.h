/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Buffor.h
 * Author: tommy
 *
 * Created on February 16, 2017, 12:56 AM
 */

#ifndef BUFFOR_H
#define BUFFOR_H

#include <exception>

class Buffer {
public:
    Buffer(unsigned int capacity);
    Buffer(const Buffer& orig);
    virtual ~Buffer();
    unsigned int GetCapacity() const;
    void SetLimit(unsigned int limit);
    unsigned int GetLimit() const;
    void SetPosition(unsigned int position);
    unsigned int GetPosition() const;
    char* GetBuffer() const;
    unsigned int lastOperationLen();
    void reset();
    void reset(unsigned int len);
    unsigned int remaining();

    class BufferOverflowException : public std::exception {
    public:

        const char* what() const throw () {
            return "Buffor overflow exception";
        }
    };
protected:
    char* const buffer;
    unsigned int position;
    unsigned int limit;
    unsigned int capacity;
    unsigned int previousPosition;
private:

};

#endif /* BUFFOR_H */

