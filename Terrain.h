#pragma once
#include <SFML/Graphics.hpp>

enum GroundType
{
	Grass1,Grass2,Dirt,Water
};

class Terrain
{
	int mapX, mapY;
	GroundType* TerrainData;
	sf::Sprite* TerrainSprites;
	std::vector<sf::Sprite*> EdgeSprites;
	sf::Texture Grass1;
	sf::Texture Grass2;
	sf::Texture Dirt;
	sf::Texture Water;

	sf::Texture Grass1Edge;
	void CreateBlankMap();

public:
	Terrain();
	void RenderTerrain(sf::RenderWindow* window, sf::Vector2f);
	void LoadMap(std::string name);

};

