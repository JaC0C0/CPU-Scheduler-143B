#pragma once
#ifndef RCB_H
#define RCB_H
#include <vector>
#include <list>
#include "pcb.h"
#include <memory>

struct RCB
{
//public:
//	RCB(int rID, int resources);
//	int getRID();
//	int getResources();
//	void incrementResources(int incr);
//	void decreaseResources(int decr);
//	rStatus getStatus();
//	void setStatus(rStatus status);
//	std::shared_ptr<std::list<PCB>> getWaitingList();
//private:
	bool operator==(const RCB&r) const;

	int rID;
	std::pair<int, int> resources;
	std::shared_ptr<std::list<std::pair<int, std::shared_ptr<PCB>>>> waitingList;
};

#endif //RCB_H