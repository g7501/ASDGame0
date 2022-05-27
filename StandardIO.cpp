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



	dataFile.close();
	return output;
}
