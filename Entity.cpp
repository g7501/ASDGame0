#include "Entity.h"
#include "iostream"



std::vector<Entity*> Entity::StaticEntities;


void Entity::EntityLogic(double Deltatime)
{
	//probably needs removing
	//if (Health<=0)
	//{

		//delete this;
	//}

}



void Entity::RenderEntity(sf::RenderWindow* window, double DeltaTime)
{
	//Sprite.setPosition(Sprite.getPosition()+Camera);
	//window->draw(Sprite);
	
	sf::Vector2f LocalPosition = (Loc + Camera::Location)*Camera::Zoom;
	for(Component* i: Components)
	{
		i->RenderComponent(window,LocalPosition, DeltaTime);
	}
	//sound is part of rendering
	for(std::pair<std::string, SoundComponent*> i: AudioComponents)
	{
		i.second->AudioLogic(Loc);
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

float Entity::DistanceTo(sf::Vector2f point)
{
	float x = std::abs(Loc.x - point.x);
	float y = std::abs(Loc.y - point.y);


	return pow(x * x + y * y, 0.5);
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

	for (std::pair<std::string, SoundComponent*> i : AudioComponents)
	{
		delete i.second;
	}
}

void Entity::CleanStatics()
{
	for (size_t i = 0; i < StaticEntities.size();)
	{
		if (StaticEntities.at(i)->PendingDelete)
		{
			delete StaticEntities.at(i);
			StaticEntities.erase(StaticEntities.begin()+ i);
		}
		else
		{
			i++;
		}
	}


}



