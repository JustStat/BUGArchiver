#ifndef INPUT_H_INCLUDED
#define INPUT_H_INCLUDED
#include <vector>

typedef unsigned char byte;
using namespace std;
typedef struct data
{
        char* input;
        char* output;
        string type; // c or d
        bool have_input_file;
}data;

void using_any_option(int argc, char* argv[], data* input_data);
bool reading(data* input_data, vector<byte>& buffer);
#endif // INPUT_H_INCLUDED

