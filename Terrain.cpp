#include "Terrain.h"
#include <iostream>


int Terrain::mapX;
int Terrain::mapY;
GroundType* Terrain::TerrainData;
int Terrain::GridSize = 128;


//might want to refactor this so it only uses the bare minimum number of sprites
void Terrain::CreateBlankMap()
{
	TerrainData = new GroundType[mapX*mapY];
	TerrainSprites = new SpriteLoc[mapX*mapY];
	for (size_t i = 0; i < mapX*mapY; i++)
	{
		int tmp = i; //needed for the position calcs
		TerrainData[i] = GroundType::Grass1;
		TerrainSprites[i].s.setTexture(Grass1);
		TerrainSprites[i].l = sf::Vector2f(tmp/mapY*128 - 64*mapY,tmp%mapY*128 - 64*mapX);
		
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

	if (!Grass2.loadFromFile("Data/Terrain/Grass2.png"))
	{
		//TODO
	}

	if (!Dirt1.loadFromFile("Data/Terrain/Dirt1.png"))
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

	if (!Grass1Edge.loadFromFile("Data/Terrain/Beach.png"))
	{
		//^
	}


	LoadMap("Default.png");

}

void Terrain::RenderTerrain(sf::RenderWindow* window)
{
	
	
	sf::Vector2f LocalPosition;


	for (int i = mapX*mapY - 1; i >= 0; i--)
	{
		LocalPosition = (TerrainSprites[i].l + Camera::Location) * Camera::Zoom;
		TerrainSprites[i].s.setScale(Camera::Zoom, Camera::Zoom);
		TerrainSprites[i].s.setPosition(LocalPosition);
		window->draw(TerrainSprites[i].s);
	}

	for (SpriteLoc* i: EdgeSprites)
	{
		LocalPosition = (i->l + Camera::Location)*Camera::Zoom;
		i->s.setPosition(LocalPosition);
		i->s.setScale(Camera::Zoom, Camera::Zoom);
		window->draw(i->s);
	}


}

void Terrain::LoadMap(std::string name)
{
	sf::Image MapData;
	MapData.loadFromFile("Data/Maps/"+name);
	mapX = MapData.getSize().x;
	mapY = MapData.getSize().y;
	

	TerrainData = new GroundType[mapX * mapY];
	TerrainSprites = new SpriteLoc[mapX * mapY];
	for (size_t i = 0; i < mapX * mapY; i++)
	{
		int tmp = i; //needed for the position calcs
		if (MapData.getPixel(i%mapY,i/mapY).b == 255)
		{
			TerrainData[i] = GroundType::Water;
			TerrainSprites[i].s.setTexture(Water);
		}
		if (MapData.getPixel(i % mapY, i / mapY).b == 55)
		{
			TerrainData[i] = GroundType::Grass1;
			TerrainSprites[i].s.setTexture(Grass1);
		}
		if (MapData.getPixel(i % mapY, i / mapY).b == 0)
		{
			TerrainData[i] = GroundType::Grass2;
			TerrainSprites[i].s.setTexture(Grass2);
		}

		if (MapData.getPixel(i % mapY, i / mapY).b == 31)
		{
			TerrainData[i] = GroundType::Dirt1;
			TerrainSprites[i].s.setTexture(Dirt1);
		}


		TerrainSprites[i].l = sf::Vector2f(tmp % mapY * 128 - 64 * mapX, tmp / mapY * 128 - 64 * mapY);

		//now for the edges
		if (i-1>0)
		{
			//if on verge
			if(TerrainData[i-1]!=TerrainData[i] && TerrainData[i]==GroundType::Grass1)
			{
				//a difference
				EdgeSprites.push_back(new SpriteLoc());
				EdgeSprites.back()->s.setTexture(Grass1Edge);
				EdgeSprites.back()->l = sf::Vector2f(tmp / mapY * 128 - 64 * mapY, tmp % mapY * 128 - 64 * mapX);
				
				EdgeSprites.back()->s.setRotation(-90);
			}
		}

		
	}

	

}

GroundType Terrain::GetGroundTypeAtMouse()
{
	sf::Vector2f Location = (sf::Vector2f)sf::Mouse::getPosition() / Camera::Zoom - Camera::Location;
	//just need to divide by 128 now
	Location /= (float)GridSize;
	int x = trunc(Location.x+mapX/2); //using trunc to be safe
	int y = trunc(Location.y+mapY/2);
	int idx = y*mapX + x;

	if (idx>=mapX*mapY)
	{
		return GroundType::Invalid;
	}
	
	return TerrainData[idx];
}
