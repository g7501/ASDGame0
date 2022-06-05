#include "StandardIO.h"



ConfigData getConfiguration()
{
	ConfigData output;

	std::ifstream dataFile("Data/config.ini");

	//prototype version right now
	//Data is read based on its line
	std::string tempLine;
	std::getline(dataFile, tempLine);
	output.ScreenX = stoi(tempLine);
	std::getline(dataFile, tempLine);
	output.ScreenY = stoi(tempLine);
	std::getline(dataFile, tempLine);
	output.Choice = stoi(tempLine);
	

	dataFile.close();
	return output;


	
}


/*
sf::Image a;
std::ifstream b("Data/ObjectTextures/arrow.cse", std::ios::binary);

std::streampos fsize = b.tellg();
b.seekg(0, std::ios::end);
fsize = b.tellg() - fsize;
b.seekg(0, std::ios::beg);

char* c = (char*)malloc(fsize);
b.read(c, fsize);


if (a.loadFromMemory(c, fsize))
{
	std::cout << "a";
}

*/