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

bool comress(vector<Byte> in_buff, int in_buff_len, vector<Byte> &out_buff, int* out_buff_len);
bool de_comress(vector<Byte> in_buff, vector<Byte> &out_buff, int buff_len);
bool nope(vector<Byte> in_buff, vector<Byte> &out_buff);










#endif
