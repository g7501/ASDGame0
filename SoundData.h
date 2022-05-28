#pragma once
#include <SFML/Audio.hpp>
#include <map>

struct Sound
{
	sf::SoundBuffer sound;
	float Volume = 100;
	std::string Subtitle; //might be used for some stuff
	bool isAttenuated = false; // does the sound have a specific place that it is played
	float AttenuationRadius; //length before sound becomes unaudible

	Sound(std::string name);
};


class SoundComponent
{
public:
	std::string Name;
	Sound* SoundData;
	sf::Sound Audio;
	SoundComponent(std::string inName);
	void AudioLogic(sf::Vector2f AudioLocation);
};


class SoundData
{

public:
	static std::map<std::string, Sound*> sounds;

	static void LoadAllSounds();
};

