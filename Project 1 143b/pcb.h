#pragma once
#ifndef PCB_H
#define PCB_H
#include <vector>
#include "status.h"

struct PCB
{
	int pID;
	std::vector<int> otherResources;
	pStatus status = READY;
	//LinkedList<int> creationTree;
};
#endif //PCB_H