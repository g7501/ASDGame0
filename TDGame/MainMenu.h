#pragma once


#include "HUD.h"
#include "StandardIO.h"
namespace MSWindow
{
#include <windows.h>
}

class MainMenu
{
	ConfigData config;
	sf::RenderWindow* window;
	VButton* StartButton;
	VButton* LoadButton;
	VButton* DiscordBbutton;
	VButton* ExitButton;

public:
	int MenuLoop();
	MainMenu();
};

