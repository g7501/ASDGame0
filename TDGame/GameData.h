#pragma once
#include "Building.h"

class GameData
{
public:

	static std::vector<Building*> Buildings;
	static std::vector<Building*> Mines;
	static std::vector<Soldier*> Soldiers;
	static std::vector<Projectile*> Projectiles;

	static void CleanEntities();
};

