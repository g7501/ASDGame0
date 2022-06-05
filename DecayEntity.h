#pragma once
#include "Entity.h"

class DecayEntity : public Entity
{
public:
	float RemainingTime;
	void RenderEntity(sf::RenderWindow* window, double DeltaTime);

	DecayEntity(std::string inName, float time, sf::Vector2f inLoc);
};

