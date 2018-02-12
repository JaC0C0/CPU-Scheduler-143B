#include "pcb.h"
#include "status.h"
#include "rcb.h"

PCB::PCB(std::string pID, int priority, int reqResources, std::shared_ptr<std::list<std::shared_ptr<PCB>>> list,
	std::shared_ptr<PCB> parent)
{
	this->pID = pID;
	this->priority = priority;
	this->reqResources = reqResources;
	this->status = READY;
	this->list = list;
	this->parent = parent;
}

//== overrider
bool PCB::operator==(const PCB &p) const { return pID == p.pID;}