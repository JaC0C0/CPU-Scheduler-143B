#include "resourceManager.h"

//void ResourceManager::addResource(std::string rID, int quantity)
//{
//	resourceMap.at(rID).resources += quantity;
//};

void ResourceManager::request(std::string rID, int quantity, std::shared_ptr<PCB> pcb)
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
		//resourceMap.at(rID).status = rStatus::BLOCKED;
		resourceMap.at(rID)->waitingList->push_back(std::make_pair(quantity, pcb));
	}
};

void ResourceManager::release(std::string rID, int quantity, PCB pcb)
{
	RCB rcb = *resourceMap.at(rID);
	rcb.resources.second += quantity;
	//Check for other waiting processes and if enough resources, request more resources
	while (!rcb.waitingList->empty & rcb.resources.first >= rcb.waitingList->front->first)
	{
		PCB newlyReleased = rcb.waitingList->front->second;
		rcb.resources.second -= rcb.waitingList->front->first;
		rcb.waitingList->pop_front;
		

	}
};