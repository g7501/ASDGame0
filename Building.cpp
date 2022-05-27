#include "Building.h"
#include <iostream>

Building::Building(std::string inName, sf::Vector2f Loc) : Entity(inName)
{
	


	
	if (inName=="StandardTower" || inName=="TownCentre")
	{
		Components.push_back(new Component("StandardTower"));
		ProjectileInst.Damage = 15;
		ProjectileInst.Speed = 700;
		ProjectileInst.TimeExists = 4;
		ProjectileInst.TimeGap = 0.65;
		AttackDelay = 1;
	}
	if (inName=="Mine")
	{
		Components.push_back(new Component("Mine"));
	}
	if (inName=="Mage")
	{
		Components.push_back(new Component("MageTower"));
		ProjectileInst.Damage = 8;
		ProjectileInst.Speed = 550;
		ProjectileInst.TimeExists = 4;
		ProjectileInst.TimeGap = 0.55;
		AttackDelay = 1;
	}

	this->Loc = Loc;
}

void Building::EntityLogic(double DeltaTime, std::vector<Projectile*>* projectiles, std::vector<Soldier*> Targets)
{
	
	if (CountdownToNextAttack<=0)
	{
		
		CountdownToNextAttack = AttackDelay;
		if (AimingDirection!=sf::Vector2f(0,0))
		{
			
			projectiles->push_back(new Projectile(ProjectileInst.Speed, ProjectileInst.Damage, ProjectileInst.TimeExists, AimingDirection));
			projectiles->back()->Loc = Loc;
		}
	}
	else
	{
		CountdownToNextAttack -= DeltaTime;
	}

}

