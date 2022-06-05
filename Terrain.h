#pragma once
#include "Camera.h"

enum GroundType
{
	Grass1,Grass2,Dirt1,Water,Invalid
};


struct SpriteLoc
{
	sf::Sprite s;
	sf::Vector2f l;
};

class Terrain
{

	SpriteLoc* TerrainSprites;
	std::vector<SpriteLoc*> EdgeSprites;
	sf::Texture Grass1;
	sf::Texture Grass2;
	sf::Texture Dirt1;
	sf::Texture Water;

	sf::Texture Grass1Edge;
	sf::Texture Beach;
	void CreateBlankMap();

	static int GridSize;

public:
	Terrain();
	void RenderTerrain(sf::RenderWindow* window);
	void LoadMap(std::string name);

	static int mapX, mapY;
	static GroundType* TerrainData;

	static GroundType GetGroundTypeAtMouse();

};

