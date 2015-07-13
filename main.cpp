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
    //char* temp = new char[255];
    //temp = input_data->output + ".bag";
    outf.open(input_data->output, ios::binary);
    for(int i=0; i<buffer.size(); i++)
    {
        outf << buffer[i];
    }
}

int main(int argc, char* argv[])
{
    data* input_data = new data;
    using_any_option(argc, argv, input_data);
    if(input_data->type!="c" && input_data->type!="d")
    {
        cout <<"\nError. Wrong type of operation, use key -h";
        return 0;
    }
    int error;
    vector<Byte> buffer;
    if(input_data->have_input_file)
        error = reading(input_data, buffer);
    else
    {
        cout <<"\nError. There is no file name.";
        return 0;
    }
    if(error)
    {
        cout <<"\nError. No such file in directory";
        return 0;
    }

    vector<Byte> result;

    if(input_data->type=="c")
        result = compress(buffer);
//    else
//        result = de_compress(buffer);
    output_file(result,input_data);

    return 0;
}
