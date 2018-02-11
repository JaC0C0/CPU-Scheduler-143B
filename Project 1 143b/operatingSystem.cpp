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
		resourceMap.at(rID)->waitingList->push_back(pcb);

	}
	this->scheduler();
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
	this->scheduler();
};

void OperatingSystem::scheduler()
{
	for (size_t i = 0; i < priorityQueues.size(); i++)
	{
		if (!priorityQueues[i]->empty())
		{
			//If the right PCB is running
			if (priorityQueues[i]->front()->status == RUNNING)
			{
				return;
			}
			//If nothing is running but there is a PCB
			else if (priorityQueues[i]->front()->status != RUNNING && !this->isRunning())
			{
				priorityQueues[i]->front()->status = RUNNING;
				return;
			}
			//if the wrong PCB is running. Preemption
			else if (priorityQueues[i]->front()->status != RUNNING && this->isRunning())
			{
				//Setting flag for earlier breaking. Reduce overhead.
				/*bool foundFlag = false;
				for (size_t j = i; j < priorityQueues.size(); j++)
				{
					if (foundFlag)
					{
						break;
					}
					else if (!priorityQueues[j]->empty())
					{
						for (std::shared_ptr<PCB> pcb : *priorityQueues[j])
						{
							if (pcb->status == RUNNING)
							{
								pcb->status = READY;
								foundFlag = true;
								break;
							}
						}
					}
				}*/
				this->getRunning()->status = READY;
				priorityQueues[i]->front()->status = RUNNING;
				return;
			}
		}
	}
}

bool OperatingSystem::isRunning()
{
	for (size_t i = 0; i < priorityQueues.size(); i++)
	{
		if (!priorityQueues[i]->empty())
		{
			for (std::shared_ptr<PCB> pcb : *priorityQueues[i])
			{
				if (pcb->status == RUNNING)
				{
					return true;
				}
			}
		}
	}
	return false;
}

std::shared_ptr<PCB> OperatingSystem::getRunning()
{
	for (size_t i = 0; i < priorityQueues.size(); i++)
	{
		if (!priorityQueues[i]->empty())
		{
			for (std::shared_ptr<PCB> pcb : *priorityQueues[i])
			{
				if (pcb->status == RUNNING)
				{
					return pcb;
				}
			}
		}
	}
}
void OperatingSystem::timeOut()
{
	if (isRunning())
	{
		for (size_t i = 0; i < priorityQueues.size(); i++)
		{
			if (!priorityQueues[i]->empty())
			{
				for (std::shared_ptr<PCB> pcb : *priorityQueues[i])
				{
					if (pcb->status == RUNNING)
					{
						//std::shared_ptr<PCB> tempPCB = pcb;
						pcb->status = READY;
						priorityQueues[i]->remove(pcb);
						priorityQueues[i]->push_back(pcb);
						break;
					}
				}
			}
		}
	}
	this->scheduler();
}