#pragma once
#include "Entity.h"
#include "Projectile.h"
#include "Soldier.h"

struct ProjectileData
{
	sf::Texture Texture;
	int Damage;
	float Speed;
	float TimeGap;
	float TimeExists;
};



class Building : public Entity
{
	

public:
	Building(std::string inName, sf::Vector2f Loc);
	void EntityLogic(double DeltaTime, std::vector<Projectile*>* projectiles, std::vector<Soldier*> Targets);
	ProjectileData ProjectileInst;
	
	sf::Vector2f AimingDirection = sf::Vector2f(0,0);

	
};



