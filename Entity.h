#pragma once
#include "Component.h"
#include "SoundData.h"


class Entity
{



	
	

public:
	
	virtual void EntityLogic(double DeltaTime);
	void RenderEntity(sf::RenderWindow* , double DeltaTime);
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
	
	bool PendingDelete = false;

	float DistanceTo(Entity* other);
	float DistanceTo(sf::Vector2f point);
	sf::Vector2f FindLookAtVector(Entity* other);

	~Entity();


	static std::vector<Entity*> StaticEntities;

	static void CleanStatics();
	

protected:
	float CountdownToNextAttack;

};



