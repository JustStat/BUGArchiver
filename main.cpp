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
    if(input_data->type=="c")
    {
        outf << "UPAHUFF"<< (Byte)0 << (Byte)0 <<(Byte)10 << "output.bug";
        for(int i=0; i<8; i++)
            outf << (Byte)0;

    }
    /*res.push_back('P');
    res.push_back('A');
    if(input_data->alg=="h")
    {
        res.push_back('H');
        res.push_back('A');
        res.push_back('F');
        res.push_back('F');
    }else
    {
        res.push_back('N');
        res.push_back('O');
        res.push_back('P');
        res.push_back('E');
    }
    res.push_back('0');//is_solid*/
    for(int i=0; i<buffer.size(); i++)
    {
        outf << buffer[i];
    }
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
    if(buffer.size()==0)
    {
        cout <<"\nError. One or more files are missing in directory";
        return 0;
    }
    vector<Byte> result;
    if(input_data->alg=="n")
        {
            if(input_data->type=="c")
        {
            nope(buffer, result);
            vector<Byte> temp = adder_header(buffer, input_data);
            result.insert(result.begin(), temp.begin(), temp.end());
        }
        else
        {
            separator(buffer, input_data);
            nope(buffer, result);
        }
        }
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
            de_compress1(buffer, result,input_data->input_int_len);
        }
    }
    output_file(result,input_data);

    return 0;
}
