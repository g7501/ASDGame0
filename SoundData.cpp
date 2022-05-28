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

void SoundComponent::AudioLogic(sf::Vector2f AudioLocation)
{
	Audio.setVolume(SoundData->Volume*Camera::Zoom);
}
