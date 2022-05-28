#pragma once
#include <SFML/Graphics.hpp>
#include "Entity.h"

class Projectile : public Entity
{
	
	float Speed;
	
	
	sf::Vector2f Direction;
public:
	Projectile(float SpeedT, int DamageT, float TimeT, sf::Vector2f DirectionT, std::string type);
	void Run(double DeltaTime);
	int Damage;
	void EntityLogic(double DeltaTime);
	float RemainingTime;
};

