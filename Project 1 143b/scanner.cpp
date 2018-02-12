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

void Scanner::CmdProcessor(std::shared_ptr<OperatingSystem> os)
{
	std::ofstream textoutput("32422520.txt");
	os->processState(textoutput);
	for (size_t i = 0; i < cmdVector.size(); i++)
	{
		if (!textoutput.is_open())
		{
			std::cout << "Error: Unable to open file for writing" << std::endl;
			return;
		}
		this->terminate = false;
		std::string cmd = cmdVector[i];
		//Code utilized from https://stackoverflow.com/questions/236129/the-most-elegant-way-to-iterate-the-words-of-a-string
		std::istringstream iss(cmd);
		std::vector<std::string> tokens(std::istream_iterator<std::string>{iss},
			std::istream_iterator<std::string>());
		int cmdType = tokens.size();

		switch (cmdType)	//Filler functions currently. Remind self to add functionality
		{
			case 1 : 
				if (tokens[0] == "init")
				{
					os->initOS();
					std::cout << "init" << std::endl;
					textoutput << std::endl;
				}
				else if (tokens[0] == "to")
				{
					os->timeOut();
				}
				else
				{
					std::cout << "Error 1: Unrecognized Command" << std::endl;
				}
				break;
			case 2 :
				if (tokens[0] == "de")
				{
					std::shared_ptr<PCB> pcb = os->returnProcess(tokens[1]);
					if (pcb == nullptr || tokens[1] == "init")
					{
						std::cout << "Error 2: Invalid operation on process" << std::endl;
						textoutput << "error ";
					}
					else
					{
						os->killProcess(pcb);
					}
				}
				else
				{
					std::cout << "Error 2: Unrecognized Command" << std::endl;
					textoutput << "error ";
				}
				break;
			case 3 :
				if (tokens[0] == "cr")
				{
					if (tokens[1].size() != 1 || !this->is_number(tokens[2]) || os->returnProcess(tokens[1]) != nullptr ||
						std::stoi(tokens[2]) > 2 || std::stoi(tokens[2]) < 0)
					{
						std::cout << "Error 3: Invalid Process Command" << std::endl;
						textoutput << "error ";
					}
					else
					{
						os->create(tokens[1], std::stoi(tokens[2]), 0);
					}
				}
				else if (tokens[0] == "req")
				{
					if (is_number(tokens[2]))
					{
						os->request(tokens[1], std::stoi(tokens[2]), os->getRunning());
					}
					else
					{
						std::cout << "Error 3: Invalid Resource Request" << std::endl;
						textoutput << "error ";
					}
				}
				else if (tokens[0] == "rel")
				{
					std::vector<std::string> resourceArray = { "R1", "R2", "R3", "R4" };
					if (is_number(tokens[2]) && std::find(resourceArray.begin(), resourceArray.end(), tokens[1]) != resourceArray.end() || std::stoi(tokens[2]) > tokens[1][1])
					{
						os->release(tokens[1], std::stoi(tokens[2]));
					}
					else
					{
						std::cout << "Error 3: Invalid Resource Request" << std::endl;
						textoutput << "error ";
					}
				}
				else
				{
					std::cout << "Error 3: Invalid Command" << std::endl;
					textoutput << "error ";
				}
				break;
		}
		os->processState(textoutput);
	}
	textoutput.close();
};

//Function definition comes from https://stackoverflow.com/questions/4654636/how-to-determine-if-a-string-is-a-number-with-c
bool Scanner::is_number(const std::string& s)
{
	return !s.empty() && std::find_if(s.begin(),
		s.end(), [](char c) { return !std::isdigit(c); }) == s.end();
}