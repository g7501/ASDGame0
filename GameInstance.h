#pragma once
#include <vector>
#include "StandardIO.h"
#include "Terrain.h"
#include "TownCentre.h"
#include "Soldier.h"
#include "HUD.h"

class GameInstance
{
public:
	GameInstance();
	void GameLoop();
	ConfigData config;

	int Gold = 500;
private:
	float TotalTime = 0;


	sf::RenderWindow* window;
	
	Terrain* TerrainData;
	sf::Vector2f CameraLocation;
	sf::Vector2f CameraDelta;


	TownCentre* Town;
	
	std::vector<Building*> Buildings;
	std::vector<Building*> Mines;
	std::vector<Soldier*> Soldiers;
	std::vector<Projectile*> Projectiles;
	std::vector<Projectile*> ProjectileRemovals;


	HUD* UI;

	float SecondTimer; //logic in gold calc
	void GoldCalulation(double DeltaTime);


	void SetObjectToTower();
	void SetObjectToMine();
	void SetObjectToMage();

	void HandleButtons(double DeltaTime);

	float MouseCooldown = 0;

	std::string CurrentPlaceObject = "";


	void AimAtNearestEnemy(Building* inst);


	void ProjectileCollision(Projectile* inst);

	
	void FindBuildingtoAttack(Soldier* inst);

	void SpawnEnemies();


	float EnemySpawnCountDown = 6;
};

