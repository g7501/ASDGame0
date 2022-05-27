#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

struct Button
{
private:
	sf::Vector2i TopLeft;
	sf::Vector2i BottomRight;

	
public:
	Button(sf::Vector2i TL, sf::Vector2i BR)
	{
		
		TopLeft = TL;
		BottomRight = BR;
	}
	Button()
	{

	}
	bool CallIfHovered()
	{
		

		bool x = sf::Mouse::getPosition().x > TopLeft.x && sf::Mouse::getPosition().x < BottomRight.x;
		bool y = sf::Mouse::getPosition().y > TopLeft.y && sf::Mouse::getPosition().y < BottomRight.y;
		
		return x && y;
	}

	void SetLoc(int x, int y, int x2, int y2)
	{
		TopLeft = sf::Vector2i(x,y);
		BottomRight = sf::Vector2i(x2,y2);
	}
	
	
	
};

class HUD
{

	sf::Text MoneyTest;
	sf::Sprite BaseSprite;

	sf::Sprite StandardTower;
	sf::Sprite Mine;
	sf::Sprite Mage;

	


public:

	HUD();
	void Render(sf::RenderWindow* window, int money);
	Button StandardTowerButton;
	Button MineButton;
	Button MageButton;

};