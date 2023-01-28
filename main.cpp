#include "CommandHandler.h"

int main(int argc, char* argv[])
{
	vector<string> arguments(5, "");
	vector<int> encoded_message;
	for (int i = 0; i < argc; i++)
	{
		arguments[i] = argv[i];
	}

	COMMAND cmd = getUserCommand(arguments);

	handleCommand(cmd);

	system("pause");
	return 0;
}




