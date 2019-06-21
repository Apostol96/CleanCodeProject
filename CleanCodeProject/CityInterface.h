#pragma once
#include "City.h"

class CityInterface
{
	City city;

public:
	void startCityInterface();

private:
	void processCommand(const std::string& command);
	void printGreetingsMessage() const;
	void printHelpDocument(std::ifstream& file);
};