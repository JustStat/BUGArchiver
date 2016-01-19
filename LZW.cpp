#include "Archivation.h"
#include <iostream>
#include <map>
#include <set>
#include <string>
#define BIT_COUNT 12

using namespace std;

map <string, long long> dict;
vector <string> dict2;
set <string> set_dict;
vector <long long> prov;

Byte get_code_len(long long code){
	Byte count = 0;
	while (code > 0){
		code = code >> 1;
		count += 1;
	}
	return count;
}

bool LZW_compress(vector <Byte>& in_buf, vector <Byte>& out_buf){
	string current_word = "";
	for (int i = 0; i < 256; i++){
		current_word = "";
		current_word.push_back((char)i);
		dict[current_word] = i;
		set_dict.insert(current_word);
	}
	current_word = "";
	current_word.push_back(*(in_buf.begin()));
	long long current_code = 256;

	for (vector <Byte>::iterator i = in_buf.begin() + 1; i != in_buf.end(); i++){
		string next_word = current_word;
		next_word.push_back((char)*i);
		if (set_dict.find(next_word) == set_dict.end()){
			set_dict.insert(next_word);
			dict[next_word] = current_code;
			current_code++;
			long long code = dict[current_word];
			current_word = "";
			current_word.push_back((char)*i);
			prov.push_back(code); 	
		}
		else{
			current_word = next_word;
		}
	}
	prov.push_back(dict[current_word]);

	Byte code_len = get_code_len(current_code);
	out_buf.push_back(code_len);

	int c_bit = 0;
	Byte c_byte = 0;
	for (int i = 0; i < prov.size(); i++){
		// cout << prov[i] << " " << endl;
		long long code = prov[i];
		for (int j = 0; j < code_len; j++){
			if (code & (1 << j)){
				c_byte = c_byte | (1 << c_bit);
			}
			c_bit++;
			if (c_bit == 8){
				out_buf.push_back(c_byte);
				c_byte = 0;
				c_bit = 0;
			}
		}
	}
	if (c_bit != 0){
		out_buf.push_back(c_byte);
	}
	return true;
}


bool LZW_decompress(vector <Byte>& in_buf, vector <Byte>& out_buf){
	int code_len = in_buf[0];
	int c_bit = 0;
	long long code = 0;
	long long l_code = -1;
	string current_word = "";
	string last_word = "";
	for (int i = 0; i < 256; i++){
		current_word = "";
		current_word.push_back((char)i);
		dict2.push_back(current_word);
		set_dict.insert(current_word);
	}
	cout << in_buf.size() << endl;
	int k = 0;
	for (int i = 1; i + 1 < in_buf.size();){
		code = 0;
		for (int j = 0; j < code_len; j++){
			if ((in_buf[i]) & (1 << c_bit)){
				code  = code | (1 << j);
			}	
			c_bit++;
			if (c_bit == 8){
				i++;
				c_bit = 0;
			}
		}
		prov.push_back(code);
	}

	if (k == 10881){
		cout << prov[0] << endl;
	}
	last_word = dict2[*(prov.begin())];
	cout << "?" << endl;
	for (int i = 1; i < prov.size(); i++){
			if (dict2.size() == 306){
				cout << prov[i] << endl;
			}
		current_word = dict2[prov[i]];
			if (dict2.size() == 306){
				cout << 1 << endl;
			}
		// cout << last_word + current_word << endl;
		if (set_dict.find(last_word + current_word) == set_dict.end()){
			set_dict.insert(last_word + current_word);
			dict2.push_back(last_word + current_word);
			// cout << dict2.size() << endl;
			for (int j = 0; j < last_word.length(); j++){
				out_buf.push_back((Byte)last_word[j]);
			}
			last_word = current_word;
		}
		else{
			last_word += current_word;
		}
	}
	for (int i = 0; i < last_word.length(); i++){
		out_buf.push_back((Byte)last_word[i]);
	}
	return true;
}

