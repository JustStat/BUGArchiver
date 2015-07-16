#include <fstream>
#include <iostream>
#include <math.h>
#include <string>
#include "input.h"
#include "anyoption.h"
#define HUFF "HUFF"
#define UPA "UPA"

using namespace std;

void using_any_option(int argc, char* argv[], data* input_data)
{
    AnyOption *opt = new AnyOption();
    opt->addUsage( "" );
    opt->addUsage( "HELP" );
    opt->addUsage( "" );
    opt->addUsage( " -h     --help          Help " );
    opt->addUsage( " -i     --input         Name of input file " );
    opt->addUsage( " -o     --output        Name of output file " );
    opt->addUsage( " -a    --algorithm      Type of algorithm n or h (nope or huffman)" );
    opt->addUsage( " -t     --type          Type of operation c or d (compress or decompress)" );
    opt->addUsage( "" );

    opt->setFlag(  "help", 'h' );
    opt->setOption(  "input", 'i' );
    opt->setOption(  "output", 'o' );
    opt->setOption(  "type", 't' );
    opt->processCommandArgs( argc, argv );

    if( opt->getFlag( "help" ) || opt->getFlag( 'h' ) )
    {
        opt->printUsage();
    }
    if( opt->getValue( 'i' ) != NULL  || opt->getValue( "input" ) != NULL  )
    {
        input_data->input.push_back(opt->getValue('i'));
        input_data->fcount++;
    }
    if( opt->getValue( 'o' ) != NULL  || opt->getValue( "output" ) != NULL  )
    {
        input_data->output=opt->getValue('o');
    }else
    {
        input_data->output="output.bug";
    }
    if( opt->getValue( 'a' ) != NULL  || opt->getValue( "algorithm" ) != NULL  )
    {
        input_data->alg=opt->getValue('a');
    }else
    {
        input_data->alg="h";
    }
    if( opt->getValue( 't' ) != NULL  || opt->getValue( "type" ) != NULL  )
    {
        input_data->type=opt->getValue('t');
    }else
    {
        input_data->type="c";
    }
    for( int i = 0 ; i < opt->getArgc() ; i++ )
    {
        cout << "wrong arg = " <<  opt->getArgv( i ) << ";";
    }
    delete opt;
}

bool reading(data* input_data, vector<Byte>& buffer) // возвращает true, если ошибка
{
    ifstream inf;
    for(int i=0; i<input_data->fcount; i++)
    {
        inf.open(input_data->input[i], ios::binary);
        if(!inf)
        return true;
        Byte temp;
        while(!inf.eof())
        {
            inf.read((char*)&temp,sizeof(temp));
            buffer.push_back(temp);
        }
        buffer.erase(buffer.end()-1);
    }
    return false;
}
vector<Byte> adder_header(vector<Byte>& buffer, data* input_data)
{
    vector<Byte> res;
    //v.insert(v.end(), v2.begin(), v2.end());
    res.push_back('U');
    res.push_back('P');
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
    res.push_back('0');//is_solid
    unsigned short int temp = input_data->fcount / 256;
    res.insert(res.begin(), input_data->fcount % 256);
    res.insert(res.begin(), temp);
    long long len=buffer.size();
    for(int i=0; i<8; i++)
    {
        res.insert(res.begin(), len % 256);
        len=len/256;
    }
    input_data->input_len=res;
    return res;
}
bool separator(vector<Byte>& buffer, data* input_data)
{
    //Byte huff[4]="HUFF";
    for(int i=0; i<3; i++)// сделать проверки
    {
        if(UPA[i]==buffer[0])
            buffer.erase(buffer.begin()+1);
        else
            return true;
    }
    for(int i=0; i<4; i++)// сделать проверки
    {
        if(HUFF[i]==buffer[0])
            buffer.erase(buffer.begin()+1);
        else
            return true;
    }
    long long a=0;
    for(int i=0; i<8; i++)
    {
        a=a+buffer[i]*pow(256,8-i-1);
    }
    input_data->input_int_len=a;
    for(int i=0;i<8; i++)
        buffer.erase(buffer.begin()+1);
    return false;
}

