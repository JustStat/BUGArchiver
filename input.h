#ifndef INPUT_H_INCLUDED
#define INPUT_H_INCLUDED
#include <vector>

typedef unsigned char Byte;
using namespace std;
typedef struct data
{
        vector<char*> input;
        char* output;
        string type; // c or d
        int fcount;
        string alg;
        vector<Byte> input_len;
}data;

void using_any_option(int argc, char* argv[], data* input_data);
bool reading(data* input_data, vector<Byte>& buffer);
bool separator(vector<Byte>& buffer, data* input_data);
vector<Byte> adder_header(vector<Byte>& buffer, data* input_data);
#endif // INPUT_H_INCLUDED

