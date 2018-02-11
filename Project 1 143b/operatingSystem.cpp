#include "operatingSystem.h"

OperatingSystem::OperatingSystem()
{
	std::list<PCB> priorityQueue0, priorityQueue1, priorityQueue2;
	this->priorityQueues = { priorityQueue0, priorityQueue1, priorityQueue2 };
}

void OperatingSystem::request(std::string rID, int quantity, std::shared_ptr<PCB> pcb)
{
	if (resourceMap.at(rID)->resources.second == quantity)
	{
		resourceMap.at(rID)->resources.second = 0;
		//resourceMap.at(rID).status = rStatus::BLOCKED;
	}
	else if (resourceMap.at(rID)->resources.second > quantity)
	{
		resourceMap.at(rID)->resources.second -= quantity;
	}
	else
	{
		std::cout << "Resource Blocked" << std::endl;
		resourceMap.at(rID)->waitingList->push_back(std::make_pair(quantity, pcb));

	}
};

void OperatingSystem::release(std::string rID, int quantity, PCB pcb)
{
	RCB rcb = *resourceMap.at(rID);
	rcb.resources.second += quantity;
	//Check for other waiting processes and if enough resources, request more resources
	while (!rcb.waitingList->empty() && rcb.resources.first >= rcb.waitingList->front().first)
	{
		std::shared_ptr<PCB> newlyReleased = rcb.waitingList->front().second;
		rcb.resources.second -= rcb.waitingList->front().first;
		rcb.waitingList->pop_front();
		//newlyReleased->readyList->assign();

	}
};