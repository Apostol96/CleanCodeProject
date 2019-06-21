#include "CityInterface.h"
#include <fstream>

#define BUFFER_SIZE 256

void CityInterface::startCityInterface()
{
	printGreetingsMessage();
	while (!std::cin.eof())
	{
		std::string command;
		std::cin >> command;
		processCommand(command);
	}
}

void CityInterface::processCommand(const std::string& command)
{
	if (command == "location")
	{
		std::cout << city.currentCrossroadName() << '\n';
	}
	else if (command == "moveTo")
	{
		std::string name;
		std::cin >> name;
		city.changeCurrentCrossroadTo(name);
	}
	else if (command == "neighbours")
	{
		city.printCurrentNeighbours();
	}
	else if (command == "close")
	{
		std::string name;
		std::cin >> name;
		city.closeCrossroad(name);
	}
	else if (command == "open")
	{
		std::string name;
		std::cin >> name;
		city.openCrossroad(name);
	}
	else if (command == "closed")
	{
		city.printClosedCrossroads();
	}
	else if (command == "addCrossroad")
	{
		std::string name;
		std::cin >> name;
		city.addCrossroad(name);
	}
	else if (command == "addStreet")
	{
		std::string from;
		std::string to;
		int length;
		std::cin >> from >> to >> length;
		city.addStreet(from, to, length);
	}
	else if (command == "help")
	{
		std::ifstream file("help.txt");
		printHelpDocument(file);
	}
	else if (std::cin.eof())
	{
		std::cout << "You've exited the city.\n";
	}
	else
	{
		std::cout << "No such command exists!\n";
	}
}

void CityInterface::printGreetingsMessage() const
{
	std::cout << "Welcome to the programme!\nIf you want to see the commands you can use, type \"help\"\n";
}

void CityInterface::printHelpDocument(std::ifstream& file)
{
	while (!file.eof())
	{
		char buffer[BUFFER_SIZE];
		file.getline(buffer, BUFFER_SIZE);
		std::cout << buffer << '\n';
	}
}