#include "CommandHandler.h"
#include "LZW.h"

// get user command line arguments 
COMMAND getUserCommand(vector<string> arguments)
{
	COMMAND cmd;

	if (arguments[1].compare("-e") == 0)
	{
		cmd.action = 0;
	}
	else if (arguments[1].compare("-d") == 0)
	{
		cmd.action = 1;
	}
	else
	{
		cmd.action = -1;
	}

	cmd.input_path = arguments[2];
	cmd.output_path = arguments[3];
	
	if (arguments[4].compare("-i") == 0)
	{
		cmd.output_info = 0;
	}
	else if (arguments[4].compare("-d") == 0)
	{
		cmd.output_info = 1;
	}
	else if (arguments[4].compare("-ind") == 0)
	{
		cmd.output_info = 2;
	}
	else    // not all of cases above
	{
		cmd.output_info = -1;
	}

	return cmd;
}

// print input size, output size and the percent of space saved
void printFileSize(int input_size, int output_size, float space_saved)
{
	cout << "Input size: " << input_size << " bits\n";
	cout << "Output size: " << output_size << " bits\n";
	cout << "Space saved: " << fixed << setprecision(2) << space_saved << "%" << endl;
}

// print dictionary created from encoding process or decoding process 
void printDictionary(vector<pair<string, int>> dict)
{
	cout << "Dictionary created: \n";
	for (auto x : dict)
	{
		cout << x.first << " \t " << x.second << endl;
	}
}

// handle user command with those cases in project requests
void handleCommand(COMMAND cmd)
{
	ifstream file_in;
	ofstream file_out;
	vector<int> res;
	vector<pair<string, int>> dictionary;
	string msg;
	string decoded_msg;
	int bps = 8;   // number of bits per symbol in dictionary
	int max_index = 0;   // store the max index of dictionary
	int input_size = 0, output_size = 0;
	float space_saved = 0.0;


	switch (cmd.action)
	{
	case 0:
		file_in.open(cmd.input_path, ios_base::in);
		if (!file_in.is_open())
		{
			cout << "ERROR: Cannot open '" << cmd.input_path << "' to read\n";
			exit(0);
		}
		else
		{
			string s, t;
			while (getline(file_in, t))
			{
				s += t;
				s += '\n';
			}
			s = s.substr(0, s.size() - 1);
			input_size = s.size() * 8;
			res = LZWEncoding(s, max_index, dictionary);
			writeToFile(cmd, toBinaryEncodedMsg(res, max_index), max_index, output_size);
		}
		file_in.close();
		space_saved = 100.0 - 100.0 * output_size / input_size;
		break;

	case 1:
		readFromFile(cmd, msg, bps, input_size);
		res = toIntArray(msg, bps);
		decoded_msg = LZWDecoding(res, dictionary);

		file_out.open(cmd.output_path, ios_base::out);
		file_out << decoded_msg << endl;
		file_out.close();

		output_size = decoded_msg.size() * 8;
		space_saved = 100.0 - 100.0 * input_size / output_size;
		break;
	default:
		cout << "ERROR: User action is not available!\n";
		exit(0);
	}

	switch (cmd.output_info)
	{
	case 0:
		printFileSize(input_size, output_size, space_saved);
		break;

	case 1:
		printDictionary(dictionary);
		break;
	case 2:
		printFileSize(input_size, output_size, space_saved);
		printDictionary(dictionary);
		break;
	default:
		cout << "ERROR: User's output info is not available!\n";
		exit(0);
	}

}