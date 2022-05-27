#include "Soldier.h"
#include <iostream>

void Soldier::EntityLogic(double Deltatime)
{
	Entity::EntityLogic(Deltatime);
	//unit vector calculations can be put somewhere else
	//is in the entity class now

	if (DistanceTo(Target)<Target->size)
	{
		//attack
		if (CountdownToNextAttack<0)
		{
			AttackEntity(Target);
		}
		else
		{
			CountdownToNextAttack -= Deltatime;
		}
	}
	else
	{
		//move


		
		Loc=(Loc + FindLookAtVector(Target) *(float)Deltatime*Speed);
	}


}



Soldier::Soldier(std::string inName, sf::Vector2f SpawnLocation, Entity* inTarget) : Entity(inName)
{
	Target = inTarget;
	
	
	Loc = SpawnLocation;
	Health = 50;
	Attack = 5;


	Components.push_back(new Component("Grunt"));
}
