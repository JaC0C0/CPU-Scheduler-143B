#pragma once
#ifndef RESOURCEMANAGER_H
#define RESOURCEMANAGER_H
#include <list>
#include <string>
#include <map>
#include "rcb.h"
#include "pcb.h"
#include <iostream>

class ResourceManager {
public:
	//addResource() for init
	//void addResource(std::string rID, int quantity);
	void request(std::string rID, int quantity, PCB pcb);
	void release(std::string rID, int quantity, PCB pcb);
private:
	std::map<std::string, RCB> resourceMap;
};
#endif //RESOURCEMANAGER_H