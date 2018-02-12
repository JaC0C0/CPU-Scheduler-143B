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
	scanner.Reader("test.txt");
	while (!os.checkTermination())
	{
		scanner.CmdProcessor(std::make_shared<OperatingSystem>(os));
		os.processState();
	}
	return 0;
}

