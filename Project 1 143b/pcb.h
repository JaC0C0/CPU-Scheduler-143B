#pragma once
#ifndef PCB_H
#define PCB_H
#include <vector>
#include <list>
#include "status.h"
#include "readylist.h"

struct PCB
{
	PCB(int pID, std::vector<int> otherResources, std::pair<pStatus, std::list<PCB>*> status);

	int pID;
	std::vector<int> otherResources;
	//ReadyList creationTree;
	std::pair<pStatus, std::list<PCB>*> status;

	bool operator==(const PCB &p) const;
};

#endif //PCB_H