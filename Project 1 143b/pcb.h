#pragma once
#ifndef PCB_H
#define PCB_H
#include <vector>
#include <list>
#include "status.h"
#include "readylist.h"
#include <memory>

struct RCB;

struct PCB
{
	int pID, priority;
	std::list<std::shared_ptr<RCB>> otherResources;
	pStatus status;
	std::shared_ptr<std::list<std::shared_ptr<PCB>>> list;

	bool operator==(const PCB &p) const;
};

#endif //PCB_H