#pragma once
#include <SFML/Graphics.hpp>
#include "Entity.h"

class Projectile : public Entity
{
	

public:
	Projectile(float SpeedT, int DamageT, float TimeT, sf::Vector2f DirectionT, std::string type);
	void Run(double DeltaTime);
	int Damage;
	void EntityLogic(double DeltaTime);
	float RemainingTime;


	float Speed;


	sf::Vector2f Direction;
};

