#pragma once
#include "City.h"

class CityInterface
{
	City city;

public:
	void startCityInterface();

private:
	void addCrossroad(const std::string& name);
	void addStreet(const std::string& from, const std::string& to, int length);
	void printLocation();
	void changeLocation(const std::string& to);
	void printCurrentCrossroadNeighbours();
	void close(const std::string& name);
	void open(const std::string& name);
	void printClosedCrossroads();
	void processCommand(const std::string& command);
};