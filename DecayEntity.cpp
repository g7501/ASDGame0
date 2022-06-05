#include "DecayEntity.h"
#include <iostream>

void DecayEntity::RenderEntity(sf::RenderWindow* window, double DeltaTime)
{
	
	RemainingTime -= DeltaTime;
	PendingDelete = RemainingTime <= 0;
	Entity::RenderEntity(window, DeltaTime);
}


DecayEntity::DecayEntity(std::string inName, float time, sf::Vector2f inLoc) : Entity(inName)
{
	Loc = inLoc;
	RemainingTime = time;
	Components.push_back(new Component(inName));
}