#pragma once
#ifndef SCANNER_H
#define SCANNER_H

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <sstream>
#include <iterator>

class Scanner
{
public:
	void Reader(std::string fileName);
	void CmdProcessor();
};

#endif //SCANNER_H