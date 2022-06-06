#include "Soldier.h"
#include <iostream>

void Soldier::EntityLogic(double Deltatime)
{



	Entity::EntityLogic(Deltatime);
	//unit vector calculations can be put somewhere else
	//is in the entity class now

	if (DistanceTo(Target)<Target->size+size)
	{
		//attack
		if (CountdownToNextAttack<0)
		{
			AttackEntity(Target);
			CountdownToNextAttack = AttackDelay;
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

	if (inName == "Grunt")
	{
		Health = 50;
		Attack = 5;
		size = 5;
		AttackDelay = 1.5;
		Speed = 100;
	}

	if (inName == "Giant")
	{
		Health = 175;
		Attack = 20;
		size = 10;
		AttackDelay = 2.5;
		Speed = 85;
	}
	if (inName == "Raider")
	{
		Health = 30;
		Attack = 6;
		size = 6;
		AttackDelay = 1.2;
		Speed = 140;
	}

	if (inName == "Knight")
	{
		Health = 125;
		Attack = 12;
		size = 6;
		AttackDelay = 1.4;
		Speed = 95;
	}



	Components.push_back(new Component(inName));
}

Soldier::~Soldier()
{
	Entity::StaticEntities.push_back(new DecayEntity(Name+"Corpse",2,Loc));

}
