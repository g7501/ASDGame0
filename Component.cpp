#include "Component.h"
#include <iostream>

Component::Component(std::string inName)
{
	if (Anim::Animations.contains(inName))
	{
		
		Visual.setTexture(*Anim::Animations.at(inName)->GetDefaultFrame());
		Scale = sf::Vector2f(1, 1);
		RelativeLocation = sf::Vector2f(0, 0);
		TextureName = inName;
		Visual.setOrigin((sf::Vector2f)Visual.getTexture()->getSize()*0.5f);
		AnimData = Anim::Animations.at(inName);
	}
	else
	{
		std::cout << "Could not find anim" << std::endl;
		//add proper error here
	}

}


void Component::RenderComponent(sf::RenderWindow* window, sf::Vector2f RenderPosition, double DeltaTime)
{
	if (FPSCountDown<=0)
	{

		FPSCountDown = 1/AnimData->FPS;
		Visual.setTexture(*AnimData->GetFrame(CurrentAnimState, CurrentAnimFrame));
		CurrentAnimFrame++;
		if (CurrentAnimFrame >= AnimData->GetLengthOfCurrentAnim(CurrentAnimState))
		{
			CurrentAnimFrame = 0;

		}
	}
	else
	{
		FPSCountDown -= DeltaTime;
	}


	Visual.setScale(Camera::Zoom*0.5,Camera::Zoom*0.5);
	Visual.setRotation(Rotation);
	Visual.setPosition(RenderPosition+RelativeLocation);
	window->draw(Visual);
}

