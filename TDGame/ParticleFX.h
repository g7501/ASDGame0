#pragma once
#include <SFML/Graphics.hpp>
#include "AnimationData.h"
#include "Utils.h"
#include "HUD.h"

struct ParticleTemplate
{
	float LocVariance;
	float Size;
	std::string ShapeType;
	sf::Color Colour;
	float LifeTime;
	float DeltaSize;
};


struct Shape
{
	sf::Sprite* s;
	sf::Vector2f Velocity = sf::Vector2f(0,0);
	float RemainingTime;

	Shape(float rt, sf::Vector2f v)
	{
		RemainingTime = rt;
		Velocity = v;

	}
};


class ParticleFX
{
public:
	bool PendingDelete = false;
	sf::Vector2f Velocity;
	bool RandomVelocity;
	
	std::vector<Shape*> Shapes;

	sf::Vector2f Loc = sf::Vector2f(300,300);


	float Lifetime;
	
	ParticleTemplate Template;
	float SpawnShapeTime;
	float SpawnShapeTimeVariance;

	void Render(sf::RenderWindow* window, sf::Vector2f RenderLoc, double DeltaTime);

	ParticleFX();

private:
	float SpawnShapeTimeRemain;
	float TimeExisting = 0;

};

