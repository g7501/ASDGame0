#include "Building.h"
#include <iostream>

Building::Building(std::string inName, sf::Vector2f Loc) : Entity(inName)
{
	
	
	
	
	if (inName=="StandardTower")
	{
		Components.push_back(new Component("StandardTower"));
		ProjectileInst.Damage = 15;
		ProjectileInst.Speed = 700;
		ProjectileInst.TimeExists = 4;
		ProjectileInst.TimeGap = 0.65;
		AttackDelay = 1;
		Health = 125;
		AudioComponents.emplace("Fire", new SoundComponent("ArrowFire"));
	}
	if (inName == "TownCentre")
	{
		ProjectileInst.Damage = 15;
		ProjectileInst.Speed = 700;
		ProjectileInst.TimeExists = 4;
		ProjectileInst.TimeGap = 0.65;
		AttackDelay = 1;
		AudioComponents.emplace("Fire", new SoundComponent("ArrowFire"));
	}
	if (inName=="Mine")
	{
		Components.push_back(new Component("Mine"));
		Health = 100;
	}
	if (inName=="Mage")
	{
		Components.push_back(new Component("MageTower"));
		ProjectileInst.Damage = 8;
		ProjectileInst.Speed = 550;
		ProjectileInst.TimeExists = 0.6;
		ProjectileInst.TimeGap = 0.55;
		AttackDelay = 0.4;
		Health = 150;
		AudioComponents.emplace("Fire", new SoundComponent("MagicFire"));
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

			if (Name == "Mage")
			{
				
				projectiles->push_back(new Projectile(ProjectileInst.Speed, ProjectileInst.Damage, ProjectileInst.TimeExists, AimingDirection, "Magic"));
				projectiles->back()->Loc = Loc;

				projectiles->push_back(new Projectile(ProjectileInst.Speed, ProjectileInst.Damage, ProjectileInst.TimeExists, AimingDirection, "Magic"));
				projectiles->back()->Loc = Loc + sf::Vector2f(std::rand() % 20 - 10, std::rand()%20-10);

				projectiles->push_back(new Projectile(ProjectileInst.Speed, ProjectileInst.Damage, ProjectileInst.TimeExists, AimingDirection,"Magic"));
				projectiles->back()->Loc = Loc+sf::Vector2f(std::rand() % 20 - 10, std::rand() % 20 - 10);
			}
			if (Name == "TownCentre" || Name=="StandardTower")
			{

				projectiles->push_back(new Projectile(ProjectileInst.Speed, ProjectileInst.Damage, ProjectileInst.TimeExists, AimingDirection,"Arrow"));
				projectiles->back()->Loc = Loc;
				
			}
			AudioComponents.at("Fire")->Audio.play();
		}
	}
	else
	{
		CountdownToNextAttack -= DeltaTime;
	}

}

