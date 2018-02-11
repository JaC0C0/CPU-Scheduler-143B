#pragma once
#ifndef RCB_H
#define RCB_H
#include <vector>
#include <list>
#include "pcb.h"
#include <memory>

struct RCB
{
	bool operator==(const RCB&r) const;

	int rID;
	std::pair<int, int> resources;
	std::shared_ptr<std::list<std::shared_ptr<PCB>>> waitingList;
};

#endif //RCB_H