#pragma once
#ifndef RCB_H
#define RCB_H
#include <vector>
#include <list>
#include "pcb.h"
#include <memory>
#include <string>

struct RCB
{
	bool operator==(const RCB&r) const;
	RCB(int rID);

	std::string rID;
	//resources.first are original allocated resource count. resource.second is current resource count
	std::pair<const int, int> resources;
	std::shared_ptr<std::list<std::shared_ptr<PCB>>> waitingList;
};

#endif //RCB_H