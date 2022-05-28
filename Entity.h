#pragma once
#include "Component.h"
#include "SoundData.h"


class Entity
{



	
	

public:
	
	virtual void EntityLogic(double DeltaTime);
	void RenderEntity(sf::RenderWindow* window);
	void AttackEntity(Entity* ATarget);
	Entity(std::string inName);


	sf::Vector2f Loc;
	int Health;
	int Attack;
	float AttackDelay;
	int size;
	std::string Name;

	std::vector<Component*> Components;
	std::map<std::string, SoundComponent*> AudioComponents; 
	

	float DistanceTo(Entity* other);
	sf::Vector2f FindLookAtVector(Entity* other);

	~Entity();

protected:
	float CountdownToNextAttack;

};



