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
	AnimationData(std::string name, bool isDir);
	sf::Texture* GetDefaultFrame();
	sf::Texture* GetFrame(std::string State, int Frame);
	
};



class Anim
{
	Anim() {};
public:
	static void LoadAllAnims();

	static std::map<std::string, AnimationData*> Animations;


};







