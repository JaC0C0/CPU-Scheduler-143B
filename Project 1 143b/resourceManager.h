#pragma once
#ifndef RESOURCEMANAGER_H
#define RESOURCEMANAGER_H
#include <list>
#include <string>

class ResourceManager {
public:
	//addResource() for init
	void addResource(std::string rID, int quantity);
	void request(std::string rID, int quantity);
	void release(std::string rID);
};
#endif //RESOURCEMANAGER_H