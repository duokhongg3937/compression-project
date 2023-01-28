#pragma once
#ifndef _LZW_H_

#include "CommandHandler.h"

vector<int> LZWEncoding(string s, int& max_index, vector<pair<string, int>>& dict);

string LZWDecoding(vector<int> encoded_str, vector<pair<string, int>>& dict);

string DecToBin(int code, int code_size);

string toBinaryEncodedMsg(vector<int> encoded_msg, int max_index);

vector<int> toIntArray(string msg, int bps);

int BinToDec(string s);

void writeToFile(COMMAND cmd, string msg, int max_index, int& output_size);

void readFromFile(COMMAND cmd, string& msg, int& bps, int& input_size);

#endif // !_LZW_H_
