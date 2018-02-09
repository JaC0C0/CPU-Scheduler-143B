#include "resourceManager.h"

void ResourceManager::addResource(std::string rID, int quantity)
{
	resourceMap.at(rID).incrementResources(quantity);
};

void ResourceManager::request(std::string rID, int quantity, PCB pcb)
{
	if (resourceMap.at(rID).getResources() == quantity)
	{
		resourceMap.at(rID).decreaseResources(quantity);
		resourceMap.at(rID).setStatus(rStatus::BLOCKED);
	}
	else if (resourceMap.at(rID).getResources() > quantity)
	{
		resourceMap.at(rID).decreaseResources(quantity);
	}
	else
	{
		std::cout << "Resource Blocked" << std::endl;
		resourceMap.at(rID).setStatus(rStatus::BLOCKED);
		resourceMap.at(rID).getWaitingList().push_back(pcb);
	}
};

void ResourceManager::release(std::string rID)
{

};