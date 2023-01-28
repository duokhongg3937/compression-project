#include "CommandHandler.h"

void LZWDecoding(vector<int> encoded_str)
{
	int n, code = 256;
	int old = encoded_str[0];
	unordered_map<int, string> table;
	string c = "", s;


	cout << "DECODING...\n";

	for (int i = 0; i < 256; i++)
	{
		string tmp = "";
		char x = char(i);
		tmp += x;
		table[i] = tmp;
	}

	s = table[old];
	c += s[0];
	cout << s;

	for (int i = 0; i < encoded_str.size() - 1; i++)
	{
		n = encoded_str[i + 1];
		if (table.find(n) == table.end())
		{
			s = table[old];
			s += c;
		}
		else
		{
			s = table[n];
		}
		cout << s;
		c = "";
		c += s[0];
		table[code] = table[old] + c;
		++code;
		old = n;
	}
	cout << endl;
	
}