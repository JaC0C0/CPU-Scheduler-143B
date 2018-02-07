#pragma once
#ifndef PCB_H
#define PCB_H
#include <vector>
#include "status.h"
#include "readylist.h"

struct PCB
{
	PCB(int pID, std::vector<int> otherResources, std::pair<pStatus, ReadyList> status);

	int pID;
	std::vector<int> otherResources;
	ReadyList creationTree;
	std::pair<pStatus, ReadyList> status = std::make_pair(READY, creationTree);

	bool operator==(const PCB &p) const;
};

#endif //PCB_H