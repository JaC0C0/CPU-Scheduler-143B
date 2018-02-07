#include "readylist.h"

//Adds PCB from OS process creation
void ReadyList::addProcess(int priority, PCB pcb)
{
	switch (priority)
	{
	case 1:
		priorityQ1.push_back(pcb);
		break;
	case 2:
		priorityQ2.push_back(pcb);
		break;
	case 3:
		priorityQ3.push_back(pcb);
		break;
	}
}
//Moves front process to back for round robin
void ReadyList::cycleProcess(int priority)
{
	switch (priority)
	{
	case 1:
		priorityQ1.push_back(priorityQ1.front());
		priorityQ1.pop_front();
		break;
	case 2:
		priorityQ2.push_back(priorityQ2.front());
		priorityQ2.pop_front();
		break;
	case 3:
		priorityQ3.push_back(priorityQ3.front());
		priorityQ3.pop_front();
		break;
	}
}
//Removes process based on pID regardless of priority queue
void ReadyList::popProcess(int pID)
{
	for (PCB pcb : priorityQ1)
	{
		if (pcb.pID == pID)
		{
			priorityQ1.remove(pcb);
			return;
		}
	}
	for (PCB pcb : priorityQ2)
	{
		if (pcb.pID == pID)
		{
			priorityQ2.remove(pcb);
			return;
		}
	}
	for (PCB pcb : priorityQ3)
	{
		if (pcb.pID == pID)
		{
			priorityQ3.remove(pcb);
			return;
		}
	}
	//Not too sure how this works. Please check back to make sure this doesn't screw things up later
	throw std::invalid_argument("Process ID not found in ReadyList");
}

