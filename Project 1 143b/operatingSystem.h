#pragma once
#ifndef OPERATINGSYSTEM_H
#define OPERATINGSYSTEM_H
#include <list>
#include <string>
#include <map>
#include "rcb.h"
#include "pcb.h"
#include <iostream>
#include <vector>

class OperatingSystem {
public:
	void initOS();
	void create(std::string pID, int priority, int numResources);
	void request(std::string rID, int quantity, std::shared_ptr<PCB> pcb);
	void release(std::string rID);
	void scheduler();
	bool isRunning();
	std::shared_ptr<PCB> getRunning();
	void timeOut();
	void killProcess(std::shared_ptr<PCB>);
	void processState();
	bool checkTermination();
private:
	std::map<std::string, std::shared_ptr<RCB>> resourceMap;
	std::vector<std::shared_ptr<std::list<std::shared_ptr<PCB>>>> priorityQueues;
};

#endif //OPERATINGSYSTEM_H