//
//  Archivation.h
//  BUGArchive
//
//  Created on 13.07.15.
//  Copyright (c) 2015 Buggers. All rights reserved.
//

#ifndef BUGArchive_Archivation_h
#define BUGArchive_Archivation_h

using namespace std;

typedef unsigned char Byte;

#include <vector>

bool compress(vector <Byte>& in_buf, vector <Byte>& out_buf);
bool de_compress(vector<Byte> in_buff, vector<Byte> &out_buff, int buff_len);
bool de_compress1(vector<Byte> in_buf, vector<Byte> &out_buf, long long buf_len);
bool nope(vector<Byte> in_buff, vector<Byte> &out_buff);
bool LZW_compress(vector <Byte>& in_buf, vector <Byte>& out_buf);
bool LZW_decompress(vector <Byte>& in_buf, vector <Byte>& out_buf);
int lz77_encode(char* input, char* output)
int lz77_decode(char* input, char* output)










#endif
