#pragma once
#ifndef SCANNER_H
#define SCANNER_H

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <sstream>
#include <iterator>
#include <memory>
#include <algorithm>
#include <cctype>
#include "operatingSystem.h"

class Scanner
{
public:
	void Reader(std::string fileName);
	void CmdProcessor(std::shared_ptr<OperatingSystem> os);
	//Function definition comes from https://stackoverflow.com/questions/4654636/how-to-determine-if-a-string-is-a-number-with-c
	bool is_number(const std::string& s);
private:
	std::vector<std::string> cmdVector;
	bool terminate;
};

#endif //SCANNER_H