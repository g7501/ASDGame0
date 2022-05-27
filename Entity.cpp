#include "Entity.h"
#include "iostream"

void Entity::EntityLogic(double Deltatime)
{
	if (Health<=0)
	{

		delete this;
	}
}



void Entity::RenderEntity(sf::RenderWindow* window, sf::Vector2f Camera)
{
	//Sprite.setPosition(Sprite.getPosition()+Camera);
	//window->draw(Sprite);
	Loc += Camera;
	for(Component* i: Components)
	{
		i->RenderComponent(window, Loc);
	}
	
}

void Entity::AttackEntity(Entity* ATarget)
{
	ATarget->Health -= Attack;
	CountdownToNextAttack = AttackDelay;
}





Entity::Entity(std::string inName)
{
	Name = inName;
}

float Entity::DistanceTo(Entity* other)
{
	float x = std::abs(Loc.x - other->Loc.x);
	float y = std::abs(Loc.y - other->Loc.y);


	return pow(x*x+y*y,0.5);
}

sf::Vector2f Entity::FindLookAtVector(Entity* other)
{
	float x = other->Loc.x - Loc.x;
	float y = other->Loc.y - Loc.y;
	float length = pow(x * x + y * y, 0.5);
	x /= length;
	y /= length;

	return sf::Vector2f(x,y);
}

Entity::~Entity()
{
	for (Component* i: Components)
	{
		delete i;
	}
}



