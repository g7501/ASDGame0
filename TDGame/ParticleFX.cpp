#include "ParticleFX.h"
#include <iostream>
#include <fstream>






void ParticleFX::Render(sf::RenderWindow* window, sf::Vector2f RenderLoc, double DeltaTime)
{

	int idx = 0;
	for (Shape* i : Shapes)
	{
		window->draw(*i->s);
		i->s->setPosition(i->s->getPosition()+(i->Velocity*(float)DeltaTime));
		i->RemainingTime -= DeltaTime;
		i->s->setScale(i->s->getScale()+i->s->getScale()*(float)DeltaTime*Template.DeltaSize);
		i->Velocity = (i->Velocity + i->Velocity * (float)DeltaTime*Template.DeltaVelocity);
		
		if (i->RemainingTime<=0)
		{
			
			delete i->s;
			delete i;
			Shapes.erase(Shapes.begin()+idx);
		}
		else
		{
			
			idx++;
		}
		
	}
	
	if (SpawnShapeTimeRemain<=0)
	{
		
		SpawnShapeTimeRemain = SpawnShapeTime + Utils::RandomFloatInRange(SpawnShapeTimeVariance);
	
		sf::Vector2f tVel;
		if (RandomVelocity)
		{
			tVel = sf::Vector2f(Utils::RandomFloatInRange(Velocity.x),Utils::RandomFloatInRange(Velocity.y));
		}
		else
		{
			tVel = Velocity;
		}
		Shapes.push_back(new Shape(Template.LifeTime, tVel));
		Shapes.back()->s = new sf::Sprite();
		Shapes.back()->s->setScale(sf::Vector2f(Template.Size,Template.Size));
		Shapes.back()->s->setColor(Template.Colour);
		Shapes.back()->s->setPosition(Loc+ sf::Vector2f(Utils::RandomFloatInRange(Template.LocVariance), Utils::RandomFloatInRange(Template.LocVariance)));
		Shapes.back()->s->setTexture(*Anim::Animations.at(Template.ShapeType)->GetDefaultFrame());
		Shapes.back()->s->setOrigin(sf::Vector2f(Shapes.back()->s->getLocalBounds().width/2,Shapes.back()->s->getLocalBounds().height/2));
		if (Template.RandomRotation)
		{
			Shapes.back()->s->setRotation(rand()%360);
		}
		
	}
	else
	{
		SpawnShapeTimeRemain -= DeltaTime;
	}

	Lifetime -= DeltaTime;
	PendingDelete = Lifetime < 0;



}

ParticleFX::ParticleFX(std::string name)
{


	std::ifstream dataFile("Data/Particles/" + name + ".csp");
	std::string l;
	std::getline(dataFile,l);
	Lifetime = std::stof(l);

	std::getline(dataFile, l);
	SpawnShapeTime = std::stof(l);

	std::getline(dataFile, l);
	SpawnShapeTimeVariance = std::stof(l);

	std::getline(dataFile, l);
	RandomVelocity = std::stoi(l);

	std::getline(dataFile, l);
	Velocity.x = std::stof(l);

	std::getline(dataFile, l);
	Velocity.y = std::stof(l);


	std::getline(dataFile, Template.ShapeType);

	std::getline(dataFile, l);
	Template.LocVariance = std::stof(l);

	std::getline(dataFile, l);
	Template.LifeTime = std::stof(l);

	std::getline(dataFile, l);
	Template.Size = std::stof(l);

	std::getline(dataFile, l);
	Template.DeltaSize = std::stof(l);

	std::getline(dataFile, l);
	Template.Colour.r = std::stoi(l);

	std::getline(dataFile, l);
	Template.Colour.g = std::stoi(l);

	std::getline(dataFile, l);
	Template.Colour.b = std::stoi(l);

	std::getline(dataFile, l);
	Template.RandomRotation = std::stoi(l);

	std::getline(dataFile, l);
	Template.DeltaVelocity = std::stof(l);


	SpawnShapeTimeRemain = 0;



	dataFile.close();
}
