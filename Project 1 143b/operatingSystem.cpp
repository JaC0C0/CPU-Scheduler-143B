#include "operatingSystem.h"

OperatingSystem::OperatingSystem()
{
	std::shared_ptr<std::list<std::shared_ptr<PCB>>> 
		priorityQueue0 = std::make_shared<std::list<std::shared_ptr<PCB>>>(), priorityQueue1 = std::make_shared<std::list<std::shared_ptr<PCB>>>(), priorityQueue2 = std::make_shared<std::list<std::shared_ptr<PCB>>>();
	this->priorityQueues = { priorityQueue0, priorityQueue1, priorityQueue2 };
	this->resourceMap = { { "R1", std::make_shared<RCB>(RCB(1)) },{ "R2", std::make_shared<RCB>(RCB(2)) },
	{ "R3", std::make_shared<RCB>(RCB(3)) },{ "R4", std::make_shared<RCB>(RCB(4)) } };
	this->create("init", 0, 0);	
}

void OperatingSystem::create(std::string pID, int priority, int numResources)
{
	std::shared_ptr<PCB> parent = this->getRunning();
	std::shared_ptr<PCB> newPCB = std::make_shared<PCB>(PCB(pID, priority, numResources, priorityQueues[priority], parent));
	priorityQueues[priority]->push_back(std::shared_ptr<PCB>(newPCB));
}

void OperatingSystem::request(std::string rID, int quantity, std::shared_ptr<PCB> pcb)
{
	//Sets the # of resources the 
	pcb->numResources = quantity;
	if (resourceMap.at(rID)->resources.second == quantity)
	{
		resourceMap.at(rID)->resources.second = 0;
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

void OperatingSystem::release(std::string rID)
{
	RCB& rcb = *resourceMap.at(rID);
	rcb.resources.second += this->getRunning()->numResources;
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
	if (this->isRunning())
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
	return nullptr;
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

void OperatingSystem::killProcess(std::shared_ptr<PCB> pcb)
{
	if (!pcb->children.empty())
	{
		for (std::shared_ptr<PCB> iterPCB : pcb->children)
		{
			this->killProcess(iterPCB);
		}
	}
	if (!pcb->otherResources.empty())
	{
		for (std::shared_ptr<RCB> rcb : pcb->otherResources)
		{
			this->release(rcb->rID);
		}
	}
}