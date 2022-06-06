#include "Projectile.h"
#include <iostream>


Projectile::Projectile(float SpeedT, int DamageT, float TimeT, sf::Vector2f DirectionT, std::string type) : Entity("Arrow")
{
	Components.push_back(new Component(type));
	Speed = SpeedT;
	Damage = DamageT;
	RemainingTime = TimeT;
	Direction = DirectionT;

	//initially in radians so must convert
	float d = atan2(DirectionT.x,DirectionT.y)*57.296;
	
	Components.back()->Rotation = d;
	
	
}

void Projectile::EntityLogic(double DeltaTime)
{
	Loc = (Loc + Direction * Speed * (float)DeltaTime);
	RemainingTime -= DeltaTime;
}