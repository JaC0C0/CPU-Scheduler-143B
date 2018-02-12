// Project 1 143b.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "scanner.h"
#include "operatingSystem.h"
#include <iostream>

int main()
{
	Scanner scanner;
	OperatingSystem os;
	os.initOS();
	scanner.Reader("test.txt");
	scanner.CmdProcessor(std::make_shared<OperatingSystem>(os));
	return 0;
}

