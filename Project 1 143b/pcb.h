#pragma once
#ifndef PCB_H
#define PCB_H
#include <vector>
#include <list>
#include "status.h"
#include "readylist.h"

struct PCB
{
	int pID;
	std::list<RCB> otherResources;
	pStatus status;
	std::list<std::shared_ptr<PCB>> readyList;

	bool operator==(const PCB &p) const;
};

#endif //PCB_H