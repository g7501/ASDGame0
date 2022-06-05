#pragma once
#include <SFML/Graphics.hpp>
#include "AnimationData.h"
#include "Camera.h"






class Component
{
public:
	sf::Sprite Visual;
	std::string TextureName;
	sf::Vector2f RelativeLocation;
	float Rotation = 0;
	sf::Vector2f Scale;

	Component(std::string inName);
	
	std::string CurrentAnimState = "Idle";
	int CurrentAnimFrame = 0;
	double FPSCountDown = 0;

	AnimationData* AnimData;

	void RenderComponent(sf::RenderWindow* window, sf::Vector2f RenderPosition, double DeltaTime);
	
};

