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
	PCB(std::string pID, int priority, int numResources, std::shared_ptr<std::list<std::shared_ptr<PCB>>> list, 
		std::shared_ptr<PCB> parent);
	std::string pID;
	int priority, numResources;
	std::list<std::shared_ptr<RCB>> otherResources;
	pStatus status;
	std::shared_ptr<std::list<std::shared_ptr<PCB>>> list;
	//Parent/Child Tree Element
	std::shared_ptr<PCB> parent;
	std::list<std::shared_ptr<PCB>> children;

	bool operator==(const PCB &p) const;
};

#endif //PCB_H