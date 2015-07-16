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

void output_file(vector<Byte> buffer, data* input_data) // ����� ����� ������ � �����������, �� ��� ������� ���������� �������� ���������� input� ������� ���� �� ����
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
    input_data->fcount = 0;
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
    //    nope(buffer, result);
    cout << buffer.size();
    if(input_data->type=="c")
        compress(buffer, result);
  //  else
//        de_compress1(buffer, result, 0);
    output_file(result,input_data);

    return 0;
}
