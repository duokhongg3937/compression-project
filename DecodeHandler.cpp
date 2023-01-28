#include "CommandHandler.h"
#include "LZW.h"

// decode a vector of symbols into a string of data
string LZWDecoding(vector<int> encoded_msg, vector<pair<string, int>>& dict)
{
	int n, code = 256;
	int old = encoded_msg[0];
	unordered_map<int, string> table;
	string c = "", res = "", s;

	// initialize available code from 0 -> 255
	for (int i = 0; i < 256; i++)
	{
		string tmp = "";
		char x = char(i);
		tmp += x;
		table[i] = tmp;
	}

	s = table[old];
	c += s[0];
	res += s;

	for (int i = 0; i < encoded_msg.size() - 1; i++)
	{
		n = encoded_msg[i + 1];
		
		// if dictionary doesn't contain 'n'
		if (table.find(n) == table.end())
		{
			s = table[old];
			s += c;
		}
		else   // if contains
		{
			s = table[n];
		}

		res += s;
		c = s[0];
		table[code] = table[old] + c;
		dict.push_back({ table[code], code });
		++code;
		old = n;
	}

	return res;
}

// convert from a binary string into a decimal number
int BinToDec(string s)
{
	int res = 0, base = 1, len = s.size();

	for (int i = len - 1; i >= 0; i--)
	{
		if (s[i] == '1')
		{
			res += base;
		}
		base *= 2;
	}

	return res;
}

// convert from a binary message into a array of numbers
vector<int> toIntArray(string bin_msg, int bps)
{
	vector<int> res;

	int i = 0;
	while (bin_msg.size() - i >= bps)
	{
		int x = BinToDec(bin_msg.substr(i, bps));
		res.push_back(x);
		i += bps;
	}

	return res;
}

// read binary string from encoded file and get the number of bits per symbol 
void readFromFile(COMMAND cmd, string& bin_msg, int& bps, int& input_size)
{
	ifstream file_in;
	file_in.open(cmd.input_path, ios::in | ios::binary);

	if (!file_in.is_open())
	{
		cout << "ERROR: Cannot open '" << cmd.input_path << "' to read\n";
	}
	else
	{
		// read header to identify max bit size of a symbol
		bitset<8> byte;
		file_in.read((char*)&byte, 1);
		bps = BinToDec(byte.to_string());
		input_size = 8;

		// get all bit data into string 'msg'
		while (file_in.read((char*)&byte, 1))
		{
			bin_msg += byte.to_string();
			input_size += 8;
		}
	}
}