/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   data_conversion.h
 * Author: tommy
 *
 * Created on February 15, 2017, 7:20 PM
 */

#ifndef DATA_CONVERSION_H
#define DATA_CONVERSION_H

int array_to_int(char* bytes);
char *int_to_bytes(int n, char *bytes);
char *alloc_int_to_bytes(int n);

#endif /* DATA_CONVERSION_H */

