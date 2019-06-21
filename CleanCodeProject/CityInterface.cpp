#include "CityInterface.h"

void CityInterface::startCityInterface()
{
	while (!std::cin.eof())
	{
		std::string command;
		std::cin >> command;
		processCommand(command);
	}
}

void CityInterface::addCrossroad(const std::string& name)
{
	city.addCrossroad(name);
}

void CityInterface::addStreet(const std::string& from, const std::string& to, int length)
{
	city.addStreet(from, to, length);
}

void CityInterface::printLocation()
{
	std::cout << city.currentCrossroadName() << '\n';
}

void CityInterface::changeLocation(const std::string& to)
{
	city.changeCurrentCrossroadTo(to);
}

void CityInterface::printCurrentCrossroadNeighbours()
{
	city.printCurrentNeighbours();
}

void CityInterface::close(const std::string& name)
{
	city.closeCrossroad(name);
}

void CityInterface::open(const std::string& name)
{
	city.openCrossroad(name);
}

void CityInterface::printClosedCrossroads()
{
	city.printClosedCrossroads();
}

void CityInterface::processCommand(const std::string& command)
{
	if (command == "location")
	{
		printLocation();
	}
	else if (command == "change")
	{
		std::string name;
		std::cin >> name;
		changeLocation(name);
	}
	else if (command == "neighbours")
	{
		printCurrentCrossroadNeighbours();
	}
	else if (command == "close")
	{
		std::string name;
		std::cin >> name;
		close(name);
	}
	else if (command == "open")
	{
		std::string name;
		std::cin >> name;
		open(name);
	}
	else if (command == "closed")
	{
		printClosedCrossroads();
	}
	else if (command == "addCrossroad")
	{
		std::string name;
		std::cin >> name;
		addCrossroad(name);
	}
	else if (command == "addStreet")
	{
		std::string from;
		std::string to;
		int length;
		std::cin >> from >> to >> length;
		addStreet(from, to, length);
	}
}