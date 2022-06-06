#pragma once
#include <vector>
#include "StandardIO.h"
#include "Terrain.h"
#include "HUD.h"
#include "GameData.h"
#include "TownCentre.h"







class GameInstance
{
public:
	GameInstance();
	void GameLoop();
	void LoadGame();
	ConfigData config;

	int Gold = 500;
private:
	float TotalTime = 0;


	sf::RenderWindow* window;
	
	Terrain* TerrainData;
	sf::Vector2f CameraLocation;
	sf::Vector2f CameraDelta;


	TownCentre* Town;
	
	//std::vector<Building*> Buildings;
	std::vector<Building*> BuildingsRemovals;
	//std::vector<Building*> Mines;
	std::vector<Building*> MineRemovals;
	std::vector<Soldier*> Soldiers;
	//std::vector<Projectile*> Projectiles;
	std::vector<Projectile*> ProjectileRemovals;

	

	FieldButton* CurrentUpgrade;


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


	void SaveGame();


};

