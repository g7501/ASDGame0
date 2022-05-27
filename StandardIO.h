#pragma once
#include <iostream>
#include <fstream>
#include <string>


struct ConfigData
{
	int ScreenX;
	int ScreenY;
};

//Reads the config data
ConfigData getConfiguration();