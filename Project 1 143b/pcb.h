#pragma once
#ifndef PCB_H
#define PCB_H
#include <vector>
#include <list>
#include "status.h"
#include "readylist.h"

struct PCB
{
	//PCB(int pID, std::list<RCB> otherResources, std::pair<pStatus, std::list<PCB>*> status)
	//{
	//	this->pID = pID;
	//	this->otherResources = otherResources;
	//	this->status = status;
	//}

	int pID;
	std::list<RCB> otherResources;
	std::pair<pStatus, std::list<PCB>*> status;

	bool operator==(const PCB &p) const;
};

#endif //PCB_H