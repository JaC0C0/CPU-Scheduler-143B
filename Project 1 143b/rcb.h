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
	//NOT NEEDED? PROBABLY DONE IN SCHEDULER
	RCB(int rID, int resources);
	////Requests resource from respective ID. Returns boolean for QoL.
	//bool Request(int rID);
	////Release process and respective resources with ID
	//void Release(int rID);
private:
	int rID, resources;
	//rStatus status; Not sure if i need this?
	rStatus status;
	std::list<PCB> waitingList;
};

#endif //RCB_H