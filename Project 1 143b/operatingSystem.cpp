#include "operatingSystem.h"

OperatingSystem::OperatingSystem()
{
	std::shared_ptr<std::list<std::shared_ptr<PCB>>> priorityQueue0, priorityQueue1, priorityQueue2;
	this->priorityQueues = { priorityQueue0, priorityQueue1, priorityQueue2 };
}

void OperatingSystem::request(std::string rID, int quantity, std::shared_ptr<PCB> pcb)
{
	//Sets the # of resources the 
	pcb->numResources = quantity;
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
		pcb->list = resourceMap.at(rID)->waitingList;
		pcb->status = BLOCKED;
		resourceMap.at(rID)->waitingList->push_back(std::make_pair(quantity, pcb));

	}
};

void OperatingSystem::release(std::string rID, int quantity, PCB pcb)
{
	RCB rcb = *resourceMap.at(rID);
	rcb.resources.second += quantity;
	//Check for other waiting processes and if enough resources, request more resources
	while (!rcb.waitingList->empty() && rcb.resources.first >= rcb.waitingList->front()->numResources)
	{
		//reqResources is the amount of resources requested by the process that is waiting
		int reqResources = rcb.waitingList->front()->numResources;

		std::shared_ptr<PCB> newlyReleased = rcb.waitingList->front();
		//Remove ptr to PCB from the front of the waitingList to the respective priority queue and reserves respective resources
		rcb.resources.second -= reqResources;
		rcb.waitingList->pop_front();
		priorityQueues[newlyReleased->priority]->push_front(newlyReleased);
		//Change status of PCB to ready and next in line for running
		newlyReleased->list = priorityQueues[newlyReleased->priority];
		newlyReleased->status = READY;
	}
};

void OperatingSystem::scheduler()
{
	for (int i; i < priorityQueues.size(); i++)
	{
		if (!priorityQueues[i]->empty())
		{
			if (priorityQueues[i]->front()->)
		}
	}
}