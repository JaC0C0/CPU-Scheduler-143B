#include "scanner.h"

//Reads files and places them in a vector to be further processed

void Scanner::Reader(std::string fileName)
{
	std::ifstream cmdfile(fileName);
	std::string cmdString;

	if (cmdfile.is_open())
	{
		while (cmdfile.peek() != EOF)
		{
			std::getline(cmdfile, cmdString);
			cmdVector.push_back(cmdString);
		}

	}
	else
	{
		std::cout << "Unable to open file." << std::endl;
	}
};

void Scanner::CmdProcessor()
{
	for (int i = 0; i < cmdVector.size(); i++)
	{
		std::string cmd = cmdVector[i];
		std::istringstream iss(cmd);
		std::vector<std::string> tokens(std::istream_iterator<std::string>{iss},
			std::istream_iterator<std::string>());
		int cmdType = tokens.size();

		switch (cmdType)	//Filler functions currently. Remind self to add functionality
		{
			case 1 : 
				if (tokens[0] == "init")
				{
					std::cout << "Init Called" << std::endl;
				}
				else if (tokens[0] == "to")
				{
					std::cout << "to called" << std::endl;
				}
				else
				{
					std::cout << "1 tokens, but not init or to, something fukd up" << std::endl;
				}
				break;
			case 2 :
				if (tokens[0] == "de")
				{
					std::cout << "cr called" << std::endl;
				}
				else
				{
					std::cout << "2 tokens, but not de, something fukd up" << std::endl;
				}
				break;
			case 3 :
				if (tokens[0] == "cr")
				{
					std::cout << "cr called" << std::endl;
					if (tokens[1].length != 1)
					{
						std::cout << "Error: Process name too long" << std::endl;
					}
				}
				else if (tokens[0] == "req")
				{
					std::cout << "req called" << std::endl;
				}
				else if (tokens[0] == "rel")
				{
					std::cout << "rel called" << std::endl;
				}
				else
				{
					std::cout << "3 tokens, but not cr,req,rel, something fukd up" << std::endl;
				}
				break;
		}
	}
};
