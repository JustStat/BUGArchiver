//
//  main.cpp
//  BUGArchive
//
//  Created on 13.07.15.
//  Copyright (c) 2015 Buggers. All rights reserved.
//

#include <iostream>
#include <cstdio>
#include "input.h"
#include "Archivation.h"

using namespace std;

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
    vector<byte> buffer;
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
    cout << buffer.size();
    for(int i=0; i<buffer.size(); i++)
    {
        cout << buffer[i] << " ";
    }
    return 0;
}
