#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "Archivation.h"

#define SIGNATURE "BUGA"
using namespace std;
Byte* buf_a, buf_b;
vector<Byte> a, b;

struct Archive{
	char sign[3];
	char alg_sign;
	long long file_size;
	long long source_size;
	int name_len;
};

Archive make_archive(const char a_sign, long long file_size, long long source_size, int name_len){
	Archive t;
	t.sign[0] = 'B';
	t.sign[1] = 'U';
	t.sign[2] = 'G';
	t.alg_sign = a_sign;
	t.file_size = file_size;
	t.source_size = source_size;
	t.name_len = name_len;
	return t;
}

int get_name_len(const char name[]){
	int i = 0;
	while(name[i] != '\0')
		i++;
	return i;
}

char* make_name(const char a[]){
	int a_len = get_name_len(a);
	char* r = new char[a_len + 5];
	for (int i = 0; i < a_len; i++){
		r[i] = a[i];
	}
	r[a_len] = '.';
	r[a_len + 1] = 'b';
	r[a_len + 2] = 'u';
	r[a_len + 3] = 'g';
	r[a_len + 4] = '\0';
	return r;
}

void archivate(const char in_file[], const char res_file[], char alg){
	ifstream input(in_file, ifstream::binary);
	input.seekg(0, input.end);
	long long size = input.tellg();
	input.seekg(0, input.beg);
	for (int i = 0; i < size; i++){
		a.push_back(input.get());
	}
	input.close();
	switch (alg){
		case 'n':
			nope(a, b);
			break;
		case 'h':
			compress(a, b);
			break;
		case 'l':
			LZ77_compress(a, b);
			break;
		case 'w':
			LZW_compress(a, b);
			break;
	}
	cout << a.size() << endl;
	cout << b.size() << endl;
	char* r_file = make_name(res_file);
	Archive arch = make_archive(alg, b.size(), size, get_name_len(in_file));
	ofstream output(r_file, ofstream::binary);
	output.write((char*)&arch, sizeof(Archive));
	output.write(in_file, arch.name_len);
	for (int i = 0; i < b.size(); i++){
		output.put(b[i]);
	}
	output.close();
	delete r_file;
}

void dearchivate(const char in_file[]){
	Archive arch;
	ifstream input(in_file, ifstream::binary);
	input.read((char*)&arch, sizeof(arch));
	char* res_file = new char[arch.name_len + 1];
	input.read(res_file, arch.name_len);
	res_file[arch.name_len] = '\0';
	for (int i = 0; i < arch.file_size; i++){
		a.push_back(input.get());
	}
	input.close();
	switch (arch.alg_sign){
		case 'n':
			nope(a, b);
			break;
		case 'h':
			de_compress1(a, b, arch.source_size);
			break;
		case 'l':
			LZ77_decompress(a, b);
			break;
		case 'w':
			LZW_decompress(a, b);
			break;
	}
	ofstream output(res_file, ofstream::binary);
	for (int i = 0; i < b.size(); i++){
		output.put(b[i]);
	}
	output.close();
}

int main(int argc, char* argv[]){
	switch (argc){
		case 2:
			if (argv[1][1] == 'h'){
				cout << "BUGArchiver v 1.0" << endl;
				cout << "Argumets:" << endl;
				cout << "\t-[mode][algorythm_signature] [input_file] [archive_name]" << endl;
				cout << "\tmode: c(compress), d(decompress)" << endl;
				cout << "\talgorythms: n(none), h(huffman), l(LZ77)" << endl;
				cout << "\talgorythm_signature and archive_name need only in case compress mode" << endl;
			}
			else{
				cout << "ERROR: Bad arguments";
				return 1;
			}
			break;
		case 3:
			if (argv[1][1] != 'd'){
				cout << "ERROR: need result file";
				return 1;
			}
			dearchivate(argv[2]);
			break;
		case 4:
			if (argv[1][1] != 'c'){
				cout << "ERROR: Bad arguments" << endl;
				return 1; 
			}
			char alg;
			if (argv[1][2] == '\0'){
				alg = 'h';
			}
			else{
				alg = argv[1][2];
			}
			archivate(argv[2], argv[3], alg);
			break;
		default:
			cout << "ERROR: No arguments" << endl;
			return 1;
			break;
	}
	return 0;
}
