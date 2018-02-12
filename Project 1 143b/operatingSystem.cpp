#include "operatingSystem.h"

void OperatingSystem::initOS()
{
	std::shared_ptr<std::list<std::shared_ptr<PCB>>> 
		priorityQueue0 = std::make_shared<std::list<std::shared_ptr<PCB>>>(), priorityQueue1 = std::make_shared<std::list<std::shared_ptr<PCB>>>(), priorityQueue2 = std::make_shared<std::list<std::shared_ptr<PCB>>>();
	this->priorityQueues = { priorityQueue0, priorityQueue1, priorityQueue2 };
	this->resourceMap = { { "R1", std::make_shared<RCB>(RCB(1)) },{ "R2", std::make_shared<RCB>(RCB(2)) },
	{ "R3", std::make_shared<RCB>(RCB(3)) },{ "R4", std::make_shared<RCB>(RCB(4)) } };
	this->create("init", 0, 0);	
	this->scheduler();
}

void OperatingSystem::create(std::string pID, int priority, int numResources)
{
	std::shared_ptr<PCB> parent = this->getRunning();
	std::shared_ptr<PCB> newPCB = std::make_shared<PCB>(PCB(pID, priority, numResources, priorityQueues[priority], parent));
	priorityQueues[priority]->push_back(std::shared_ptr<PCB>(newPCB));
	this->scheduler();
}

void OperatingSystem::request(std::string rID, int quantity, std::shared_ptr<PCB> pcb)
{
	//Sets the # of resources the 
	//pcb->numResources = quantity;
	std::shared_ptr<RCB> rcb = resourceMap.at(rID);
	//Check if RCB already is requested and add to that RCB request
	if (this->checkRCB(pcb->otherResources, rID))
	{
		this->returnRCB(pcb->otherResources, rID)->first += quantity;
	}
	else if (rcb->resources.second == quantity)
	{
		rcb->resources.second = 0;
		pcb->otherResources.push_back(std::make_shared<std::pair<int, std::shared_ptr<RCB>>>(std::make_pair(quantity, rcb)));
	}
	else if (rcb->resources.second > quantity)
	{
		rcb->resources.second -= quantity;
		rcb->resources.second = 0;
		pcb->otherResources.push_back(std::make_shared<std::pair<int, std::shared_ptr<RCB>>>(std::make_pair(quantity, rcb)));
	}
	else
	{
		std::cout << "Resource " << rID << " is blocked" << std::endl;
		pcb->list = resourceMap.at(rID)->waitingList;
		pcb->reqResources = quantity;
		pcb->status = BLOCKED;
		rcb->waitingList->push_back(pcb);
	}
	this->scheduler();
};

void OperatingSystem::release(std::string rID, int quantity)
{
	RCB& rcb = *resourceMap.at(rID);
	//rcb.resources.second += this->getRunning()->numResources;
	rcb.resources.second += quantity;
	this->returnRCB(this->getRunning()->otherResources, rID)->first -= quantity;
	//If process still contains resource
	if (this->returnRCB(this->getRunning()->otherResources, rID)->first == 0)
	{
		for (auto rcb : this->getRunning()->otherResources)
		{
			this->getRunning()->otherResources.remove(rcb);
		}
	}
	//Check for other waiting processes and if enough resources, request more resources
	while (!rcb.waitingList->empty() && rcb.resources.first >= rcb.waitingList->front()->reqResources)
	{
		//reqResources is the amount of resources requested by the process that is waiting
		int reqResources = rcb.waitingList->front()->reqResources;

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
	for (size_t i = 2; i == 0; i--)
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

std::shared_ptr<PCB> OperatingSystem::returnProcess(std::string pID)
{
	for (size_t i = 0; i < priorityQueues.size(); i++)
	{
		if (!priorityQueues[i]->empty())
		{
			for (std::shared_ptr<PCB> pcb : *priorityQueues[i])
			{
				if (pcb->pID == pID)
				{
					return pcb;
				}
			}
		}
	}
	return nullptr;
}

std::shared_ptr<std::pair<int, std::shared_ptr<RCB>>> OperatingSystem::returnRCB(
	std::list<std::shared_ptr<std::pair<int, std::shared_ptr<RCB>>>> list, std::string rID)
{
	for (std::shared_ptr<std::pair<int, std::shared_ptr<RCB>>> rcb : list)
	{
		if (rcb->second->rID == rID)
		{
			return rcb;
		}
	}
	return nullptr;
}

bool OperatingSystem::checkRCB(std::list<std::shared_ptr<std::pair<int, std::shared_ptr<RCB>>>> list, std::string rID)
{
	for (std::shared_ptr<std::pair<int, std::shared_ptr<RCB>>> rcb : list)
	{
		if (rcb->second->rID == rID)
		{
			return true;
		}
	}
	return false;
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
		for (std::shared_ptr<std::pair<int, std::shared_ptr<RCB>>> rcb : pcb->otherResources)
		{
			this->release(rcb->second->rID, rcb->first);
		}
	}
	this->scheduler();
}

void OperatingSystem::processState()
{
	if (this->isRunning())
	{
		std::cout << "Process " << this->getRunning()->pID << " is running" << std::endl;
	}
}

bool OperatingSystem::checkTermination()
{
	if (this->isRunning() && this->getRunning()->pID == "init")
	{
		return true;
	}
	return false;
}