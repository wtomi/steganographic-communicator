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
    Buffer(int capacity);
    Buffer(const Buffer& orig);
    virtual ~Buffer();
    int GetCapacity() const;
    void SetLimit(int limit);
    int GetLimit() const;
    void SetPosition(int position);
    int GetPosition() const;
    char* GetBuffor() const;
    void reset();
    void reset(int len);
    unsigned int remaining();
protected:
    class BufferOverflowException: public std::exception {        
        const char* what() const throw() {
            return "Buffor overflow exception";
        }       
    };
    class ToBigMessageException: public std::exception {
        const char* what() const throw() {
            return "Too big message exception. "
                    "Message's length specfied "
                    "in message in the beggining "
                    "of the message is too long"
                    "for the buffer.";
        }
    };
    char *buffer;
    int position;
    int limit;
    int capacity;
private:

};

#endif /* BUFFOR_H */

