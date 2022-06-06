#include "Building.h"
#include <iostream>
#include <filesystem>
#include <fstream>

Building::Building(std::string inName, sf::Vector2f Loc) : Entity(inName)
{
	size = 50;
	
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
		Range = 1200;
	}
	if (inName == "TownCentre")
	{
		ProjectileInst.Damage = 15;
		ProjectileInst.Speed = 700;
		ProjectileInst.TimeExists = 4;
		ProjectileInst.TimeGap = 0.65;
		AttackDelay = 1;
		AudioComponents.emplace("Fire", new SoundComponent("ArrowFire"));
		Range = 800;
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
		Health = 75;
		AudioComponents.emplace("Fire", new SoundComponent("MagicFire"));
		Range = 350;
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

bool Building::NotWithinBuilding(std::vector<Building*> buildings, sf::Vector2f point)
{
	for(Building* i: buildings)
	{
		if (i->DistanceTo(point)<i->size+i->UsingTerrain)
		{
			return false;
		}
	}

	return true;
}

int Building::GetIndexOfHoveredTower(std::vector<Building*> buildings, sf::Vector2f point)
{
	int idx = 0;
	for (Building* i: buildings)
	{
		if (i->DistanceTo(point)<i->size)
		{
			return idx;
		}
		idx++;
	}



	return -1;
}



std::map<std::string, BuildingData> Building::BuildingList;

namespace fs = std::filesystem;

void Building::LoadAllBuildings()
{

	for (const auto& entry : fs::directory_iterator("Data/Buildings"))
	{
		BuildingData tmp = BuildingData(entry.path().filename().string());
		BuildingList.emplace(entry.path().filename().stem().string(),tmp);
	}

}


//put this somewhere else
std::string ReadString(std::ifstream* inp)
{
	uint8_t len;
	inp->read((char*)&len, 1);
	std::string out;
	char tmp[255];
	inp->read(tmp,len);
	tmp[len] = '\0';
	out = tmp;
	return out;
}


BuildingData::BuildingData(std::string file)
{
	std::ifstream ifs("Data/Buildings/"+file, std::fstream::binary);
	
	int version; //probably add an if here
	ifs.read((char*)&version,4);
	ReadString(&ifs);
	ifs.read((char*)&Health, 4);
	ifs.read((char*)&PDamage, 4);
	ifs.read((char*)&PTimeGap, 4);
	ifs.read((char*)&size, 4);
	ifs.read((char*)&Range, 4);
	ifs.read((char*)&Surrounding, 4);
	ReadString(&ifs);



}
