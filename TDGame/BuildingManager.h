#include<iostream>
#include "Building.h"

class BuildingManager {
public:
	/*
	* No clue how to use arrays in c++...
	* change it to an array - It's much faster.
	*/
	std::vector<Building*> buildings;
	
	void loadBuildings();
	Building* getBuilding(std::string name);
};

BuildingManager& getBuildingManager();