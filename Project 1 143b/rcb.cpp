#include "rcb.h"

//Constructor
//RCB::RCB(int rID, int resources)
//{
//	this->rID = rID;
//	this->resources = resources;
//}
//
////Getters and Setters
//int RCB::getRID()
//{
//	return rID;
//}
//
//int RCB::getResources()
//{
//	return resources;
//}
//
//void RCB::incrementResources(int incr)
//{
//	this->resources += incr;
//}
//
//void RCB::decreaseResources(int decr)
//{
//	this->resources -= decr;
//}
//
//rStatus RCB::getStatus()
//{
//	return this->status;
//}
//
//void RCB::setStatus(rStatus status)
//{
//	this->status = status;
//}
//
//std::list<PCB> RCB::getWaitingList()
//{
//	return waitingList;
//}

//Constructor
bool RCB::operator==(const RCB &r) const { return rID == r.rID; }