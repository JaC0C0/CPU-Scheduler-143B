#pragma once
#ifndef RCB_H
#define RCB_H
#include <vector>
#include "pcb.h"
#include "status.h"

class RCB
{
	//Requests resource from respective ID. Returns boolean for QoL.
	bool Request(int rID);
	//Release process and respective resources with ID
	void Release(int rID);
};

#endif //RCB_H