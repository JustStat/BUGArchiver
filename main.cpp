//
//  main.cpp
//  BUGArchive
//
//  Created on 13.07.15.
//  Copyright (c) 2015 Buggers. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <cstdio>
#include "input.h"
#include "Archivation.h"

using namespace std;

void output_file(vector<Byte> buffer, data* input_data) // будет время вынесу в библитотеку, но это требует измениений названий библиотеки inputб поэтому пока не буду
{
    ofstream outf;
    outf.open(input_data->output, ios::binary);
    Byte* temp = new Byte[buffer.size()];
    for(int i=0; i<buffer.size(); i++)
    {
        temp[i] = buffer[i];
    }
    outf.write((char*)temp, sizeof(Byte) * buffer.size());
    delete temp;
}
int main(int argc, char* argv[])
{
    data* input_data = new data;
    input_data->fcount=0;
    using_any_option(argc, argv, input_data);
    if(input_data->type!="c" && input_data->type!="d")
    {
        cout <<"\nError. Wrong type of operation, use key -h";
        return 0;
    }
    int error;
    vector<Byte> buffer;
    if(input_data->fcount!=0)
        error = reading(input_data, buffer);
    else
    {
        cout <<"\nError. There is no file name.";
        return 0;
    }
    if(error)
    {
        cout <<"\nError. One or more files are missing in directory";
        return 0;
    }
    vector<Byte> result;
    if(input_data->alg=="n")
        nope(buffer, result);
    if(input_data->alg=="h")
    {
        if(input_data->type=="c")
        {
            compress(buffer, result);
            vector<Byte> temp = adder_header(buffer, input_data);
            result.insert(result.begin(), temp.begin(), temp.end());
        }
        else
        {
            separator(buffer, input_data);
            de_compress1(buffer, result,input_data->input_len);
        }
    }
    output_file(result,input_data);

    return 0;
}
