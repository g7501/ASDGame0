#include "SoundData.h"
#include "Camera.h"
#include <filesystem>


namespace fs = std::filesystem;

std::map<std::string, Sound*> SoundData::sounds;

Sound::Sound(std::string name)
{
	sound.loadFromFile(name);

}

void SoundData::LoadAllSounds()
{

	for (const auto& entry : fs::directory_iterator("Data/Audio"))
	{


		Sound* tmp = new Sound(entry.path().generic_string());
		sounds.emplace(entry.path().filename().stem().string(), tmp);

	}
}

SoundComponent::SoundComponent(std::string inName)
{
	Name = inName;
	SoundData = SoundData::sounds.at(Name);
	Audio.setBuffer(SoundData->sound);
}

float Distance(sf::Vector2f a, sf::Vector2f b)
{
	float x = pow(a.x-b.x,2);
	float y = pow(a.y-b.y,2);
	return pow(x+y,0.5);
}


void SoundComponent::AudioLogic(sf::Vector2f AudioLocation)
{
	if (SoundData->isAttenuated)
	{
		float dist = SoundData->AttenuationRadius / Distance(AudioLocation, Camera::Location);
		Audio.setVolume(SoundData->Volume * pow(Camera::Zoom, 1.5) * dist);
	}

}
