/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include <exception>
#include <new>
#include <iostream>
#include "data_conversion.h"

int array_to_int(char* bytes) {
    int n = 0;
    n |= ((0xFF & bytes[3]));
    n |= ((0xFF & bytes[2]) << 8);
    n |= ((0xFF & bytes[1]) << 16);
    n |= ((0xFF & bytes[0]) << 24);
    return n;
}

char *int_to_bytes(int n, char *bytes) {
    bytes[0] = (n >> 24) & 0xFF;
    bytes[1] = (n >> 16) & 0xFF;
    bytes[2] = (n >> 8) & 0xFF;
    bytes[3] = n & 0xFF;    
    return bytes;
}

char *alloc_int_to_bytes(int n) {
    try {
        char *bytes = new char[sizeof (n)];
        int_to_bytes(n, bytes);
        return bytes;
    } catch (std::bad_alloc& ba) {
        std::cerr << "bad_alloc caught: " << ba.what() << '\n';
        return NULL;
    }
}