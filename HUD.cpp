#include "HUD.h"
#include "GameInstance.h"
#include "StandardIO.h"

void HUD::Render(sf::RenderWindow* window, int money)
{
	MoneyTest.setString("Gold: "+std::to_string(money));
	window->draw(MoneyTest);
	window->draw(BaseSprite);
	window->draw(StandardTower);
	window->draw(Mine);
	window->draw(Mage);


}







HUD::HUD()
{

	ConfigData Config = getConfiguration();



	sf::Font* font = new sf::Font();
	if (!font->loadFromFile("Data/UI/UI.ttf"))
	{
		// error...
	}

	MoneyTest.setFont(*font);
	MoneyTest.setPosition(((float)Config.ScreenX)/100, ((float)Config.ScreenY) / 100);

	//second thing is the main UI element
	sf::Texture* UIT = new sf::Texture();
	if (!UIT->loadFromFile("Data/UI/UIbase.png"))
	{
		//TODO
	}
	BaseSprite.setTexture(*UIT);

	//Need to make the UI the correct size for the user's screensize
	float ScaleX = (float)Config.ScreenX / UIT->getSize().x;
	float ScaleY = (float)Config.ScreenY / UIT->getSize().y;

	sf::Texture* UITower = new sf::Texture();
	if (!UITower->loadFromFile("Data/UI/UITower.png"))
	{
		//TODO
	}
	StandardTower.setTexture(*UITower);
	StandardTower.setPosition(0, Config.ScreenY*0.75);

	sf::Texture* UIMine = new sf::Texture();
	if (!UIMine->loadFromFile("Data/UI/UIMine.png"))
	{
		//TODO
	}
	Mine.setTexture(*UIMine);
	Mine.setPosition(600 * ScaleX, Config.ScreenY * 0.75);

	sf::Texture* UIMage = new sf::Texture();
	if (!UIMage->loadFromFile("Data/UI/UIMage.png"))
	{
		//TODO
	}
	Mage.setTexture(*UIMage);
	Mage.setPosition(1200 * ScaleX, Config.ScreenY * 0.75);


	BaseSprite.setScale(ScaleX,ScaleY);
	StandardTower.setScale(ScaleX,ScaleY);
	Mine.setScale(ScaleX,ScaleY);
	Mage.setScale(ScaleX,ScaleY);


	StandardTowerButton.SetLoc(0,Config.ScreenY-ScaleY*200,ScaleX*600,Config.ScreenY);
	MineButton.SetLoc(600, Config.ScreenY - ScaleY * 200, ScaleX * 600 + 600, Config.ScreenY);
	MageButton.SetLoc(1200, Config.ScreenY - ScaleY * 200, ScaleX * 600 + 1200, Config.ScreenY);
	

}