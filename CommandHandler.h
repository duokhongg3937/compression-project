#pragma once
#ifndef _COMMAND_HANDLER_H_

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <bitset>
#include <iomanip>
#include <cmath>
#include <unordered_map>

using namespace std;

struct COMMAND {
	int action;  // 0 if '-e' and 1 if '-d'
	string input_path;
	string output_path;
	int output_info;  // 0 if '-i', 1 if '-d' and 2 if '-ind'
};


COMMAND getUserCommand(vector<string> arguments);

void handleCommand(COMMAND cmd);

#endif // !_COMMAND_HANDLER_H_
