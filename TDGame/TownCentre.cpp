#include "TownCentre.h"
#include<iostream>

TownCentre::TownCentre() : Building("TownCentre",sf::Vector2f(0,0))
{
	size = 150;
	Health = 100000;
	Components.push_back(new Component("TownCentre"));
}


