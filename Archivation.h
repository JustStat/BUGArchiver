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

vector<Byte> compress(vector<Byte> input);
vector<Byte> de_compress(vector<Byte> input);











#endif
