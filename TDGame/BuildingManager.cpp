#include <json/json.h>
#include <fstream>
#include "BuildingManager.h"

void BuildingManager::loadBuildings() {
	//Loading the data file.
	Json::Value cfg_root = "";
	std::ifstream cfgfile("Data/Buildings/buildings.json");

	//Reading it as json.
	cfgfile >> cfg_root;
	
	const int buildingsSize = cfg_root.size();

	//std::cout << "[DEBUG] JSON: " << cfg_root << std::endl;
	//std::cout << "[DEBUG] BUILDINGS SIZE " << buildingsSize << std::endl;

	//Iterate throughout the buildings.
	for (Json::Value::const_iterator itr = cfg_root.begin(); itr != cfg_root.end(); itr++) {
		std::string buildingName = itr.name();
		
		//Setting values
		std::string componentName = cfg_root[buildingName]["ComponentName"].asString();
		std::string buildingType = cfg_root[buildingName]["BuildingType"].asString();
		int damage = cfg_root[buildingName]["Damage"].asInt();
		float speed = cfg_root[buildingName]["Speed"].asFloat();
		float timeExists = cfg_root[buildingName]["TimeExists"].asFloat();
		float timeGap = cfg_root[buildingName]["TimeGap"].asFloat();
		float attackDelay = cfg_root[buildingName]["AttackDelay"].asFloat();
		int health = cfg_root[buildingName]["Health"].asInt();
		int size = cfg_root[buildingName]["Size"].asInt();
		int range = cfg_root[buildingName]["Range"].asInt();
		int cost = cfg_root[buildingName]["Cost"].asInt();

		//Audi Compnent values
		std::string audioValue = cfg_root[buildingName]["Audio"]["Value"].asString();
		std::string audioSoundComponent = cfg_root[buildingName]["Audio"]["SoundComponent"].asString();

		//Adding a new building to the list
		buildings.push_back(new Building(buildingName, componentName, buildingType, damage, speed,
			timeExists, timeGap, attackDelay, health, size, range, cost, audioValue, audioSoundComponent));
	}
}

Building* BuildingManager::getBuilding(std::string name) {
	for (int i = 0; i < buildings.size(); i++) {
		if (buildings[i]->Name == name) {
			return buildings[i];
		}
	}

	return nullptr;
}

BuildingManager& getBuildingManager() {
	static BuildingManager manager;
	return manager;
}
