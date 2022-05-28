#include "AnimationData.h"
#include <iostream>
#include <fstream>
#include <string>
#include <filesystem>


AnimationData::AnimationData(std::string name, bool isDir)
{
	if (isDir)
	{


		AssetPath = name;
		std::ifstream dataFile(name + "/anim.txt");

		std::string tempLine;

		std::getline(dataFile, tempLine);
		int IdleLength = std::stoi(tempLine);

		std::getline(dataFile, tempLine);
		int MovementLength = std::stoi(tempLine);

		std::getline(dataFile, tempLine);
		int AttackLength = std::stoi(tempLine);

		std::getline(dataFile, tempLine);
		int DieLength = std::stoi(tempLine);

		std::getline(dataFile, tempLine);
		std::string Extension = tempLine;


		dataFile.close();
		sf::Texture* temp;
		for (size_t i = 0; i < IdleLength; i++)
		{
			temp = new sf::Texture;
			temp->loadFromFile(AssetPath + "/i" + std::to_string(i) + Extension);
			IdleSeq.push_back(temp);
		}
	}
	else
	{
		sf::Texture* temp = new sf::Texture;
		temp->loadFromFile(name);
		IdleSeq.push_back(temp);
		isStatic = true;
	}


}

sf::Texture* AnimationData::GetDefaultFrame()
{
	return IdleSeq.at(0);
}

sf::Texture* AnimationData::GetFrame(std::string State, int Frame)
{
	if (State=="Idle")
	{
		if (Frame>=IdleSeq.size())
		{
			Frame = 0;
		}
		return IdleSeq.at(0);
	}

	
}


namespace fs = std::filesystem;

std::map<std::string, AnimationData*> Anim::Animations;

void Anim::LoadAllAnims()
{

	for (const auto& entry : fs::directory_iterator("Data/ObjectTextures"))
	{
		
		
		AnimationData* tmp = new AnimationData(entry.path().generic_string(), entry.is_directory());
		Animations.emplace(entry.path().filename().stem().string(), tmp);
		
	}
	
}

