#pragma once
#ifndef SCANNER_H
#define SCANNER_H

#include <iostream>
#include <string>
#include <fstream>
#include "scanner.h"
#include <vector>
#include <sstream>
#include <iterator>

class Scanner
{
	void Reader(std::string fileName);
	void CmdProcessor();
};

#endif //SCANNER_H