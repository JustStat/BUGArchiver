//
//  LZ77.cpp
//  BUGArchive
//
//  Created by Kirill Varlamov on 16.07.15.
//  Copyright (c) 2015 Kirill Varlamov. All rights reserved.
//

#include "Archivation.h"

#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <fstream>
#include <iostream>
#include <string.h>

#define LBSIZE 8
#define SBSIZE 1024

using namespace std;

struct Token {
    uint16_t offset:10;
    uint8_t next;
    uint8_t length:3;
} __attribute__((packed));


long long ReadBufToInt(int* &data, vector <Byte>& in_buf) {
    
    long long i = 0;
    size_t bufLen = in_buf.size();
    data = (int*) malloc(sizeof(int)*bufLen);
    for (int i; i < in_buf.size(); ++i) {
        data[i] = in_buf[i];
    }
    return i;
}

bool LZ77_compress(vector <Byte>& in_buf, vector <Byte>& out_buf) {
    int* data;
    long long fileSize = ReadBufToInt(data, in_buf);
    Token t = {0, 0, 0};
    int matchLen = 0;
    unsigned long matchPos = 0;
    int i = 0;
    int* searchBuffer = data;
    int*lookAheadBuffer = data;
    
    do {
        lookAheadBuffer += (matchLen + 1);
        i += (matchLen + 1);
        
        t.offset = matchPos; t.length = matchLen; t.next = *(lookAheadBuffer - 1);
        out_buf.push_back(t.offset);
        out_buf.push_back(t.length);
        out_buf.push_back(t.next);
        
        if(i >= SBSIZE) {
            searchBuffer += (matchLen + 1);
        } else {
            searchBuffer = data;
        }
        
        matchLen = matchPos = 0;
        
        for(int* p = lookAheadBuffer - 1; p >= searchBuffer; p--) {
            int j = 0;
            while (*(p + j) == *(lookAheadBuffer + j) && j < LBSIZE - 1)
                j++;
            
            if (j > matchLen) {
                matchLen = j;
                matchPos = lookAheadBuffer - p;
            }
        }
    } while (i < fileSize);
    return false;
}

bool LZ77_decompress(vector <Byte>& in_buf, vector <Byte>& out_buf) {
    size_t bufLen = SBSIZE * SBSIZE;
    int* buf = (int*) malloc(sizeof(int)*(bufLen));
    Token* t;
    size_t k = 0, len = 0;
    
    for (int i = 0; i < in_buf.size(); i=i+3) {
        
        t->offset = in_buf[i];
        t->length = in_buf[i + 1];
        t->next = in_buf[i + 2];
        
        if((k + LBSIZE) >= bufLen) {
            bufLen = bufLen*2;
            buf = (int*) realloc(buf, sizeof(int)*bufLen);
        }
        
        for(i = 0; i < len; i++) {
            
            if((t + i)->offset == 0) {
                buf[k++] = (t+i)->next;
            } else {
                if(k - (t+i)->offset != k - 1) {
                    memcpy(buf + k, buf + k - (t+i)->offset, sizeof(int)*((t+i)->length+1));
                } else {
                    for(int j = 0; j < (t+i)->length; j++) {
                        *(buf + k + j) = *(buf + k - 1);
                    }
                }
                
                k += ((t+i)->length);
                buf[k++] = (t+i)->next;
                
            }
        }
    }
    for(int i = 0; i < k; i++) {
        out_buf[i] = buf[i];
    }
    return false;
}
