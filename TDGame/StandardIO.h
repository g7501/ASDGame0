#pragma once
#include <iostream>
#include <fstream>
#include <string>


struct ConfigData
{
	int ScreenX;
	int ScreenY;
	int Choice;
};

//Reads the config data
ConfigData getConfiguration();

