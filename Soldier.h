#pragma once
#include "Entity.h"
class Soldier :
    public Entity
{
    Entity* Target;
    float Speed = 100;
public:
    void EntityLogic(double DeltaTime);
    Soldier(std::string inName, sf::Vector2f SpawnLocation, Entity* inTarget);
};

