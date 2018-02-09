#pragma once
#ifndef RCB_H
#define RCB_H
#include <vector>
#include <list>
#include "pcb.h"
#include "status.h"

class RCB
{
public:
	RCB(int rID, int resources);
	int getRID();
	int getResources();
	void incrementResources(int incr);
	void decreaseResources(int decr);
	rStatus getStatus();
	void setStatus(rStatus status);
	std::list<PCB> getWaitingList();
private:
	int rID, resources;
	rStatus status;
	std::list<PCB> waitingList;
};

#endif //RCB_H