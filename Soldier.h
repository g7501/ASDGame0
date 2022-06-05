#pragma once
#include "Entity.h"
#include "DecayEntity.h"



class Soldier :
    public Entity
{
    
    float Speed = 100;
public:
    void EntityLogic(double DeltaTime);
    Soldier(std::string inName, sf::Vector2f SpawnLocation, Entity* inTarget);
    Entity* Target;

    ~Soldier();
    
    
};

