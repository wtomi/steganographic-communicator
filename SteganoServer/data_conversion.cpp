/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include <stdlib.h>
#include <stdio.h>

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
}

char *alloc_int_to_bytes(int n) {
    char *bytes = malloc(sizeof(n));
    if(bytes == NULL) {
        perror("ERROR in alloc_int_to_bytes()");
    }
    int_to_bytes(n, bytes);
    return bytes;
}