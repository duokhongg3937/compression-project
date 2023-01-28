#include "CommandHandler.h"
#include "LZW.h"

// encode a message from string to vector of symbols
vector<int> LZWEncoding(string msg, int& max_len, vector<pair<string, int>>& dict)
{
	int code = 256;
	string p = "", c = "";
	vector<int> output_code;
	unordered_map<string, int> table;

	// initialize available code from 0 -> 255
	for (int i = 0; i < 256; i++)
	{
		string s = "";
		s += char(i);
		table[s] = i;
	}

	p += msg[0];

	for (int i = 0; i < msg.size(); i++)
	{
		// if not the last char
		if (i != msg.size() - 1)
		{
			c += msg[i + 1];
		}

		// if dictionary contains 'p + c'
		if (table.find(p + c) != table.end())
		{
			p += c;
		}
		else   // if not
		{
			dict.push_back({ p + c, code });
			output_code.push_back(table[p]);
			table[p + c] = code;
			++code;
			p = c;
		}

		c = "";
	}
	output_code.push_back(table[p]);

	// store max length of a symbol in bit
	max_len = log(code) / log(2) + 1;

	return output_code;
}

// convert from a decimal into it's binary form string
string DecToBin(int code, int max_len)
{
	string bin_code = "";

	while (code > 0)
	{
		bin_code += to_string(code % 2);
		code /= 2;
	}

	reverse(begin(bin_code), end(bin_code));

	while (bin_code.length() < max_len)
	{
		bin_code = "0" + bin_code;
	}

	return bin_code;
}

// convert a vector of symbol into a binary string
string toBinaryEncodedMsg(vector<int> encoded_msg, int max_len)
{
	string res = "";

	for (auto x : encoded_msg)
	{
		res += DecToBin(x, max_len);
	}

	int add_bits = 0;

	if (res.size() % 8 != 0)
	{
		add_bits = 8 - res.size() % 8;
	}

	// add bits in case the converted code not enough 'max_len' bits
	for (int i = 0; i < add_bits; i++)
	{
		res += "0";
	}

	return res;
}

// write message in it's binary form to output file
void writeToFile(COMMAND cmd, string bin_msg, int max_len, int& output_size)
{
	ofstream file_out;
	file_out.open(cmd.output_path, ios::out | ios::binary);

	// convert max dictionary index to binary form
	string m = DecToBin(max_len, 8);
	bitset<8> header(m);
	file_out.write((char*)&header, 1);
	output_size = 8;

	// write binary encoded msg into file
	for (int i = 0; i < bin_msg.size(); i += 8)
	{
		bitset<8> symbol(bin_msg.substr(i, 8));
		file_out.write((char*)&symbol, 1);
		output_size += 8;
	}

	file_out.close();
}

