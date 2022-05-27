#include "Terrain.h"
#include <iostream>


//might want to refactor this so it only uses the bare minimum number of sprites
void Terrain::CreateBlankMap()
{
	TerrainData = new GroundType[mapX*mapY];
	TerrainSprites = new sf::Sprite[mapX*mapY];
	for (size_t i = 0; i < mapX*mapY; i++)
	{
		int tmp = i; //needed for the position calcs
		TerrainData[i] = GroundType::Grass1;
		TerrainSprites[i].setTexture(Grass1);
		TerrainSprites[i].setPosition(tmp/mapY*128 - 64*mapY,tmp%mapY*128 - 64*mapX);
		
	}


}





Terrain::Terrain()
{
	 //allow for other maps to be loaded



	//Firstly load all the textures
	if (!Grass1.loadFromFile("Data/Terrain/Grass1.png"))
	{
		//TODO
	}

	if (!Water.loadFromFile("Data/Terrain/Water.png"))
	{
		//TODO
	}
	if (!Grass1Edge.loadFromFile("Data/Terrain/Grass1Edge.png"))
	{
		//^
	}


	LoadMap("Default.png");

}

void Terrain::RenderTerrain(sf::RenderWindow* window, sf::Vector2f Camera)
{
	for (size_t i = 0; i < mapX*mapY; i++)
	{
		TerrainSprites[i].setPosition(TerrainSprites[i].getPosition()+Camera);
		window->draw(TerrainSprites[i]);
	}
	for (sf::Sprite* i: EdgeSprites)
	{
		i->setPosition(i->getPosition()+Camera);
		window->draw(*i);
	}


}

void Terrain::LoadMap(std::string name)
{
	sf::Image MapData;
	MapData.loadFromFile("Data/Maps/"+name);
	mapX = MapData.getSize().x;
	mapY = MapData.getSize().y;
	

	TerrainData = new GroundType[mapX * mapY];
	TerrainSprites = new sf::Sprite[mapX * mapY];
	for (size_t i = 0; i < mapX * mapY; i++)
	{
		int tmp = i; //needed for the position calcs
		if (MapData.getPixel(i%mapY,i/mapY).b == 255)
		{
			TerrainData[i] = GroundType::Water;
			TerrainSprites[i].setTexture(Water);
		}
		if (MapData.getPixel(i % mapY, i / mapY).b == 0)
		{
			TerrainData[i] = GroundType::Grass1;
			TerrainSprites[i].setTexture(Grass1);
		}

		TerrainSprites[i].setPosition(tmp / mapY * 128 - 64 * mapY, tmp % mapY * 128 - 64 * mapX);


		//now for the edges
		if (i-1>0)
		{
			//if on verge
			if(TerrainData[i-1]!=TerrainData[i] && TerrainData[i]==GroundType::Grass1)
			{
				//a difference
				EdgeSprites.push_back(new sf::Sprite());
				EdgeSprites.back()->setTexture(Grass1Edge);
				EdgeSprites.back()->setPosition(tmp / mapY * 128 - 64 * mapY, tmp % mapY * 128 - 64 * mapX);
				
				EdgeSprites.back()->setRotation(-90);
			}
		}

		
	}

	//test

}
