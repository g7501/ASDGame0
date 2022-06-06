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

AnimationData::AnimationData(std::string name)
{
	//reads from a csanim file
	std::ifstream file(name, std::ios::binary);
	file.read((char*) &Scale, 4);
	file.read((char*)&RelativeX, 4);
	file.read((char*)&RelativeY, 4);
	file.read((char*)&FPS, 4);

	int tmp;
	file.read((char*)&tmp,4);
	for (size_t i	= 0; i < tmp; i++)
	{
		int tmpLen;
		file.read((char*)&tmpLen, 4);
		char* imageData = new char[tmpLen];
		file.read(imageData,tmpLen);
		IdleSeq.push_back(new sf::Texture());
		IdleSeq.back()->loadFromMemory(imageData,tmpLen);
		delete[] imageData;
	}
	file.read((char*)&tmp, 4);
	for (size_t i = 0; i < tmp; i++)
	{
		int tmpLen;
		file.read((char*)&tmpLen, 4);
		char* imageData = new char[tmpLen];
		file.read(imageData, tmpLen);
		AttackSeq.push_back(new sf::Texture());
		AttackSeq.back()->loadFromMemory(imageData, tmpLen);
		delete[] imageData;
	}

	file.read((char*)&tmp, 4);
	for (size_t i = 0; i < tmp; i++)
	{
		int tmpLen;
		file.read((char*)&tmpLen, 4);
		char* imageData = new char[tmpLen];
		file.read(imageData, tmpLen);
		MovementSeq.push_back(new sf::Texture());
		MovementSeq.back()->loadFromMemory(imageData, tmpLen);
		delete[] imageData;
	}

	file.read((char*)&tmp, 4);
	for (size_t i = 0; i < tmp; i++)
	{
		int tmpLen;
		file.read((char*)&tmpLen, 4);
		char* imageData = new char[tmpLen];
		file.read(imageData, tmpLen);
		DieSeq.push_back(new sf::Texture());
		DieSeq.back()->loadFromMemory(imageData, tmpLen);
		delete[] imageData;
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
		return IdleSeq.at(Frame);
	}

	
}

int AnimationData::GetLengthOfCurrentAnim(std::string State)
{
	if (State=="Idle")
	{
		return IdleSeq.size();
	}
	return 0;
}


namespace fs = std::filesystem;

std::map<std::string, AnimationData*> Anim::Animations;

void Anim::LoadAllAnims()
{

	for (const auto& entry : fs::directory_iterator("Data/ObjectTextures"))
	{
		AnimationData* tmp;
		if (entry.path().filename().extension().string()==".csanim")
		{
			tmp = new AnimationData(entry.path().generic_string());
		}
		else
		{
			tmp = new AnimationData(entry.path().generic_string(), entry.is_directory());
		}
		Animations.emplace(entry.path().filename().stem().string(), tmp);
		
	}
	
}

