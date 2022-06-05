#include "ParticleFX.h"
#include <iostream>






void ParticleFX::Render(sf::RenderWindow* window, sf::Vector2f RenderLoc, double DeltaTime)
{

	int idx = 0;
	for (Shape* i : Shapes)
	{
		window->draw(*i->s);
		i->s->setPosition(i->s->getPosition()+(i->Velocity*(float)DeltaTime));
		i->RemainingTime -= DeltaTime;
		i->s->setScale(i->s->getScale()+i->s->getScale()*(float)DeltaTime*Template.DeltaSize);
		
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
		Shapes.push_back(new Shape(10, tVel));
		Shapes.back()->s = new sf::Sprite();
		Shapes.back()->s->setScale(sf::Vector2f(Template.Size,Template.Size));
		Shapes.back()->s->setColor(Template.Colour);
		Shapes.back()->s->setPosition(Loc);
		Shapes.back()->s->setTexture(*Anim::Animations.at(Template.ShapeType)->GetDefaultFrame());
		Shapes.back()->s->setOrigin(sf::Vector2f(Shapes.back()->s->getLocalBounds().width/2,Shapes.back()->s->getLocalBounds().height/2));
			
		
	}
	else
	{
		SpawnShapeTimeRemain -= DeltaTime;
	}

	Lifetime -= DeltaTime;
	PendingDelete = Lifetime < 0;



}

ParticleFX::ParticleFX()
{
	Velocity = sf::Vector2f(1, 1);
	RandomVelocity = true;
	SpawnShapeTime = 6;
	SpawnShapeTimeVariance = 0.1;
	Lifetime = 100;
	SpawnShapeTimeRemain = 0;

	Template.Colour = sf::Color(255,255,255);
	Template.LocVariance = 1;
	Template.ShapeType = "BlurredDot";
	Template.Size = 0.6;
	Template.DeltaSize = -0.1;

}
