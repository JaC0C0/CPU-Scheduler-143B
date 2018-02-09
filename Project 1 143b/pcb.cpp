#include "pcb.h"
#include "status.h"
#include "rcb.h"

//== overrider
bool PCB::operator==(const PCB &p) const { return pID == p.pID;}