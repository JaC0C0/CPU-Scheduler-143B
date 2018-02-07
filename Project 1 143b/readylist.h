#pragma once
#ifndef READYLIST_H
#define READYLIST_H
#include <list>
#include "pcb.h"

class ReadyList {
public:
	void addProcess(int priority, PCB pcb);
	void cycleProcess(int priority);
	void popProcess(int pID);
private:
	std::list<PCB> priorityQ1, priorityQ2, priorityQ3;
};

#endif //READYLIST_H