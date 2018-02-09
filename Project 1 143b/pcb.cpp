#include "pcb.h"
#include "status.h"

//Constructor
PCB::PCB(int pID, std::vector<int> otherResources, std::pair<pStatus, std::list<PCB>*> status)
{
	this->pID = pID;
	this->otherResources = otherResources;
	this->status = status;
}

//== overrider
bool PCB::operator==(const PCB &p) const { return pID == p.pID;}