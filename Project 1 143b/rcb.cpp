#include "rcb.h"

//Constructor
RCB::RCB(int rID)
{
	this->rID = "R" + std::to_string(rID);
	this->resources = std::make_pair(rID, rID);
	this->waitingList = std::make_shared<std::list<std::shared_ptr<PCB>>>();
}

//Overrider for compare
bool RCB::operator==(const RCB &r) const { return rID == r.rID; }