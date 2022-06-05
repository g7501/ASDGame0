#pragma once
#include <SFML/Graphics.hpp>
class AnimationData
{

	std::vector<sf::Texture*> IdleSeq;
	std::vector<sf::Texture*> MovementSeq;
	std::vector<sf::Texture*> AttackSeq;
	std::vector<sf::Texture*> DieSeq;
public:
	bool isStatic = false;
	std::string AssetPath;
	float FPS = 30;
	float Scale = 1;
	float RelativeX = 0;
	float RelativeY = 0;

	AnimationData(std::string name, bool isDir);
	AnimationData(std::string name);
	sf::Texture* GetDefaultFrame();
	sf::Texture* GetFrame(std::string State, int Frame);
	int GetLengthOfCurrentAnim(std::string State);

	
};



class Anim
{
	Anim() {};
public:
	static void LoadAllAnims();

	static std::map<std::string, AnimationData*> Animations;


};







