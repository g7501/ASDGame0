#include "GameInstance.h"
#include "MainMenu.h"
#include <iostream>
#include "Editor.h"

int main()
{
	

	int choice = 0;
	//MainMenu* Menu = new MainMenu();
	//choice = Menu->MenuLoop();


	ConfigData conf = getConfiguration();

	choice = conf.Choice;//temp



	if (choice == 0)
	{
		Anim::LoadAllAnims();
		SoundData::LoadAllSounds();
		Building::LoadAllBuildings();

		GameInstance* Game = new GameInstance();
		Game->GameLoop();
	}
	if (choice ==1)
	{
		Anim::LoadAllAnims();
		SoundData::LoadAllSounds();
		Building::LoadAllBuildings();

		GameInstance* Game = new GameInstance();
		Game->LoadGame();
		Game->GameLoop();

	}





	//particle editor
	if (choice == 2)
	{
		Anim::LoadAllAnims();
		SoundData::LoadAllSounds();
		Editor* editor = new Editor();
		editor->RunEditor(choice);
	}


}